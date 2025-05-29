#define RELAY_PIN 4
#define SWITCH_DEFAULT_COLOR 3
#define TURBO_PIN A5

// SETTINGS =========================================================================================

// The voltage reading from the pressure sensor to activate boost mode on the gauges.
const float VOLTAGE_THRESHOLD_UPPER = 1.2;

// The voltage reading from the pressure sensor to deactivate boost mode on the gauges.
const float VOLTAGE_THRESHOLD_LOWER = 0.8;

// The time in seconds the gauges will remain in boost mode AFTER the lower voltage threshold was hit.
const float GAUGE_DELAY_IN_S = 1.0;

// The number of times the gauges will flash when entering boost mode.
const char NUM_FLASHES = 2;

// The time in milliseconds a color will be held in flash mode.
// AKA Flash speed.
const int FLASH_DELAY_IN_MS = 100;

// ==================================================================================================

float voltage_threshold = VOLTAGE_THRESHOLD_UPPER;
bool has_flashed = false;
bool default_on_blue = true;
unsigned long previous_time = 0;


void turn_blue() {
  if(default_on_blue)
    digitalWrite(RELAY_PIN, LOW);
  else
    digitalWrite(RELAY_PIN, HIGH);
}

void turn_red() {
  if(default_on_blue)
    digitalWrite(RELAY_PIN, HIGH);
  else
    digitalWrite(RELAY_PIN, LOW);
}

void setup() {
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(SWITCH_DEFAULT_COLOR, INPUT_PULLUP);

  int switch_state = digitalRead(SWITCH_DEFAULT_COLOR);
  default_on_blue = (switch_state == HIGH);

  turn_blue();
  Serial.begin(9600);

}

void flash() {
  turn_red();

  for(char i = 0; i < NUM_FLASHES; i++) {
    turn_blue();
    delay(FLASH_DELAY_IN_MS);
    turn_red();
    delay(FLASH_DELAY_IN_MS);
  }
}

void loop() {
  int analog_value = analogRead(TURBO_PIN);
  float voltage = analog_value * (5.0 / 1023.0);

  int switch_state = digitalRead(SWITCH_DEFAULT_COLOR);
  default_on_blue = (switch_state == HIGH);

  Serial.println(voltage);

  if(voltage > voltage_threshold) {
    if(!has_flashed) {
      flash();
      voltage_threshold = VOLTAGE_THRESHOLD_LOWER;
      has_flashed = true;
    }
    turn_red();
    previous_time = millis();
  } 
  else {
    if((millis() - previous_time) <= GAUGE_DELAY_IN_S * 1000) {
      turn_red();
    }
    else {
      turn_blue();
      voltage_threshold = VOLTAGE_THRESHOLD_UPPER;
      has_flashed = false;      
    }
  }
}

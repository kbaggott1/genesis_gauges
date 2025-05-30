// PIN DEFINITIONS ==================================================================================

#define RELAY_PIN 4
#define SWITCH_DEFAULT_COLOR_PIN 3
#define TURBO_PIN A5

// SETTINGS =========================================================================================

// The voltage reading from the pressure sensor to activate boost mode on the gauges.
const float VOLTAGE_ACTIVATE_BOOST_MODE = 1.2;
const float VOLTAGE_DEACTIVATE_BOOST_MODE = 0.8;

// The time in seconds the gauges will remain in boost mode AFTER the lower voltage threshold was hit.
const float GAUGE_DELAY_IN_S = 1.0;

// The number of times the gauges will flash when entering boost mode.
const char NUM_FLASHES = 2;

// The time in milliseconds a color will be held in flash mode.
const int FLASH_DELAY_IN_MS = 100;

// ==================================================================================================

float voltage_threshold = VOLTAGE_ACTIVATE_BOOST_MODE;
bool has_flashed = false;
bool default_on_blue = true;
unsigned long previous_time = 0;
bool is_red = false; 

// Helper Functions =================================================================================

void set_color(bool red) {
  if (is_red != red) {
    if (default_on_blue) {
      digitalWrite(RELAY_PIN, red ? HIGH : LOW);
    } else {
      digitalWrite(RELAY_PIN, red ? LOW : HIGH);
    }
    is_red = red;
  }
}

void turn_blue() {
  set_color(false);
}

void turn_red() {
  set_color(true);
}

void flash() {
  for (char i = 0; i < NUM_FLASHES; i++) {
    turn_red();
    delay(FLASH_DELAY_IN_MS);
    turn_blue();
    delay(FLASH_DELAY_IN_MS);
  }
}

void setup() {
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(SWITCH_DEFAULT_COLOR_PIN, INPUT_PULLUP);

  default_on_blue = (digitalRead(SWITCH_DEFAULT_COLOR_PIN) == HIGH);

  turn_blue();
  Serial.begin(9600);
}

void loop() {
  int analog_value = analogRead(TURBO_PIN);
  float voltage = analog_value * (5.0 / 1023.0);
  Serial.println(voltage);

  if (voltage > voltage_threshold) {
    if (!has_flashed) {
      flash();
      voltage_threshold = VOLTAGE_DEACTIVATE_BOOST_MODE;
      has_flashed = true;
    }
    turn_red();
    previous_time = millis();
  } 
  else {
    if ((millis() - previous_time) <= GAUGE_DELAY_IN_S * 1000) {
      turn_red();
    } 
    else {
      turn_blue();
      voltage_threshold = VOLTAGE_ACTIVATE_BOOST_MODE;
      has_flashed = false;
    }
  }
}

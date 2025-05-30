# Genesis Gauges

This project allows your aftermarket automotive gauges to dynamically change LED colors based on turbo boost levels. It was built for a **Hyundai Genesis Coupe**, but can be adapted for any vehicle with compatible 12V analog gauges and a turbo pressure sensor.

## 📋 Overview

The gauges light up **blue** or **red** depending on boost state:

* **Below boost** → one color (default blue)
* **In boost** → other color (default red)
* **Switching behavior can be reversed** via a toggle switch

Boost mode is detected via a pressure sensor that outputs an analog voltage. When voltage crosses a threshold, the gauge backlight color is switched using a relay.

---

## 🔧 Hardware Requirements

* [ELEGOO Nano Board CH340/ATmega328P](https://www.amazon.ca/dp/B0713XK923?ref=ppx_yo2ov_dt_b_fed_asin_title&th=1) (presoldered is also okay if you dont have a soldering kit)
* [2-1/16" ProSport Evo Electrical Boost Gauge](https://prosportgauges.com/products/2-1-16-evo-electrical-boost-gauge)
* [SRD-05VDC-SL-C relay](https://www.amazon.ca/10PCS-Power-Relay-SRD-05VDC-SL-C-Type/dp/B07VLRMFK7/ref=asc_df_B07VLRMFK7?mcid=5ff0bce8950539a18cbb1c2ade3e6fcf&tag=googleshopc0c-20&linkCode=df0&hvadid=752800291404&hvpos=&hvnetw=g&hvrand=331648257033183498&hvpone=&hvptwo=&hvqmt=&hvdev=c&hvdvcmdl=&hvlocint=&hvlocphy=9000501&hvtargid=pla-2445217979514&psc=1&gad_source=1)
* [SPDT switch (to set default color behavior)](https://www.amazon.ca/Twidec-Rocker-Control-Pre-soldered-KCD2-102N-4C-X/dp/B07W4HGMZS/ref=sr_1_22_sspa?dib=eyJ2IjoiMSJ9.idOxNavnFrgOJ1UHe7UNofAZXw8z8GRo8Qem3v6544zboRwXP7044oAUqFWbUejfiz8YYshUUTs7INzkayejqDL09O_0Ow-CaiHk-uh7z_F8nmt-1m3U3bZARp1BZcDFQg2CRQ4V8q7aKzzmW83ImhD6Ty3inPwtsJ4PRQKv8pNWcLS8NhF895thiGZdQfz5FEkf87VpcPrwbZtF_e6fFuxzgyj4xEsFTL_QK27W0dfb5TMMh6HsLg-FEkrRPVVBM6nQelDHT_TGF0SzhMBjj2RZ_0zGr-1ebqyYrio05ao.ouSbB4K5arQSljoK89-kOFW75djkw9y_24gealj8JIA&dib_tag=se&keywords=switch&qid=1748565772&sr=8-22-spons&sp_csd=d2lkZ2V0TmFtZT1zcF9tdGY&th=1)
* [2x ProSport Evo Gauges of your choice](https://prosportgauges.com/collections/52mm-evo-series-red-blue)

### Schematic

![schematic](https://github.com/user-attachments/assets/3040c750-4fec-4d7f-a310-64795aa9110a)


---

## ⚙️ Features

* **Automatic LED color change** based on boost levels
* **Voltage thresholds** to choose when boost mode should be activated
* **Flash animation** when entering boost mode
* **Toggle switch** for reversing color behavior
* Easy to modify thresholds and delays via code constants

---

## 🚀 Code Behavior

```cpp
#define RELAY_PIN 4                     // Controls LED color via relay
#define SWITCH_DEFAULT_COLOR_PIN 3     // Reads toggle switch state
#define TURBO_PIN A5                   // Analog input from pressure sensor

const float VOLTAGE_THRESHOLD_UPPER = 1.2; // Boost mode activation
const float VOLTAGE_THRESHOLD_LOWER = 0.8; // Boost mode deactivation
const float GAUGE_DELAY_IN_S = 1.0;        // Hold boost color for 1s after drop (enables time for shifting)
const char NUM_FLASHES = 2;                // Number of flashes when entering boost mode
const int FLASH_DELAY_IN_MS = 100;         // Flash speed
```

---
You can change the pin numbers so long as the pressure sensor (boost sensor) goes in an analog pin on the board.

## 🧠 Behavior Modes

| Boost State  | Switch OFF (default blue) | Switch ON (default red) |
| ------------ | ------------------------- | ----------------------- |
| Not in boost | Blue                      | Red                     |
| In boost     | Red                       | Blue                    |

The SPDT switch flips the meaning of "default" color.

---

## 📦 Installation

1. Flash the Arduino with the provided `.ino` file
2. Wire up the components according to the schematic
3. Connect the analog sensor and test voltage thresholds
4. Toggle the switch to set your preferred resting color

---

# PreciseLM35

A simple LM35 wrapper with optional voltage calibration facility

Features selectable reference voltage. Actual AREF value is polled from MCU, eliminating inaccuracies due to changing AREF value (depleting batteries, etc)

## Examples

### High resolution
Uses maximum precision when measuring temperature by executing analogReference(INTERNAL)

This way LM35's output will be measured on a smaller scale (0mV - 1100mV) than standard 3.3V or 5V

WARNING: Using internal AREF, your maximum measured temperature is limited to `1100 / 10 = 110.0C (230F)`

```ino
#include <PreciseLM35.h>

const int pinLM35 = A0;
PreciseLM35 lm35(pinLM35);

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println("Temp (C): " + String(lm35.readCelsius()));
  Serial.println("Temp (F): " + String(lm35.readFahrenheit()));
  delay(2000);
} 
```

### Normal resolution with actual Vcc measurement
Uses MCU's reported Vcc voltage instead of a nominal value of 3.3V or 5V which can change over time due to depleting battery, unstable power supply, etc.

Use this if you need to measure temperatures higher than 110C or other analog sensor needs to read values higher than 1.1V. 

Otherwise CalibratedInternalRead gives you more accurate results

```ino
#include <PreciseLM35.h>

const int pinLM35 = A0;
PreciseLM35 lm35(pinLM35, DEFAULT);

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println("Temp (C): " + String(lm35.readCelsius()));
  Serial.println("Temp (F): " + String(lm35.readFahrenheit()));
  Serial.println("AREF: " + String(lm35.readPreciseAref()));
  delay(2000);
}
```
## High resolution with calibrated 1.1V
Uses maximum precision when measuring temperature by executing analogReference(INTERNAL). 

This way LM35's output will be measured on a smaller scale (0mV - 1100mV) than  standard 3.3V or 5V

WARNING: Using internal AREF, your maximum measured temperature is limited to  `1100 / 10 = 110.0C (230F)`

### Calibration:
 - First run with measuredVsReadAreFratio = 1.0
 - Use a multimeter and measure voltage on AREF pin. It should be around 1.1V 
 - Divide this value by 1.1 and use it as measuredVsReadArefRatio
 - Check if serial terminal shows correct value for AREF

```ino
#include <PreciseLM35.h>

const int pinLM35 = A0;
const float measuredVsReadArefRatio = 1.0; // enter here your ratio between measured and expected AREF
PreciseLM35 lm35(pinLM35, INTERNAL, measuredVsReadArefRatio);

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println("Temp (C): " + String(lm35.readCelsius()));
  Serial.println("Temp (F): " + String(lm35.readFahrenheit()));
  Serial.println("AREF: " + String(lm35.readPreciseAref()));
  delay(2000);
}
```

## Normal resolution with calibrated Vcc measurement
Use this if you need to measure temperatures higher than 110C or other analog sensor needs to read values higher than 1.1V. 

Otherwise CalibratedInternalRead gives you more accurate results

Uses MCU's reported Vcc voltage instead of a nominal value of 3.3V or 5V which can change over time due to depleting battery, unstable power supply, etc.

### Calibration
 - First run with measuredVsReadAreFratio = 1.0
 - Use a multimeter and measure voltage on AREF pin. It should be around 3.3V or 5V depending on your Arduino
 - Divide this value by the displayed AREF value and use it as measuredVsReadAreFratio
 - Run the sketch again and check if serial terminal shows correct value for AREF
 
```ino
#include <PreciseLM35.h>

const int pinLM35 = A0;
const float measuredVsReadArefRatio = 1.0; // enter here your ratio between measured and expected AREF
PreciseLM35 lm35(pinLM35, DEFAULT, measuredVsReadArefRatio);

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println("Temp (C): " + String(lm35.readCelsius()));
  Serial.println("Temp (F): " + String(lm35.readFahrenheit()));
  Serial.println("AREF: " + String(lm35.readPreciseAref()));
  delay(2000);
} 
```

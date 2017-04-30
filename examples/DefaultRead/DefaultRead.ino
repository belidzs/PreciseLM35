/*
 * PreciseLM35: A simple LM35 wrapper with optional voltage calibration facility
 * Version 1.0.2 (2017-04-30)
 * Written by belidzs
 * 
 * Features selectable reference voltage. 
 * Actual AREF value is polled from MCU, eliminating inaccuracies due to changing 
 * AREF value (depleting batteries, etc)
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * See file LICENSE for further informations on licensing terms.
 *
 * DefaultRead.ino
 *
 * Uses MCU's reported Vcc voltage instead of a nominal value of 3.3V or 5V
 * which can change over time due to depleting battery, unstable power
 * supply, etc.
 *
 * Use this if you need to measure temperatures higher than 110C or 
 * other analog sensor needs to read values higher than 1.1V. 
 * Otherwise CalibratedInternalRead gives you more accurate results
 * 
 */

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

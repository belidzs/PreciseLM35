/*
 * PreciseLM35: A simple LM35 wrapper with optional voltage calibration facility
 * Version 1.0.1 (2017-04-30)
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
 * CalibratedDefaultRead.ino
 *
 * Use this if you need to measure temperatures higher than 110C or 
 * other analog sensor needs to read values higher than 1.1V. 
 * Otherwise CalibratedInternalRead gives you more accurate results
 *
 * Calibration:
 * - First run with measuredVsReadAreFratio = 1.0
 * - Use a multimeter and measure voltage on AREF pin. It should be around 3.3V or 5V 
 *   depending on your Arduino
 * - Divide this value by the displayed AREF value and use it as measuredVsReadAreFratio
 * - Run the sketch again and check if serial terminal shows correct value for AREF
 * 
 */

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

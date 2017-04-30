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
 * InternalRead.ino
 *
 * Uses maximum precision when measuring temperature by executing analogReference(INTERNAL)
 * This way LM35's output will be measured on a smaller scale (0mV - 1100mV) than 
 * standard 3.3V or 5V
 *
 * WARNING: Using internal AREF, your maximum measured temperature is limited to 
 * 1100 / 10 = 110.0C (230F)
 *
 */

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

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
 */

// stops loading this library twice
#ifndef PreciseLM35_h
#define PreciseLM35_h

// basic Arduino headers
#include "Arduino.h"

class PreciseLM35 {
  public:
    PreciseLM35(int pin);
    PreciseLM35(int pin, int analogReferenceValue);
    PreciseLM35(int pin, int analogReferenceValue, float measuredVsReadArefRatio);
    float readCelsius();
    float readFahrenheit();
    long readPreciseAref();
  private:
    void init(int pin, int analogReferenceValue, float measuredVsReadArefRatio);
    long readSystemVcc();
    int _pin;
    float _measuredVsReadArefRatio;
    int _analogReferenceValue;
};

#endif


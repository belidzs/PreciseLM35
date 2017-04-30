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
 */

#include "Arduino.h"
#include "PreciseLM35.h"

PreciseLM35::PreciseLM35(int pin) {
  init(pin, INTERNAL, 1.0);
}

PreciseLM35::PreciseLM35(int pin, int analogReferenceValue) {
  init(pin, analogReferenceValue, 1.0);
}

PreciseLM35::PreciseLM35(int pin, int analogReferenceValue, float measuredVsReadArefRatio) {
  init(pin, analogReferenceValue, measuredVsReadArefRatio);
}

void PreciseLM35::init(int pin, int analogReferenceValue, float measuredVsReadArefRatio) {
  _pin = pin;
  _measuredVsReadArefRatio = measuredVsReadArefRatio;
  _analogReferenceValue = analogReferenceValue;
  pinMode(pin, INPUT);
  analogReference(analogReferenceValue);
}

float PreciseLM35::readCelsius() {
  int readOut = map(analogRead(_pin), 0, 1023, 0, readPreciseAref());
  return readOut / 10.0;
}

float PreciseLM35::readFahrenheit() {
  return readCelsius() * 1.8 + 32;
}

long PreciseLM35::readPreciseAref() {
  long result;
  if (_analogReferenceValue == INTERNAL) {
    result = 1100 * _measuredVsReadArefRatio;
  } else {
    result = readSystemVcc() * _measuredVsReadArefRatio;
  }
  return result;
}

long PreciseLM35::readSystemVcc() {
  // Read 1.1V reference against AVcc
  // set the reference to Vcc and the measurement to the internal 1.1V reference
#if defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
  ADMUX = _BV(REFS0) | _BV(MUX4) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
#elif defined (__AVR_ATtiny24__) || defined(__AVR_ATtiny44__) || defined(__AVR_ATtiny84__)
  ADMUX = _BV(MUX5) | _BV(MUX0);
#elif defined (__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__)
  ADMUX = _BV(MUX3) | _BV(MUX2);
#else
  ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
#endif  

  delay(2); // Wait for Vref to settle
  ADCSRA |= _BV(ADSC); // Start conversion
  while (bit_is_set(ADCSRA, ADSC)); // measuring

  uint8_t low = ADCL; // must read ADCL first - it then locks ADCH  
  uint8_t high = ADCH; // unlocks both

  long result = (high << 8) | low;

  // This is only true if the 1.1V reference voltage is actually 1.1V
  result = 1125300L / result; // Calculate Vcc (in mV); 1125300 = 1.1*1023*1000
  
  return result; // Vcc in millivolts
}

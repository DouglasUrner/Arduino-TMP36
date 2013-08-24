/*
** Driver for Analog Devices TMP36 analog temperature sensor
*/

#undef DEBUG

#include "TMP36.h"

/*
** Use built-in 5.0 V analog reference voltage.
*/

TMP36::TMP36(int pin)
{
  _pin  = pin;
}

/*
** Supply something other than the default 5.0 V analog reference voltage
** on the AREF pin. Two constructors in case it is difficult to compare
** floating point values.
*/

TMP36::TMP36(int pin, int refType, float aRef)
{
  _pin  = pin;

  switch (refType) {
  case DEFAULT:
    _aRef = 5.0;
    break;
  case INTERNAL:
    _aRef = 1.1;
    break;
  case EXTERNAL:
    _aRef = aRef;
    break;
  }
  analogReference(refType);
}

float TMP36::degC()
{
  int rawA2D   = analogRead(_pin);
  float volts = (rawA2D * _aRef) / A2D_FULL_SCALE;

  /*
   * Convert voltage to temperature in degrees C. Voltage is proportional
   * to temperature with a +500 mV offset to make all in-range readings
   * postive values. A change of 1 mV equates to 1 degree C.
   *
   * degrees C = (volts - 500 mV (offset) ) * 100 (mV / degree)
   */
  float degC = (volts - 0.5) * 100;

  return degC;
}

#ifdef TMP36_FARENHEIT
float TMP36::degF()
{
  return ((TMP36::degC() * 5) / 9) + 32;
}
#endif

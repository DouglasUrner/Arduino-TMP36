/*
** Driver for Analog Devices TMP36 temperature sensor.
**
** It should not be too hard to modify this driver to support the other
** devices in this family (e.g. TMP35 and TMP37).
*/

#ifndef tmp36_h
#define tmp36_h

#include <Arduino.h>

#include "../Common/DEBUG.h"

#define A2D_FULL_SCALE 1024

class TMP36 {

 public:
  TMP36(int pin);
  TMP36(int pin, int type, float aRef);
  float degC();
  float degF();

 private:
  float _aRef;	       /* Analog reference (full scale) voltage for
			* this TMP36.  Any reasonable voltage could be
			* specified, but the most logical values would
			* be +5, +3.3, or, perhaps, +1.1
			* (INTERNAL/INTERNAL1V1). Using a value close
			* to the expected full scale reading in the
			* application will produce better resolution.
			*/
  int _pin;	       // Analog pin this TMP36 is attached to.
  float _read();       // Common read function.
};

#endif // tmp36_h

//PQ: Use this to set values by software. Used example code eeprom_update

/***
   EEPROM Update method

   Stores values read from analog input 0 into the EEPROM.
   These values will stay in the EEPROM when the board is
   turned off and may be retrieved later by another sketch.

   If a value has not changed in the EEPROM, it is not overwritten
   which would reduce the life span of the EEPROM unnecessarily.

   Released using MIT licence.
 ***/


#include <EEPROM.h>

/** the current address in the EEPROM (i.e. which byte we're going to write to next) **/
int addressON = 0;
int addressOFF = 1;
int addressCycles = 2;

void setup() {
  int ON = 30;
  int OFF = 10;
  int cycles = 3;

  /***
    Update the particular EEPROM cell.
    these values will remain there when the board is
    turned off.
  ***/
  EEPROM.update(addressON, ON);
  EEPROM.update(addressOFF, OFF);
  EEPROM.update(addressCycles, cycles);
}

void loop() {

  delay(100);
}

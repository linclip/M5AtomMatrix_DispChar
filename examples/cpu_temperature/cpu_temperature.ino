
#include "M5Atom.h"
#include "M5AtomMatrix_DispChar.h"

MatrixDispChar mdc;  // create an instance 

void setup()
{
  M5.begin(true, false, true);
  delay(10);
  
  // opening (blink) fill screen
  for(int i=0; i< 3; i++){
    mdc.fill(0x401010);  // Red
    delay(100);  
    mdc.fill(0x606010);  // Yellow
    delay(100);  
    mdc.fill(0x000000);  // Black
    delay(100);  
  }
}

void loop ()
{

  M5.update();

  uint8_t temp = temperatureRead(); // CPU temperature

  mdc.twoDigits(temp, 0xff69b4);  // Pink

  delay(1000);  
}

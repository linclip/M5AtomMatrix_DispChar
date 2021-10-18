# M5AtomMatrix_DispChar

An Arduino Library to display text in M5Stack Atom Matrix (M5Atom Matrix).

# Features
 
Display ASCII characters, two decimal digits, two hexadecimal digits, fill screen.

## example

```
#include "M5Atom.h"
#include "M5AtomMatrix_DispChar.h"

MatrixDispChar mdc;  // create an instance 

void setup(){
  M5.begin(true, false, true);
}

void loop(){

  mdc.drawChar("Hello World:) ", 0x9370db, 0, 250);  // string of characters, color, background color, delaytime
  delay(2000);

  mdc.drawChar(35, 0x00ff00 );  // ASCII code (#), color
  delay(2000);

  mdc.twoDigits(99, 0xff69b4);  // number, color
  delay(2000);

  mdc.twoHex(255, 0x606010);  // number(ff), color
  delay(2000);

  for(int i=0; i< 4; i++){
    mdc.fill(0x202020);  // Fill White
    delay(200);  
    mdc.fill(0x401010);  // Fill Red
    delay(200);  
    mdc.fill(0x000000);  // Fill Black
    delay(200);  
  }
  delay(2000);
}

```

see also **examples/demo/**

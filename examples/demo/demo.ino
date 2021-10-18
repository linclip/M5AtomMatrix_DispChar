#include "M5Atom.h"
#include "M5AtomMatrix_DispChar.h"

MatrixDispChar mdc;  // create an instance 

byte buttonpin = 39;

void blink(){
  for(int i=0; i< 4; i++){
    mdc.drawChar("*", 0x660000 ,0x404040);
    delay(100);
    mdc.drawChar("+", 0x660030 ,0x404040);
    delay(100);
  }
}

void setup()
{
  M5.begin(true, false, true);
  delay(10);

  // opening (blink) fill screen
  for(int i=0; i< 4; i++){
    mdc.fill(0x202020);  // White
    delay(80);  
    mdc.fill(0x401010);  // Red
    delay(80);  
    mdc.fill(0x000000);  // Black
    delay(80);  
  }
}

void loop ()
{

  mdc.scrollChar("M5Stack", 0xff8c00, 0, 200);
  mdc.scrollChar("Atom Matrix", 0x006666, 0, 200);
  
  // print image
  for (int i = 0; i < 4 ; i++){
    String goodface[5] =
    {
      "00000",
      "01010",
      "00000",
      "10001",
      "01110"
    };
    mdc.drawImage(goodface, 0x006666, 0);
    delay(400);
  
    String badface[5] = 
    {
      "00000",
      "01010",
      "00000",
      "01110",
      "10001"
    };
    mdc.drawImage(badface, 0x660000, 0);
    delay(400);  
  }
   
  // print string in order 文字列を1文字ずつ順に表示
  mdc.drawChar("M5Stack", 0x006666, 0, 250);  // Cyan / 2番目以降の引数は省略可
  delay(400);  
  
  // print string with scroll / 文字列をスクロール表示
  mdc.scrollChar("Atom Matrix", 0xff8c00, 0, 200);  // Orange / 2番目以降の引数は省略可
  delay(400);  

  // print single character / 文字列を1文字ずつ表示 文字をプログラム側で指定して順に表示
  char mes[] = "Atom Matrix ";
  for (int i = 0; i < sizeof(mes)-1 ; i++){
    mdc.drawChar(mes[i], 0x600060 );  // Purple
    delay(300);
    mdc.drawChar(32);  // 32: SPACE、色は省略可
    delay(40);

    if(digitalRead(buttonpin) == 0){
      blink();
      break;
    }
  }
  
  // print single character, ASCII code / 文字コードを数値で指定して一覧表示    
  for (int i = 32; i < 128 ; i++){
    mdc.drawChar(i, 0x00ff00 );  // Green
    delay(300);  
    if(digitalRead(buttonpin) == 0){
      blink();
      break;
    }
  }

  // two decimal digits / 10進数 2桁表示で -9から99まで
  for (int i = -9; i < 100 ; i++){
    mdc.twoDigits(i, 0xff69b4);  // Pink
    delay(180);  
    if(digitalRead(buttonpin) == 0){
      blink();
      break;
    }
  }
  
  //two hexadecimal digits / 16進数 2桁表示で 0x90から0xff（255）まで
  for (int i = 0x90; i < 0x100 ; i++){
    mdc.twoHex(i, 0x606010);  // Yellow
    delay(300);  
    if(digitalRead(buttonpin) == 0){
      blink();
      break;
    }
  }

  blink();

}
#include "M5Atom.h"
#include "M5AtomMatrix_DispChar.h"

MatrixDispChar::MatrixDispChar()
{
}

/*
 *  swapcolor for M5Atom 0.0.5 bug
 */
void MatrixDispChar::swapcolor(uint8_t *a, uint8_t *b){
  uint8_t tmp;
  tmp = *a;
  *a  = *b;
  *b  = tmp;
}
/*
 *  print single character (character code can be specified) 1文字を表示（文字コードを数値で指定可能）
 */
void MatrixDispChar::drawChar(const char str,  uint32_t color, uint32_t bColor){
    if(str < 32 || str > 127){
      Serial.println("Char range Error...");
      return;
    }

    uint8_t R  = color >> 16;
    uint8_t G  = (color >> 8) & 0xff;
    uint8_t B  = color & 0xff;
    uint8_t Rb  = bColor >> 16;
    uint8_t Gb  = (bColor >> 8) & 0xff;
    uint8_t Bb  = bColor & 0xff;    

    swapcolor(&R, &G);
    swapcolor(&Rb, &Gb);

    uint8_t DisBuff[2 + 5 * 5 * 3];
    DisBuff[0] = 0x05;
    DisBuff[1] = 0x05;
    int start = ((int)str -32) * 5;
    
    for (int row = 0 ; row < 5 ; row++){
      for (int i = 0; i < 5; i++){ 
        if(( FONTDATA[ start + row ] & (1 << abs(i-4))) != 0){
          DisBuff[2 + ((row) * 5 + i) * 3 + 0] = R;
          DisBuff[2 + ((row) * 5 + i) * 3 + 1] = G;
          DisBuff[2 + ((row) * 5 + i) * 3 + 2] = B;
        }
        else {
          DisBuff[2 + ((row) * 5 + i) * 3 + 0] = Rb;
          DisBuff[2 + ((row) * 5 + i) * 3 + 1] = Gb;
          DisBuff[2 + ((row) * 5 + i) * 3 + 2] = Bb;
        }
      }
    }
    M5.dis.setWidthHeight(5, 5);
    M5.dis.displaybuff(DisBuff);
}


/*
 *  print strings in order 文字列を順に表示
 */
void MatrixDispChar::drawChar(const char mes[], uint32_t color, uint32_t bColor, int delaytime){

  uint8_t DisBuff[2 + 5 * 5 * 3];
  M5.dis.setWidthHeight(5, 5);
  DisBuff[0] = 0x05;
  DisBuff[1] = 0x05;
  
  for (int j = 0; j < strlen(mes) ; j++){
    char str = mes[j];

    MatrixDispChar::drawChar(mes[j], color, bColor);  
    
    if(strlen(mes) > 1){
      delay(delaytime);
      MatrixDispChar::fill(bColor);  
      delay(50);
    }
  }
}

/*
 *  print strings with scroll 文字列をスクロール表示
 */
void MatrixDispChar::scrollChar(const char mes[], uint32_t color, uint32_t bColor, int delaytime){

  uint8_t DisBuff[2 + 5 * 5 * 3];
  M5.dis.setWidthHeight(5, 5);
  DisBuff[0] = 0x05;
  DisBuff[1] = 0x05;

  uint8_t R  = color >> 16;
  uint8_t G  = (color >> 8) & 0xff;
  uint8_t B  = color & 0xff;
  uint8_t Rb  = bColor >> 16;
  uint8_t Gb  = (bColor >> 8) & 0xff;
  uint8_t Bb  = bColor & 0xff;

  swapcolor(&R, &G);
  swapcolor(&Rb, &Gb);

  char newmes[strlen(mes) + 2] = " ";
  strcat(newmes, mes);
  strcat(newmes, " ");

  for (int i = 0; i < 25; i++)
  {
        DisBuff[2 + i * 3 + 0] = Rb;
        DisBuff[2 + i * 3 + 1] = Gb;
        DisBuff[2 + i * 3 + 2] = Bb;
  }

  for (int j = 0; j < strlen(newmes)-1 ; j++){
    char str = newmes[j];
    int start  = ((int)str -32) * 5;
    int start2 = ((int)newmes[j+1] -32) * 5;    

    for(int col = 0; col > -6; col--){

      // 1st
      for (int i = abs(col); i < 5; i++){
        for (int row = 0 ; row < 5 ; row++){
          if( (FONTDATA[ start + row ] & (1 << abs(i-4))) != 0  ){
            DisBuff[2 + ((row) * 5 + i + col) * 3 + 0] = R;
            DisBuff[2 + ((row) * 5 + i + col) * 3 + 1] = G;
            DisBuff[2 + ((row) * 5 + i + col) * 3 + 2] = B;
          } else {
            DisBuff[2 + ((row) * 5 + i + col) * 3 + 0] = Rb;
            DisBuff[2 + ((row) * 5 + i + col) * 3 + 1] = Gb;
            DisBuff[2 + ((row) * 5 + i + col) * 3 + 2] = Bb;
          }
        }
      }
      // separater
      if( col > -5 && col !=0){
        for (int row = 0 ; row < 5 ; row++){
          DisBuff[2 + ((row) * 5 + 5 + col) * 3 + 0] = Rb;
          DisBuff[2 + ((row) * 5 + 5 + col) * 3 + 1] = Gb;
          DisBuff[2 + ((row) * 5 + 5 + col) * 3 + 2] = Bb;
        }
      }
  
      // 2nd
      if( col < -1){   //  col < 0
        for (int i = 0; i < abs(col+1); i++){  //abs(col)
            for (int row = 0 ; row < 5 ; row++){
              if( (FONTDATA[ start2 + row ] & (1 << abs(i-4))) != 0 ){
                DisBuff[2 + ((row) * 5 + i + col + 6 ) * 3 + 0] = R;
                DisBuff[2 + ((row) * 5 + i + col + 6 ) * 3 + 1] = G;
                DisBuff[2 + ((row) * 5 + i + col + 6 ) * 3 + 2] = B;
              } else {
                DisBuff[2 + ((row) * 5 + i + col + 6 ) * 3 + 0] = Rb;
                DisBuff[2 + ((row) * 5 + i + col + 6 ) * 3 + 1] = Gb;
                DisBuff[2 + ((row) * 5 + i + col + 6 ) * 3 + 2] = Bb;
              }
            }
        }
      }
      M5.dis.displaybuff(DisBuff);
      delay(delaytime);
    }
  }
}

/*
 * two decimal digits 10進数で2桁表示
 */
void MatrixDispChar::twoDigits(int v, uint32_t color, uint32_t bColor){
  uint8_t DisBuff[2 + 5 * 5 * 3];
  M5.dis.setWidthHeight(5, 5);
  DisBuff[0] = 0x05;
  DisBuff[1] = 0x05;

  uint8_t R  = color >> 16;
  uint8_t G  = (color >> 8) & 0xff;
  uint8_t B  = color & 0xff;
  uint8_t Rb  = bColor >> 16;
  uint8_t Gb  = (bColor >> 8) & 0xff;
  uint8_t Bb  = bColor & 0xff;

  swapcolor(&R, &G);
  swapcolor(&Rb, &Gb);

  if(v < -9){  // -9 未満なら表示しない
    return;
  }
  int n1 = 0, n2 = 0;
  
  if (v < 0){  // - （マイナス）を表示
    n2 = 16;
  }
  else {
    n2 = floor(v % 100 /10);
  }
  n1 = abs(floor(v % 10));

  for (int i = 2; i < 25; i+=5){
        DisBuff[2 + i * 3 + 0] = Rb;
        DisBuff[2 + i * 3 + 1] = Gb;
        DisBuff[2 + i * 3 + 2] = Bb;
  }

  for (int y = 0; y < 5; y++) {
      for (int x = 0; x < 2; x++) {
          if ((NUMFONTDATA[n2][y]).substring(x, x+1) == "1" && n2 != 0) {
            DisBuff[2 + (y * 5 + x) * 3 + 0] = R;
            DisBuff[2 + (y * 5 + x) * 3 + 1] = G;
            DisBuff[2 + (y * 5 + x) * 3 + 2] = B;
          }
          else {
            DisBuff[2 + (y * 5 + x) * 3 + 0] = Rb;
            DisBuff[2 + (y * 5 + x) * 3 + 1] = Gb;
            DisBuff[2 + (y * 5 + x) * 3 + 2] = Bb;
          }
      }

      for (int z = 3; z < 5; z++) {
          if ((NUMFONTDATA[n1][y]).substring(z - 3, z-3+1) == "1") {
                DisBuff[2 + (y * 5 + z) * 3 + 0] = R;
                DisBuff[2 + (y * 5 + z) * 3 + 1] = G;
                DisBuff[2 + (y * 5 + z) * 3 + 2] = B;
          }
          else {
                DisBuff[2 + (y * 5 + z) * 3 + 0] = Rb;
                DisBuff[2 + (y * 5 + z) * 3 + 1] = Gb;
                DisBuff[2 + (y * 5 + z) * 3 + 2] = Bb;
          }
      }
      M5.dis.displaybuff(DisBuff);
  }
}

/*
 * two hexadecimal digits 16進数で2桁表示
 */
void MatrixDispChar::twoHex(int v, uint32_t color ,uint32_t bColor){
  uint8_t R  = color >> 16;
  uint8_t G  = (color >> 8) & 0xff;
  uint8_t B  = color & 0xff;
  uint8_t Rb  = bColor >> 16;
  uint8_t Gb  = (bColor >> 8) & 0xff;
  uint8_t Bb  = bColor & 0xff;

  swapcolor(&R, &G);
  swapcolor(&Rb, &Gb);

  uint8_t DisBuff[2 + 5 * 5 * 3];
  M5.dis.setWidthHeight(5, 5);
  DisBuff[0] = 0x05;
  DisBuff[1] = 0x05;
    
  if(v < -9){  // -9 未満なら表示しない
    return;
  }
  int n1 = 0, n2 = 0;
  
  if (v < 0){  // - （マイナス）を表示
    n2 = 16;
  }
  else {
    n2 = floor(v % 256 / 16);
  }
  n1 = abs(floor(v % 16));

  for (int i = 2; i < 25; i+=5){
        DisBuff[2 + i * 3 + 0] = Rb;
        DisBuff[2 + i * 3 + 1] = Gb;
        DisBuff[2 + i * 3 + 2] = Bb;
  }

  for (int y = 0; y < 5; y++) {
      for (int x = 0; x < 2; x++) {
          if ((NUMFONTDATA[n2][y]).substring(x, x+1) == "1" && n2 != 0) {
            DisBuff[2 + (y * 5 + x) * 3 + 0] = R;
            DisBuff[2 + (y * 5 + x) * 3 + 1] = G;
            DisBuff[2 + (y * 5 + x) * 3 + 2] = B;
          }
          else {
            DisBuff[2 + (y * 5 + x) * 3 + 0] = Rb;
            DisBuff[2 + (y * 5 + x) * 3 + 1] = Gb;
            DisBuff[2 + (y * 5 + x) * 3 + 2] = Bb;
          }
      }

      for (int z = 3; z < 5; z++) {
          if ((NUMFONTDATA[n1][y]).substring(z - 3, z-3+1) == "1") {
                DisBuff[2 + (y * 5 + z) * 3 + 0] = R;
                DisBuff[2 + (y * 5 + z) * 3 + 1] = G;
                DisBuff[2 + (y * 5 + z) * 3 + 2] = B;
          }
          else {
                DisBuff[2 + (y * 5 + z) * 3 + 0] = Rb;
                DisBuff[2 + (y * 5 + z) * 3 + 1] = Gb;
                DisBuff[2 + (y * 5 + z) * 3 + 2] = Bb;
          }
      }
      M5.dis.displaybuff(DisBuff);
  }
}

/*
 * draw an image
 */
void MatrixDispChar::drawImage(const String str[], uint32_t color , uint32_t bColor){
  uint8_t R  = color >> 16;
  uint8_t G  = (color >> 8) & 0xff;
  uint8_t B  = color & 0xff;
  uint8_t Rb  = bColor >> 16;
  uint8_t Gb  = (bColor >> 8) & 0xff;
  uint8_t Bb  = bColor & 0xff;

  swapcolor(&R, &G);
  swapcolor(&Rb, &Gb);

  uint8_t DisBuff[2 + 5 * 5 * 3];
  M5.dis.setWidthHeight(5, 5);
  DisBuff[0] = 0x05;
  DisBuff[1] = 0x05;

  for (int y = 0; y < 5; y++) {
      for (int x = 0; x < 5; x++) {
          if (str[y].substring(x, x+1) == "1") {
            DisBuff[2 + (y * 5 + x) * 3 + 0] = R;
            DisBuff[2 + (y * 5 + x) * 3 + 1] = G;
            DisBuff[2 + (y * 5 + x) * 3 + 2] = B;
            Serial.print("X");
          }
          else {
            DisBuff[2 + (y * 5 + x) * 3 + 0] = Rb;
            DisBuff[2 + (y * 5 + x) * 3 + 1] = Gb;
            DisBuff[2 + (y * 5 + x) * 3 + 2] = Bb;
            Serial.print(".");
          }
      }
      Serial.println("");
  }
      M5.dis.displaybuff(DisBuff);
      Serial.println("");
  
}

/*
 * fill Screen
 */
void MatrixDispChar::fill(uint32_t color)
{
  uint8_t R  = color >> 16;
  uint8_t G  = (color >> 8) & 0xff;
  uint8_t B  = color & 0xff;

  swapcolor(&R, &G);
 
  uint8_t DisBuff[2 + 5 * 5 * 3];
  M5.dis.setWidthHeight(5, 5);
  DisBuff[0] = 0x05;
  DisBuff[1] = 0x05;
  for (int i = 0; i < 25; i++)
  {
      DisBuff[2 + i * 3 + 0] = R;
      DisBuff[2 + i * 3 + 1] = G;
      DisBuff[2 + i * 3 + 2] = B;
  }
  M5.dis.displaybuff(DisBuff);

}

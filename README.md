# RoomWeatherScreen
ESP8266 and QVGA 2.2" SPI screen to show room air condition and street weather

## Why

I can

I have a home server which gather all information about sensors distributed among the home. And I have small ESP8266EX MCU and SPI QVGA 2.2" color screen. And I have time. So why not to spend it to create smalll screen for living room to show what is going on. So I did.

One of the source is modified [dust sensor VINDRIKTNING](https://github.com/katurov/VINDRIKTNING-upgrade) and it is good time to add its numbers on the always-on screen. Yep.

## Good problem to solve

Actually I have no idea how to add own font for project. I like non-standart fonts and I found one nice, but I need it in two sizes and just part with the numbers. So... I thinking is here some elegant solution to use it in my project, and I found one simple: create casse with numbers in two sizes and two colors, store 'em as a pictures and use 'em as a letters in the code. Look at it:

### To center the text on the screen
I need to know width of the resulting text, so this is method to know it:
```
uint8_t getSmallFontWidht( char *text ) {
  uint8_t FontWidht = 0;

  for (uint8_t i = 0; i < SRT_LEN; i ++) {
    switch (text[i] ) {
      case '1' :
        FontWidht = FontWidht + 10;
        break;
      case '2' :
        FontWidht = FontWidht + 20;
        break;
      case '3' :
        FontWidht = FontWidht + 18;
        break;
      case '4' :
        FontWidht = FontWidht + 18;
        break;
      
      /*
       * For every letter!
       */ 
      
      case '-' :
        FontWidht = FontWidht + 18;
        break;
      case '%' :
        FontWidht = FontWidht + 26;
        break;
      default :
        break;
    }
  }

  return FontWidht;
}

```
So I can call it: 
```
  dtostrf(badroom_pres, 6, 0, result);
  text_width = getSmallFontWidht(result);
```

### Making text with selected fonts
```
void drawBigFont( char *text, uint8_t x, uint16_t y ) {
  uint8_t FontWidht = x;

  for (uint8_t i = 0; i < SRT_LEN; i ++) {
    switch (text[i] ) {
      case '1' :
        tft.drawRGBBitmap( FontWidht, y, big_b1, 34, TEXT_BIG );
        FontWidht = FontWidht + 34;
        break;
      case '2' :
        tft.drawRGBBitmap( FontWidht, y, big_b2, 65, TEXT_BIG );
        FontWidht = FontWidht + 65;
        break;
      case '9' :
        tft.drawRGBBitmap( FontWidht, y, big_b9, 64, TEXT_BIG );
        FontWidht = FontWidht + 64;
        break;
      case '0' :
        tft.drawRGBBitmap( FontWidht, y, big_b0, 68, TEXT_BIG );
        FontWidht = FontWidht + 68;
        break;
      case '.' :
        tft.drawRGBBitmap( FontWidht, y, big_bdot, 32, TEXT_BIG );
        FontWidht = FontWidht + 32;
        break;
      case '-' :
        tft.drawRGBBitmap( FontWidht, y, big_bdash, 60, TEXT_BIG );
        FontWidht = FontWidht + 60;
        break;
      default :
        break;
    }
  }

}
```
Please note that I need a 'case block' for each character and it move the start X-point for next and so on.

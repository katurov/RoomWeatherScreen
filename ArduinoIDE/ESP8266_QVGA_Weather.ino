#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"

#include "images.h"

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>

#include <ArduinoJson.h>

/* SPI pin-out for WeMos D1 mini
 *  CLK is D5 (14)
 *  MISO is D6 (12) and not used here
 *  MOSI is D7 (13)
 *  CS is D8 (15) but in this sketch it is D2 (4) would I like to update it later?
 */
#define TFT_DC 5  // D1
#define TFT_CS 4  // D2
#define SCR_WIDTH       240
#define SCR_HEIGHT      320

#define SRT_LEN         9  // String no longer than

#define SSD "<YOUR_WIFI>"
#define SPW "<YOUR_PASS>"
#define SRV "http://192.168.0.2/json/weather/"


Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
ESP8266WiFiMulti WiFiMulti;
WiFiClient client;
HTTPClient http;
char result[SRT_LEN];
uint8_t text_start = 0;
uint8_t text_width = 0;
DynamicJsonDocument doc(2048);

const uint16_t* getImage ( String name ) {
  if (name == String("01d")) return img01d;
  if (name == String("01n")) return img01n;

  if (name == String("02d")) return img02d;
  if (name == String("02n")) return img02n;

  if (name == String("03d")) return img03d;
  if (name == String("03n")) return img03n;

  if (name == String("04d")) return img04d;
  if (name == String("04n")) return img04n;

  if (name == String("09d")) return img09d;
  if (name == String("09n")) return img09n;

  if (name == String("10d")) return img10d;
  if (name == String("10n")) return img10n;

  if (name == String("11d")) return img11d;
  if (name == String("11n")) return img11n;

  if (name == String("13d")) return img13d;
  if (name == String("13n")) return img13n;

  if (name == String("50d")) return img50d;
  if (name == String("50n")) return img50n;

  return img01d;
}

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
      case '5' :
        FontWidht = FontWidht + 18;
        break;
      case '6' :
        FontWidht = FontWidht + 19;
        break;
      case '7' :
        FontWidht = FontWidht + 15;
        break;
      case '8' :
        FontWidht = FontWidht + 18;
        break;
      case '9' :
        FontWidht = FontWidht + 19;
        break;
      case '0' :
        FontWidht = FontWidht + 20;
        break;
      case '.' :
        FontWidht = FontWidht + 10;
        break;
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

uint8_t getBigFontWidht( char *text ) {
  uint8_t FontWidht = 0;

  for (uint8_t i = 0; i < SRT_LEN; i ++) {
    switch (text[i] ) {
      case '1' :
        FontWidht = FontWidht + 34;
        break;
      case '2' :
        FontWidht = FontWidht + 65;
        break;
      case '3' :
        FontWidht = FontWidht + 61;
        break;
      case '4' :
        FontWidht = FontWidht + 59;
        break;
      case '5' :
        FontWidht = FontWidht + 62;
        break;
      case '6' :
        FontWidht = FontWidht + 64;
        break;
      case '7' :
        FontWidht = FontWidht + 50;
        break;
      case '8' :
        FontWidht = FontWidht + 61;
        break;
      case '9' :
        FontWidht = FontWidht + 64;
        break;
      case '0' :
        FontWidht = FontWidht + 68;
        break;
      case '.' :
        FontWidht = FontWidht + 32;
        break;
      case '-' :
        FontWidht = FontWidht + 60;
        break;
      default :
        break;
    }
  }

  return FontWidht;
}


void drawSmallFont( char *text, uint8_t x, uint16_t y ) {
  uint8_t FontWidht = x;

  for (uint8_t i = 0; i < SRT_LEN; i ++) {
    switch (text[i] ) {
      case '1' :
        tft.drawRGBBitmap( FontWidht, y, small_m1, 10, TEXT_SMALL );
        FontWidht = FontWidht + 10;
        break;
      case '2' :
        tft.drawRGBBitmap( FontWidht, y, small_m2, 20, TEXT_SMALL );
        FontWidht = FontWidht + 20;
        break;
      case '3' :
        tft.drawRGBBitmap( FontWidht, y, small_m3, 18, TEXT_SMALL );
        FontWidht = FontWidht + 18;
        break;
      case '4' :
        tft.drawRGBBitmap( FontWidht, y, small_m4, 18, TEXT_SMALL );
        FontWidht = FontWidht + 18;
        break;
      case '5' :
        tft.drawRGBBitmap( FontWidht, y, small_m5, 18, TEXT_SMALL );
        FontWidht = FontWidht + 18;
        break;
      case '6' :
        tft.drawRGBBitmap( FontWidht, y, small_m6, 19, TEXT_SMALL );
        FontWidht = FontWidht + 19;
        break;
      case '7' :
        tft.drawRGBBitmap( FontWidht, y, small_m7, 15, TEXT_SMALL );
        FontWidht = FontWidht + 15;
        break;
      case '8' :
        tft.drawRGBBitmap( FontWidht, y, small_m8, 18, TEXT_SMALL );
        FontWidht = FontWidht + 18;
        break;
      case '9' :
        tft.drawRGBBitmap( FontWidht, y, small_m9, 19, TEXT_SMALL );
        FontWidht = FontWidht + 19;
        break;
      case '0' :
        tft.drawRGBBitmap( FontWidht, y, small_m0, 20, TEXT_SMALL );
        FontWidht = FontWidht + 20;
        break;
      case '.' :
        tft.drawRGBBitmap( FontWidht, y, small_mdot, 10, TEXT_SMALL );
        FontWidht = FontWidht + 10;
        break;
      case '-' :
        tft.drawRGBBitmap( FontWidht, y, small_mdash, 18, TEXT_SMALL );
        FontWidht = FontWidht + 18;
        break;
      case '%' :
        tft.drawRGBBitmap( FontWidht, y, small_mpercent, 26, TEXT_SMALL );
        FontWidht = FontWidht + 26;
        break;
      default :
        break;
    }
  }

}


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
      case '3' :
        tft.drawRGBBitmap( FontWidht, y, big_b3, 61, TEXT_BIG );
        FontWidht = FontWidht + 61;
        break;
      case '4' :
        tft.drawRGBBitmap( FontWidht, y, big_b4, 59, TEXT_BIG );
        FontWidht = FontWidht + 59;
        break;
      case '5' :
        tft.drawRGBBitmap( FontWidht, y, big_b5, 62, TEXT_BIG );
        FontWidht = FontWidht + 62;
        break;
      case '6' :
        tft.drawRGBBitmap( FontWidht, y, big_b6, 64, TEXT_BIG );
        FontWidht = FontWidht + 64;
        break;
      case '7' :
        tft.drawRGBBitmap( FontWidht, y, big_b7, 50, TEXT_BIG );
        FontWidht = FontWidht + 50;
        break;
      case '8' :
        tft.drawRGBBitmap( FontWidht, y, big_b8, 61, TEXT_BIG );
        FontWidht = FontWidht + 61;
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


void setup() {
  Serial.begin( 115200 );
  Serial.println("ILI9341 Test!"); 
 
  tft.begin();
  tft.setSPISpeed(80000000);      // Check is it faster or not
  tft.setRotation( 2 );           // Upside Down
  tft.fillScreen(ILI9341_BLACK);

  WiFiMulti.addAP(SSD, SPW);

  while (WiFiMulti.run() != WL_CONNECTED) {
    delay(100);
  }

  tft.setTextColor(ILI9341_YELLOW, ILI9341_BLACK); tft.setTextSize(1);
  tft.println("Connected!");
  tft.println(WiFi.SSID());
  tft.println(WiFi.localIP());

  /*
  delay(2000);

  tft.drawLine(0, 100, tft.width(), 100, ILI9341_BLUE);
  tft.drawLine(0, 140, tft.width(), 140, ILI9341_BLUE);

  int i = tft.width() / 6;
  tft.drawLine(i  , 100, i  , 170, ILI9341_PINK);
  tft.drawLine(i*3, 100, i*3, 170, ILI9341_PINK);
  tft.drawLine(i*5, 100, i*5, 170, ILI9341_PINK);

  tft.drawLine(0, 170, tft.width(), 170, ILI9341_BLUE);
  tft.drawLine(0, 280, tft.width(), 280, ILI9341_BLUE);
  */
}

void loop() {

  http.begin(client, SRV);
  int httpCode = http.GET();

  if ( httpCode != 200 ) {
    delay(3000);
    return;
  }

  DeserializationError error = deserializeJson(doc, http.getString());

  if ( error ) {
    delay(3000);
    return;
  }

  http.end();

  int value_dust      = doc["DUST"];
  JsonArray street    = doc["STR"];
  float street_temp   = street[0];
  JsonArray badroom   = doc["BDR"];
  float badroom_temp  = badroom[0];
  float badroom_pres  = badroom[1];
  float badroom_humd  = badroom[2];
  JsonArray future    = doc["FTR"];
  float ftr1_temp     = future[0][0];
  String ftr1_icon    = future[0][1];
  float ftr2_temp     = future[1][0];
  String ftr2_icon    = future[1][1];
  float ftr3_temp     = future[2][0];
  String ftr3_icon    = future[2][1];

    
  ESP.wdtFeed();

  /*
   * Draw big numbers
   */
  tft.fillRect(0, 0, tft.width(), TEXT_BIG, ILI9341_BLACK);
   
  dtostrf(street_temp, 6, 1, result);
  text_width = getBigFontWidht(result);
  text_start = (tft.width() - text_width) / 2;
  drawBigFont( result, text_start, 0 );

  tft.fillRect(0, 282-TEXT_BIG, tft.width(), TEXT_BIG, ILI9341_BLACK);

  dtostrf(badroom_temp, 6, 1, result);
  text_width = getBigFontWidht(result);
  text_start = (tft.width() - text_width) / 2;
  drawBigFont( result, text_start, 282-TEXT_BIG );

  ESP.wdtFeed();

  /*
   * Icons of future weather
   * 
   * Let me make a guess: if rows before are about left border of the icon
   *  to center the text we have to add shift for half of the icon width
   */
  tft.fillRect(0, TEXT_BIG, tft.width(), 50 + TEXT_SMALL, ILI9341_BLACK);

  tft.drawRGBBitmap( 25, TEXT_BIG, getImage( ftr1_icon ), ICON_WIDTH, ICON_HEIGHT );
  dtostrf(ftr1_temp, 6, 0, result);
  text_width = getSmallFontWidht(result);
  text_start = 25 + ICON_WIDTH / 2 - (text_width / 2);
  drawSmallFont( result, text_start, TEXT_BIG + 47 );

  tft.drawRGBBitmap( 95, TEXT_BIG, getImage( ftr2_icon ), ICON_WIDTH, ICON_HEIGHT );
  dtostrf(ftr2_temp, 6, 0, result);
  text_width = getSmallFontWidht(result);
  text_start = 95 + ICON_WIDTH / 2 - (text_width / 2);
  drawSmallFont( result, text_start, TEXT_BIG + 47 );

  tft.drawRGBBitmap( 165, TEXT_BIG, getImage( ftr3_icon ), ICON_WIDTH, ICON_HEIGHT );
  dtostrf(ftr3_temp, 6, 0, result);
  text_width = getSmallFontWidht(result);
  text_start = 165 + ICON_WIDTH / 2 - (text_width / 2);
  drawSmallFont( result, text_start, TEXT_BIG + 47 );

  ESP.wdtFeed();

  /*
   * Okay, footer with pressure and humidity
   */
  tft.fillRect(0, 282, tft.width(), tft.height(), ILI9341_BLACK);
  dtostrf(badroom_pres, 6, 0, result);
  text_width = getSmallFontWidht(result);
  text_start = 0;
  drawSmallFont( result, text_start, 282 );

  dtostrf(badroom_humd, 6, 1, result);
  result[6] = (char)'%';
  text_width = getSmallFontWidht(result);
  text_start = tft.width() - text_width;
  drawSmallFont( result, text_start, 282 );

  /*
   * Dust sensor, levels from https://blissair.com/what-is-pm-2-5.htm
   */
  tft.setCursor(0, 0); tft.setTextSize(1);
  if (value_dust < 50) tft.setTextColor(ILI9341_GREEN, ILI9341_BLACK); 
  else if (value_dust < 100) tft.setTextColor(ILI9341_YELLOW, ILI9341_BLACK);
  else tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
  dtostrf(value_dust, 6, 0, result);
  tft.print("DUST: "); tft.print( result );

  delay(60000);

}

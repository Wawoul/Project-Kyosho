//--------------------------------------------------------------------------------------
//  Project Kyosho - 22/01/2021
//  By Ewen Paterson - Rev 1
//
//  Code for an array of sensors and leds into a RC nitro truggy
//
//  ArduinoIDE ATmega328P Micro Controller
//--------------------------------------------------------------------------------------
//////////////////////////////
// CH6 PWM Range and effects~
// Left most - 995
// Mid - 1498
// Far Right - 1986
// 1- 950-1080  -off
// 2- 1082-1210  - Blue
// 3- 1210-1340  - Red
// 4 - 1340-1470  - Yellow
// 5- 1470-1600  - White
// 6- 1600-1730  - Fade
// 7- 1730-1860  - Rainbow
// 8- 1860-1990  - Police
//////////////////////////////

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>  // Including the library of DS1820 Temperature module
#include <DallasTemperature.h>  // Including the library of DS1820 Temperature module
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define rcPin6 4   // Pin 4 Connected to CH6 of Transmitter;
#define PIN 5      // LED Pin
#define N_LEDS 4
#define ONE_WIRE_BUS 2             // Initializing the Arduino pin 2 for temperature module

OneWire ourWire(ONE_WIRE_BUS);     // Declaring a variable named our wire
DallasTemperature sensors ( &ourWire ); // Asking the Dallas temperature library to use the one wire library
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2); // LCD Setup
int tempPin = 2; //Temp Sen
int introFlag = 0;
int ch6 = 0;  // Receiver Channel 6 PPM value

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, PIN, NEO_GRB + NEO_KHZ800);

//-----------------------------------

const int frameMax = 19;

int frames[frameMax][8][3] = {
  {{0, 0, 255 }, {0, 0, 255 }, {0, 0, 0 }, {0, 0, 0 }, {0, 0, 0 }, {0, 0, 0 }, {255, 0, 0 }, {255, 0, 0 }},
  {{0, 0, 0 }, {0, 0, 0 }, {0, 0, 0 }, {0, 0, 0 }, {0, 0, 0 }, {0, 0, 0 }, {255, 0, 0 }, {255, 0, 0 }},
  {{0, 0, 0 }, {0, 0, 0 }, {0, 0, 0 }, {0, 0, 0 }, {0, 0, 0 }, {0, 0, 0 }, {0, 0, 0 }, {0, 0, 0 }},
  {{0, 0, 255 }, {0, 0, 255 }, {0, 0, 0 }, {0, 0, 0 }, {0, 0, 0 }, {0, 0, 0 }, {0, 0, 0 }, {0, 0, 0 }},
  {{0, 0, 0 }, {0, 0, 0 }, {0, 0, 0 }, {0, 0, 0 }, {0, 0, 0 }, {0, 0, 0 }, {255, 0, 0 }, {255, 0, 0 }},
  {{0, 0, 0 }, {0, 0, 0 }, {0, 0, 0 }, {0, 0, 0 }, {0, 0, 0 }, {0, 0, 0 }, {0, 0, 0 }, {0, 0, 0 }},
  {{0, 0, 255 }, {0, 0, 255 }, {0, 0, 0 }, {0, 0, 0 }, {0, 0, 0 }, {0, 0, 0 }, {0, 0, 0 }, {0, 0, 0 }},
  {{0, 0, 0 }, {0, 0, 0 }, {0, 0, 0 }, {0, 0, 0 }, {0, 0, 0 }, {0, 0, 0 }, {255, 0, 0 }, {255, 0, 0 }},
  {{0, 0, 0 }, {0, 0, 0 }, {0, 0, 0 }, {255, 255, 255}, {255, 255, 255}, {0, 0, 0 }, {0, 0, 0 }, {0, 0, 0 }},
  {{0, 0, 0 }, {0, 0, 0 }, {0, 0, 0 }, {0, 0, 0 }, {0, 0, 0 }, {0, 0, 0 }, {0, 0, 0 }, {0, 0, 0 }},
  {{0, 0, 0 }, {0, 0, 0 }, {0, 0, 0 }, {255, 255, 255}, {255, 255, 255}, {0, 0, 0 }, {0, 0, 0 }, {0, 0, 0 }},
  {{0, 0, 0 }, {0, 0, 0 }, {0, 0, 0 }, {0, 0, 0 }, {0, 0, 0 }, {0, 0, 0 }, {0, 0, 0 }, {0, 0, 0 }},
  {{0, 0, 0 }, {255, 0, 0 }, {255, 0, 0 }, {255, 0, 0 }, {255, 0, 0 }, {0, 0, 0 }, {0, 0, 0 }, {0, 0, 0 }},
  {{0, 0, 0 }, {255, 0, 0 }, {255, 0, 0}, {0, 0, 0 }, {255, 0, 0 }, {0, 0, 0 }, {255, 0, 0 }, {255, 0, 0 }},
  {{0, 0, 255 }, {0, 0, 0 }, {0, 0, 0 }, {0, 0, 0 }, {0, 0, 0 }, {0, 0, 0 }, {0, 0, 0 }, {255, 0, 0 }},
  {{255, 255, 255},{255, 255, 255},{255, 255, 255},{255, 255, 255},{255, 255, 255},{255, 255, 255},{255, 255, 255},{255, 255, 255}},
  {{0, 0, 255 }, {0, 0, 255 }, {0, 0, 0 }, {0, 0, 0 }, {0, 0, 0 }, {0, 0, 0 }, {0, 0, 0 }, {0, 0, 0 }},
  {{0, 0, 0 },{0, 0, 0 },{255, 255, 255},{255, 255, 255},{255, 255, 255},{255, 255, 255},{0, 0, 0 },{0, 0, 0 }},
  {{0, 0,  0}, {0, 0, 0 }, {255, 0, 0}, {255, 0, 0 }, {255, 0, 0 }, {255, 0, 0 }, {0, 0, 0 }, {0, 0, 0 }}
    };

int durations[frameMax] = {1000, 100, 100, 50, 50, 10, 50, 50, 50,40,50,40,100,100,100,20,40,20,100};
int frameCurrent = 0;

//-----------------------------------
// SETUP
//-----------------------------------

void setup() {
 lcd.init();    //LCD Screen
 lcd.backlight(); //LCD Screen
 sensors.begin(); //Temp Sensor
 pinMode(3, INPUT); //Fuel Sensor
 pinMode(rcPin6, INPUT); //CH6 Reader
 strip.begin(); //LED Start
 strip.show(); //Initialize all pixels to 'off'
 strip.setBrightness(10); //Sets LEDs brightness
}

//-----------------------------------
// LOOP
//-----------------------------------

void loop() {
 //Start-up Display
 if (introFlag == 0){ 
 lcd.clear();
 lcd.setCursor(0, 0);      // start to print at the first row
 lcd.print("   - KYOSHO -");
 lcd.setCursor(0, 1);
 lcd.print("* THE KAMIKAZE *");
 delay(3000);  
 lcd.clear();
 introFlag = 1;
 }else 

 //Fuel Display                                    
 lcd.setCursor(0, 0);
 if (digitalRead(3) == HIGH) {
  lcd.print("Fuel  : LOW");
 } else {
  lcd.print("Fuel  : OK ");
 }
 
 //Temp Display    
 sensors.requestTemperatures();
 lcd.setCursor(0, 1);      // start to print at the first row
 lcd.print("Engine: ");
 lcd.print(sensors.getTempCByIndex(0), 1);    // print the temperature in Celsius
 lcd.print((char)223);      // print ° character
 lcd.print("C");
 delay(1000);

 //CH6 LED control
 ch6 = pulseIn(rcPin6, HIGH, 20000);  // (Pin, State, Timeout)
 //1- 950-1080 - off
 if (ch6 >= 950 && ch6 <= 1080) {
   for (int i = 0; i < N_LEDS; ++i)
      {
      strip.setPixelColor(i, 0, 0, 0); //CLEAR
      }
      strip.show();
    }else
 //2- 1082-1210  - Blue
 if (ch6 >= 1082 && ch6 <= 1210) {
    for (int i = 0; i < N_LEDS; ++i)
      {
      strip.setPixelColor(i, 0, 0, 255); //Blue
      }
      strip.show();
    }else
 //3- 1210-1340 - Red
 if (ch6 >= 1210 && ch6 <= 1340) {
    for (int i = 0; i < N_LEDS; ++i)
      {
      strip.setPixelColor(i, 255, 0, 0); //Red
      }
      strip.show();
    }else
 //4- 1340-1470 - Yellow
 if (ch6 >= 1340 && ch6 <= 1471) {
    for (int i = 0; i < N_LEDS; ++i)
      {
      strip.setPixelColor(i, 255, 255, 0); //Yellow
      }
      strip.show();
    }
  //5- 1470-1600 - v
  if (ch6 >= 1470 && ch6 <= 1600) {
   for (int i = 0; i < N_LEDS; ++i)
      {
      strip.setPixelColor(i, 255, 255, 255); //White
      }
      strip.show();
    }else
 //6- 1600-1730 - Fade
 if (ch6 >= 1600 && ch6 <= 1730) {
     RGBLoop();
    }else
 //7- 1730-1860 - Rainbow Cycle
 if (ch6 >= 1730 && ch6 <= 1860) {
    rainbowCycle(1);
    }else
 //8- 1860-1990 - Police
 if (ch6 >= 1860 && ch6 <= 1990) {
    police1(strip.Color(255,   0,   0), durations[frameCurrent]);
    frameCurrent++;
    if (frameCurrent >= frameMax) frameCurrent = 0;
    }
}

//-----------------------------------
// Class
//-----------------------------------

void showStrip() {
 #ifdef ADAFRUIT_NEOPIXEL_H
   // NeoPixel
   strip.show();
 #endif
 #ifndef ADAFRUIT_NEOPIXEL_H
   // FastLED
   FastLED.show();
 #endif
}

void setPixel(int Pixel, byte red, byte green, byte blue) {
 #ifdef ADAFRUIT_NEOPIXEL_H
   // NeoPixel
   strip.setPixelColor(Pixel, strip.Color(red, green, blue));
 #endif
 #ifndef ADAFRUIT_NEOPIXEL_H
   // FastLED
   leds[Pixel].r = red;
   leds[Pixel].g = green;
   leds[Pixel].b = blue;
 #endif
}

void setAll(byte red, byte green, byte blue) {
  for(int i = 0; i < N_LEDS; i++ ) {
    setPixel(i, red, green, blue);
  }
  showStrip();
}

//Rainbow Cycle LED Pattern
void rainbowCycle(int SpeedDelay) {
  byte *c;
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< N_LEDS; i++) {
      c=Wheel(((i * 256 / N_LEDS) + j) & 255);
      setPixel(i, *c, *(c+1), *(c+2));
    }
    showStrip();
    delay(SpeedDelay);
  }
}
byte * Wheel(byte WheelPos) {
  static byte c[3];
  if(WheelPos < 85) {
   c[0]=WheelPos * 3;
   c[1]=255 - WheelPos * 3;
   c[2]=0;
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   c[0]=255 - WheelPos * 3;
   c[1]=0;
   c[2]=WheelPos * 3;
  } else {
   WheelPos -= 170;
   c[0]=0;
   c[1]=WheelPos * 3;
   c[2]=255 - WheelPos * 3;
  }
  return c;
}

//Fade LED Pattern
void RGBLoop(){
  for(int j = 0; j < 3; j++ ) {
    // Fade IN
    for(int k = 0; k < 256; k++) {
      switch(j) {
        case 0: setAll(k,0,0); break;
        case 1: setAll(0,k,0); break;
        case 2: setAll(0,0,k); break;
      }
      showStrip();
      delay(3);
    }
    // Fade OUT
    for(int k = 255; k >= 0; k--) {
      switch(j) {
        case 0: setAll(k,0,0); break;
        case 1: setAll(0,k,0); break;
        case 2: setAll(0,0,k); break;
      }
      showStrip();
      delay(3);
    }
  }
}

//Police LED Pattern
void police1(uint32_t color, int wait) {
  for (int i = 0; i < 8; i++) { // For each pixel in strip...
    strip.setPixelColor(i, strip.Color(frames[frameCurrent][i][0],frames[frameCurrent][i][1],frames[frameCurrent][i][2]));         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
  }
  delay(wait);                           //  Pause for a moment
}

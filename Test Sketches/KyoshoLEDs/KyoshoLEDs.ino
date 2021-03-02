//--------------------------------------------------------------------------------------
//  Project Kyosho - 29/01/2021
//  By Ewen Paterson - Rev 4
//
//  Code for leds in a RC nitro truggy
//
//  ArduinoIDE ATmega328P Micro Controller
//--------------------------------------------------------------------------------------
//////////////////////////////
// CH6 PWM Range - LED effects~
// Top - 995-996
// Mid - 1490-1498
// Bot - 1985-1991
// 1- 950-1080  -off
// 2- 1082-1210  - Blue
// 3- 1210-1340  - Red
// 4 - 1340-1470  - Yellow
// 5- 1470-1600  - White


// 6- 1600-1730  - Fade
// 7- 1730-1860  - Rainbow
// 8- 1860-1990  - Police
//
//CH5 PWM Range - LED Static colours~
//Top - 995-996
//Mid - 1450-1456
//Bot - 1988-1995
//
//CH4 PWM Range - Off>Head/Tail>LED Brightness~
//Bot - 995-996
//Mid - 1490-1498
//Top - 1985-1991
//
//CH2 (Throttle)PWM Range~
//Idle - 1490-1496
//Break - 1496-1991
//Accelerate - 995-1490
//////////////////////////////

#include <Adafruit_NeoPixel.h>
#define N_LEDS 44  // Num of Under LEDS

int ledHead = 6; // Head light LEDs
int ledTail = 7; // Tail light LEDs

byte PWM_PIN1 = 3; // Pin D3 onnected to CH5 of receiver
byte PWM_PIN2 = 10; // Pin D10 Connected to CH2 of receiver
byte PWM_PIN3 = 2; // Pin D2 Connected to CH4 of receiver
byte PWM_PIN4 = 4; // Pin D4 Connected to CH6 of receiver

int pwm_value1;
int pwm_value2;
int pwm_value3;
int pwm_value4;

const int ledPin5 = 5; // LED Strip
const int ledPin7 = 7; // Head light LEDs
const int ledPin6 = 6; // Tail light LEDs

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, ledPin5, NEO_GRB + NEO_KHZ800); // Under LEDs

//-----------------------------------
// Police LED Effect
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
  {{255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}},
  {{0, 0, 255 }, {0, 0, 255 }, {0, 0, 0 }, {0, 0, 0 }, {0, 0, 0 }, {0, 0, 0 }, {0, 0, 0 }, {0, 0, 0 }},
  {{0, 0, 0 }, {0, 0, 0 }, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {0, 0, 0 }, {0, 0, 0 }},
  {{0, 0,  0}, {0, 0, 0 }, {255, 0, 0}, {255, 0, 0 }, {255, 0, 0 }, {255, 0, 0 }, {0, 0, 0 }, {0, 0, 0 }}
};

int durations[frameMax] = {1000, 100, 100, 50, 50, 10, 50, 50, 50, 40, 50, 40, 100, 100, 100, 20, 40, 20, 100};
int frameCurrent = 0;

//-----------------------------------
// SETUP
//-----------------------------------

void setup() {
  strip.begin(); //Under LED Start
  strip.show(); //Initialize all pixels to 'off'
  strip.setBrightness(10); //Sets LEDs brightness

  pinMode(PWM_PIN1, INPUT);
  pinMode(PWM_PIN2, INPUT);
  pinMode(PWM_PIN3, INPUT);
  pinMode(PWM_PIN4, INPUT);

  pinMode(ledPin5, OUTPUT); // LED Strip
  pinMode(ledPin6, OUTPUT); // Tail light LEDs
  pinMode(ledPin7, OUTPUT); // Head light LEDs

  Serial.begin(115200);
}

//-----------------------------------
// LOOP
//-----------------------------------

void loop() {

  pwm_value1 = pulseIn(PWM_PIN1, HIGH); // Pin D3 onnected to CH5 of receiver
  pwm_value2 = pulseIn(PWM_PIN2, HIGH); // Pin D10 Connected to CH2 of receiver
  pwm_value3 = pulseIn(PWM_PIN3, HIGH); // Pin D2 Connected to CH4 of receiver
  pwm_value4 = pulseIn(PWM_PIN4, HIGH); // Pin D4 Connected to CH6 of receiver

  if (pwm_value1 > 1470) {
    digitalWrite(ledPin5, LOW);
    Serial.println(pwm_value1);
                      for (int i = 0; i < N_LEDS; ++i)
                      {
                        strip.setPixelColor(i, 0, 0, 0); 
                      }
                      strip.show();
                    }
                  
  else {
    digitalWrite(ledPin5, LOW);
     for (int i = 0; i < N_LEDS; ++i)
                      {
                        strip.setPixelColor(i, 255, 255, 255); //White
                      }
                      strip.show();
                    }
                    
  if (pwm_value2 >= 1500) {
    digitalWrite(ledPin7, HIGH);  // turn brake light on
    Serial.println(pwm_value2);
  }
  else {
    digitalWrite(ledPin7, LOW);
  }
  if (pwm_value3 > 1470) {
    digitalWrite(ledPin6, HIGH);
    Serial.println(pwm_value3);
  }
  else {
    digitalWrite(ledPin6, LOW);
  }
}

//-----------------------------------
// Class
//-----------------------------------
//
//void ledStatic() {
//ch5 = pulseIn(rcPin5, HIGH, 20000);  // (Pin, State, Timeout) //Effect
// //1- 950-1080 - off
// if (ch5 >= 950 && ch5 <= 1080) {
//      ledUnderFlagCH5 = 0;
//      ledUnderFlagCH6 = 1;
// }
// //2- 1082-1210  - White
// if (ch5 >= 1082 && ch5 <= 1210) {
//    for (int i = 0; i < N_LEDS; ++i)
//      {
//      strip.setPixelColor(i, 255, 255, 255); //White
//      }
//      strip.show();
//    }
// //3- 1210-1340 - Blue
// if (ch5 >= 1210 && ch5 <= 1340) {
//    for (int i = 0; i < N_LEDS; ++i)
//      {
//      strip.setPixelColor(i, 0, 0, 255); //Blue
//      }
//      strip.show();
//    }
// //4- 1340-1470 - RED
// if (ch5 >= 1340 && ch5 <= 1471) {
//    for (int i = 0; i < N_LEDS; ++i)
//      {
//      strip.setPixelColor(i, 255, 0, 0); //RED
//      }
//      strip.show();
//    }
//  //5- 1470-1600 - GREEN
//  if (ch5 >= 1470 && ch5 <= 1600) {
//   for (int i = 0; i < N_LEDS; ++i)
//      {
//      strip.setPixelColor(i, 0, 255, 0); //GREEN
//      }
//      strip.show();
//    }
// //6- 1600-1730 -
// if (ch5 >= 1600 && ch5 <= 1730) {
//     for (int i = 0; i < N_LEDS; ++i)
//      {
//      strip.setPixelColor(i, 144, 250, 14); //Yellow
//      }
//      strip.show();
//    }
// //7- 1730-1860 - YELLOW
// if (ch5 >= 1730 && ch5 <= 1860) {
//    for (int i = 0; i < N_LEDS; ++i)
//      {
//      strip.setPixelColor(i, 255, 255, 0); //Yellow
//      }
//      strip.show();
//    }
// //8- 1860-1990 -
// if (ch5 >= 1860 && ch5 <= 1990) {
//     for (int i = 0; i < N_LEDS; ++i)
//      {
//      strip.setPixelColor(i, 54, 201, 154);
//      }
//      strip.show();
//    }
//}
//
////CH6 LED control
//void ledEffect() {
// ch6 = pulseIn(rcPin6, HIGH, 20000);  // (Pin, State, Timeout)
// //1- 950-1080 - off
// if (ch6 >= 950 && ch6 <= 1080) {
//      ledUnderFlagCH5 = 1;
//      ledUnderFlagCH6 = 0;
// }
// //2- 1082-1210  - Blue
// if (ch6 >= 1082 && ch6 <= 1210) {
//    for (int i = 0; i < N_LEDS; ++i)
//      {
//      strip.setPixelColor(i, 0, 0, 255); //Blue
//      }
//      strip.show();
//    }
// //3- 1210-1340 - Red
// if (ch6 >= 1210 && ch6 <= 1340) {
//    for (int i = 0; i < N_LEDS; ++i)
//      {
//      strip.setPixelColor(i, 255, 0, 0); //Red
//      }
//      strip.show();
//    }
// //4- 1340-1470 - Yellow
// if (ch6 >= 1340 && ch6 <= 1471) {
//    for (int i = 0; i < N_LEDS; ++i)
//      {
//      strip.setPixelColor(i, 255, 255, 0); //Yellow
//      }
//      strip.show();
//    }
//  //5- 1470-1600 - v
//  if (ch6 >= 1470 && ch6 <= 1600) {
//   for (int i = 0; i < N_LEDS; ++i)
//      {
//      strip.setPixelColor(i, 255, 255, 255); //White
//      }
//      strip.show();
//    }
// //6- 1600-1730 - Fade
// if (ch6 >= 1600 && ch6 <= 1730) {
//     RGBLoop();
//    }
// //7- 1730-1860 - Rainbow Cycle
// if (ch6 >= 1730 && ch6 <= 1860) {
//    rainbowCycle(1);
//    }
// //8- 1860-1990 - Police
// if (ch6 >= 1860 && ch6 <= 1990) {
//    police1(strip.Color(255,   0,   0), durations[frameCurrent]);
//    frameCurrent++;
//    if (frameCurrent >= frameMax) frameCurrent = 0;
//     }
//   }
//
//
//
//void showStrip() {
// #ifdef ADAFRUIT_NEOPIXEL_H
//   // NeoPixel
//   strip.show();
// #endif
//}
//
//void setPixel(int Pixel, byte red, byte green, byte blue) {
// #ifdef ADAFRUIT_NEOPIXEL_H
//   // NeoPixel
//   strip.setPixelColor(Pixel, strip.Color(red, green, blue));
// #endif
//}
//
//void setAll(byte red, byte green, byte blue) {
//  for(int i = 0; i < N_LEDS; i++ ) {
//    setPixel(i, red, green, blue);
//  }
//  showStrip();
//}
//
////Rainbow Cycle LED Pattern
//void rainbowCycle(int SpeedDelay) {
//  byte *c;
//  uint16_t i, j;
//
//  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
//    for(i=0; i< N_LEDS; i++) {
//      c=Wheel(((i * 256 / N_LEDS) + j) & 255);
//      setPixel(i, *c, *(c+1), *(c+2));
//    }
//    showStrip();
//    delay(SpeedDelay);
//  }
//}
//byte * Wheel(byte WheelPos) {
//  static byte c[3];
//  if(WheelPos < 85) {
//   c[0]=WheelPos * 3;
//   c[1]=255 - WheelPos * 3;
//   c[2]=0;
//  } else if(WheelPos < 170) {
//   WheelPos -= 85;
//   c[0]=255 - WheelPos * 3;
//   c[1]=0;
//   c[2]=WheelPos * 3;
//  } else {
//   WheelPos -= 170;
//   c[0]=0;
//   c[1]=WheelPos * 3;
//   c[2]=255 - WheelPos * 3;
//  }
//  return c;
//}
//
////Fade LED Pattern
//void RGBLoop(){
//  for(int j = 0; j < 3; j++ ) {
//    // Fade IN
//    for(int k = 0; k < 256; k++) {
//      switch(j) {
//        case 0: setAll(k,0,0); break;
//        case 1: setAll(0,k,0); break;
//        case 2: setAll(0,0,k); break;
//      }
//      showStrip();
//      delay(3);
//    }
//    // Fade OUT
//    for(int k = 255; k >= 0; k--) {
//      switch(j) {
//        case 0: setAll(k,0,0); break;
//        case 1: setAll(0,k,0); break;
//        case 2: setAll(0,0,k); break;
//      }
//      showStrip();
//      delay(3);
//    }
//  }
//}
//
//
////Police LED Pattern
//void police1(uint32_t color, int wait) {
//  for (int i = 0; i < 8; i++) { // For each pixel in strip...
//    strip.setPixelColor(i, strip.Color(frames[frameCurrent][i][0],frames[frameCurrent][i][1],frames[frameCurrent][i][2]));         //  Set pixel's color (in RAM)
//    strip.show();                          //  Update strip to match
//  }
//  delay(wait);                           //  Pause for a moment
//}

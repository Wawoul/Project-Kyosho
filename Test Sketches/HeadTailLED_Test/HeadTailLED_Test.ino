//--------------------------------------------------------------------------------------
//  Project Kyosho - 25/01/2021
//  By Ewen Paterson - Rev 2
//
//  Code for an array of sensors and leds into a RC nitro truggy
//
//  ArduinoIDE ATmega328P Micro Controller
//--------------------------------------------------------------------------------------
//////////////////////////////
// CH6 PWM Range and effects~
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
//CH5 PWM Range and effects~
//Top - 995-996
//Mid - 1450-1456
//Bot - 1988-1995
//
//CH4 PWM Range and effects~
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
#ifdef __AVR__
#include <avr/power.h>
#endif

#define rcPin6 4   // Pin D4 Connected to CH6 of Transmitter;
#define rcPin5 6   // Pin D6 onnected to CH5 of Transmitter;
#define rcPin4 7   // Pin D7 Connected to CH4 of Transmitter;
#define rcPin2 10   // Pin D10 Connected to CH2 of Transmitter;
#define PINU 5      // LED Pin D5
#define PINHT 8      // LED Pin D8
#define N_LEDS 4  // Num of Under LEDS
#define N_HTLEDS 4 // Num of Head/Tail LEDS

int tempPin = 2; //Temp Sen
int introFlag = 0;
int ch6 = 0;  // Receiver Channel 6 PPM value
int ch5 = 0;  // Receiver Channel 6 PPM value
int ch4 = 0;  // Receiver Channel 6 PPM value
int ch2 = 0;  // Receiver Channel 6 PPM value

Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, PINU, NEO_GRB + NEO_KHZ800); // Under LEDs


//-----------------------------------
// SETUP
//-----------------------------------

void setup() {
 pinMode(rcPin6, INPUT); //CH6 Reader
 pinMode(rcPin5, INPUT); //CH5 Reader
 pinMode(rcPin4, INPUT); //CH4 Reader
 strip.begin(); //Under LED Start
 stripht.begin(); //Head/Tail LED Start
 strip.show(); //Initialize all pixels to 'off'
 stripht.show(); //Initialize all pixels to 'off'
 strip.setBrightness(10); //Sets LEDs brightness
 stripht.setBrightness(10); //Sets LEDs brightness
}

//-----------------------------------
// LOOP
//-----------------------------------

void loop() {

//-----------------------------------
 //CH2, CH4, CH5 LED control
  ch4 = pulseIn(rcPin4, HIGH, 20000);  // (Pin, State, Timeout) //Brightness
  if (ch4 >= 950 && ch4 <= 1000) {
        stripht.setBrightness(10); //Sets LEDs brightness
    }
  if (ch4 >= 1450 && ch4 <= 1550) { //2- 1490-1498  - High Beam Head & Tail
        stripht.setBrightness(100); //Sets LEDs brightness        
    }
   if (ch4 >= 1950 && ch4 <= 2000) {  //3- 1985-1991 - High Beam ALL
      stripht.setBrightness(100); //Sets LEDs brightness
      strip.setBrightness(100); //Sets LEDs brightness
    }
    
  ch2 = pulseIn(rcPin2, HIGH, 20000);  // (Pin, State, Timeout) //Break
  if (ch2 >= 1500) {
    stripht.setPixelColor(1, 255, 0, 0); //Red
    stripht.setPixelColor(2, 255, 0, 0); //Red
    stripht.show();
   }
   

 ch5 = pulseIn(rcPin5, HIGH, 20000);  // (Pin, State, Timeout) //Effect
 //1- 950-1080 - off
 if (ch5 >= 950 && ch5 <= 1080) {
   for (int i = 0; i < N_HTLEDS; ++i) {
      stripht.setPixelColor(i, 0, 0, 0); //CLEAR
      }
      stripht.show();
    }
    
 //2- 1082-1210  - White
 if (ch5 >= 1082 && ch5 <= 1210) {
    for (int i = 0; i < N_HTLEDS; ++i)
      {
      stripht.setPixelColor(i, 255, 255, 255); //White
      }
      stripht.show();
    }
}

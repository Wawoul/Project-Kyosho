//--------------------------------------------------------------------------------------
//  Project Kyosho - 12/03/2021
//  By Ewen Paterson - Rev 5.1
//
//  Code for fuel and temp sensor fitted to a RC nitro truggy
//  Including RGB Leds and led head/tail lights
//
//  ArduinoIDE ATmega328P Micro Controller
//--------------------------------------------------------------------------------------

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>  // Including the library of DS1820 Temperature module
#include <DallasTemperature.h>  // Including the library of DS1820 Temperature module
#include <Adafruit_NeoPixel.h>
#define ONE_WIRE_BUS 8             // Initializing the Arduino pin 8 for temperature module

OneWire ourWire(ONE_WIRE_BUS);     // Declaring a variable named our wire
DallasTemperature sensors ( &ourWire ); // Asking the Dallas temperature library to use the one wire library
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2); // LCD Setup
int tempPin = 8; //Temp Sen
int introFlag = 0;

#define N_LEDS 46  // Num of Under LEDS

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
Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, ledPin5, NEO_GRB + NEO_KHZ800); // Under LEDs

//-----------------------------------
// SETUP
//-----------------------------------

void setup() {
 lcd.init();    //LCD Screen
 lcd.backlight(); //LCD Screen
 sensors.begin(); //Temp Sensor
 pinMode(9, INPUT); //Fuel Sensor

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
 }

//-----------------------------------
// //Fuel Display                                    
 lcd.setCursor(0, 0);
 if (digitalRead(9) == HIGH) {
  lcd.print("Fuel  : LOW");
 } else {
  lcd.print("Fuel  : OK ");
 }

////-----------------------------------
// //Temp Display    
 sensors.requestTemperatures();
 lcd.setCursor(0, 1);      // start to print at the first row
 lcd.print("Engine: ");
 lcd.print(sensors.getTempCByIndex(0)-7, 1);    // print the temperature in Celsius
 lcd.print((char)223);      // print ° character
 lcd.print("C");
 //delay(500);


  pwm_value1 = pulseIn(PWM_PIN1, HIGH); // Pin D3 onnected to CH5 of receiver
  pwm_value2 = pulseIn(PWM_PIN2, HIGH); // Pin D10 Connected to CH2 of receiver
  pwm_value3 = pulseIn(PWM_PIN3, HIGH); // Pin D2 Connected to CH4 of receiver
  pwm_value4 = pulseIn(PWM_PIN4, HIGH); // Pin D4 Connected to CH6 of receiver

  // CH5 signal
  if (pwm_value1 < 1050 && pwm_value4 < 1050) {
    digitalWrite(ledPin5, LOW);
    Serial.println(pwm_value1);
                      for (int i = 0; i < N_LEDS; ++i)
                      {
                        strip.setPixelColor(i, 0, 0, 0); 
                      }
                      strip.show();
                    }
                  
  else if (pwm_value1 > 1101 && pwm_value1 < 1200) {
    digitalWrite(ledPin5, LOW);
    Serial.println(pwm_value1);
                      for (int i = 0; i < N_LEDS; ++i)
                      {
                        strip.setPixelColor(i, 0, 0, 255); //Blue
                      }
                      strip.show();
                    }
  else if (pwm_value1 > 1201 && pwm_value1 < 1400) {
      digitalWrite(ledPin5, LOW);
       for (int i = 0; i < N_LEDS; ++i)
                        {
                          strip.setPixelColor(i, 100, 100, 0); //Yellow
                        }
                        strip.show();
                      }
  else if (pwm_value1 > 1401 && pwm_value1 < 1600) {
      digitalWrite(ledPin5, LOW);
       for (int i = 0; i < N_LEDS; ++i)
                        {
                          strip.setPixelColor(i, 255, 0, 0); //Red
                        }
                        strip.show();
                      }
  else if (pwm_value1 > 1601 && pwm_value1 < 1800) {
      digitalWrite(ledPin5, LOW);
       for (int i = 0; i < N_LEDS; ++i)
                        {
                          strip.setPixelColor(i, 0, 255, 0); //Green
                        }
                        strip.show();
                      }
  else if (pwm_value1 > 1801 && pwm_value1 < 1995) {
      digitalWrite(ledPin5, LOW);
       for (int i = 0; i < N_LEDS; ++i)
                        {
                          strip.setPixelColor(i, 255, 255, 255); //White
                        }
                        strip.show();
   }

  // CH6 signal
  if (pwm_value4 < 1100 && pwm_value1 < 1100) {
    digitalWrite(ledPin5, LOW);
    Serial.println(pwm_value1);
                      for (int i = 0; i < N_LEDS; ++i)
                      {
                        strip.setPixelColor(i, 0, 0, 0); 
                      }
                      strip.show();
                    }
  else if (pwm_value4 > 1200 && pwm_value4 < 1500) {
      digitalWrite(ledPin5, LOW);
      PoliceLights(50);   // Police effect
                        }
  else if (pwm_value4 > 1501 && pwm_value4 < 1750) {
      digitalWrite(ledPin5, LOW);
      CylonBounce(0, 0, 0xff, 4, 10, 50);   //Cylon effect
                        }
  else if (pwm_value4 > 1751 && pwm_value4 < 1995) {
      digitalWrite(ledPin5, LOW);
      rainbowCycle(20);   //Rainbow effect
   }

  // Break Light signal                  
  if (pwm_value2 >= 1500) {
    digitalWrite(ledPin7, HIGH);  // turn brake light on
    Serial.println(pwm_value2);
  }
  else {
    digitalWrite(ledPin7, LOW);
  }

  // CH4 signal 
  if (pwm_value3 > 1470 && pwm_value3 < 1500) {  
    digitalWrite(ledPin6, HIGH);
    Serial.println(pwm_value3);
  }
  else if (pwm_value3 > 1500) {
    digitalWrite(ledPin6, HIGH);
    digitalWrite(ledPin7, HIGH);
    delay(500);
    digitalWrite(ledPin6, LOW);
    digitalWrite(ledPin7, LOW);
    Serial.println(pwm_value3);
  }
  else {
    digitalWrite(ledPin6, LOW);
  }
}

/////////////////////////////
// Effect Classes

// Rainbow effect
void rainbowCycle(int SpeedDelay) {
  byte *c;
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< N_LEDS; i++) {
      c=Wheel(((i * 256 / N_LEDS) + j) & 255);
      strip.setPixelColor(i, *c, *(c+1), *(c+2));
    }
    strip.show();
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

// Fade In and Fade Out effect
void setAll(byte red, byte green, byte blue) {
  for(int i = 0; i < N_LEDS; i++ ) {
    strip.setPixelColor(i, red, green, blue);
  }
  strip.show();
}

void RGBLoop(){
  for(int j = 0; j < 3; j++ ) {
    // Fade IN
    for(int k = 0; k < 256; k++) {
      switch(j) {
        case 0: setAll(k,0,0); break;
        case 1: setAll(0,k,0); break;
        case 2: setAll(0,0,k); break;
      }
      strip.show();
      delay(3);
    }
    // Fade OUT
    for(int k = 255; k >= 0; k--) {
      switch(j) {
        case 0: setAll(k,0,0); break;
        case 1: setAll(0,k,0); break;
        case 2: setAll(0,0,k); break;
      }
      strip.show();
      delay(3);
    }
  }
}

// Cylon effect
void CylonBounce(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay){

  for(int i = 0; i < N_LEDS-EyeSize-2; i++) {
    setAll(0,0,0);
    strip.setPixelColor(i, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize; j++) {
      strip.setPixelColor(i+j, red, green, blue);
    }
    strip.setPixelColor(i+EyeSize+1, red/10, green/10, blue/10);
    strip.show();
    delay(SpeedDelay);
  }

  delay(ReturnDelay);

  for(int i = N_LEDS-EyeSize-2; i > 0; i--) {
    setAll(0,0,0);
    strip.setPixelColor(i, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize; j++) {
      strip.setPixelColor(i+j, red, green, blue);
    }
    strip.setPixelColor(i+EyeSize+1, red/10, green/10, blue/10);
    strip.show();
    delay(SpeedDelay);
  }
 
  delay(ReturnDelay);
}

// PoliceLights
void PoliceLights(int fDelay){
for (int i = 0; i < 2; ++i) {
  for (int i = 0; i < N_LEDS/2; ++i)
                      {
                        strip.setPixelColor(i, 37, 0, 224); 
                      }
                      strip.show();
                      delay(fDelay);
  for (int i = 0; i < N_LEDS; ++i)
                      {
                        strip.setPixelColor(i, 0, 0, 0); 
                      }
                      strip.show();
                      delay(fDelay);
  for (int i = 0; i < N_LEDS/2; ++i)
                      {
                        strip.setPixelColor(i, 37, 0, 224); 
                      }
                      strip.show();
                      delay(fDelay);
  for (int i = 0; i < N_LEDS; ++i)
                      {
                        strip.setPixelColor(i, 0, 0, 0); 
                      }
                      strip.show();
                      delay(fDelay);
  for (int i = 0; i < N_LEDS; ++i)
                      {
                        strip.setPixelColor(i+23, 37, 0, 224); 
                      }
                      strip.show();
                      delay(fDelay);
  for (int i = 0; i < N_LEDS; ++i)
                      {
                        strip.setPixelColor(i, 0, 0, 0); 
                      }
                      strip.show();
                      delay(fDelay);
  for (int i = 0; i < N_LEDS/2; ++i)
                      {
                        strip.setPixelColor(i+23, 37, 0, 224); 
                      }
                      strip.show();
                      delay(fDelay);
  for (int i = 0; i < N_LEDS; ++i)
                      {
                        strip.setPixelColor(i, 0, 0, 0); 
                      }
                      strip.show();
  }
}

//////////////////////////////
// Channel Values:
// CH6 PWM Range - LED effects~
//Top - 995-1100 - OFF
//Mid - 1251-1500 - PoliceLights
//Mid - 1501-1750 - CylonBounce
//Bot - 1751-1995 - Rainbow
//
//CH5 PWM Range - LED Static colours~
//Top - 995-1100 - OFF
//Mid - 1101-1200 - Blue
//Mid - 1201-1400 - Yellow
//Mid - 1401-1600 - Red
//Mid - 1601-1800 - Green
//Bot - 1801-1995 - White
//
//CH4 PWM Range - Off>Head Lights/Hazards~
//Bot - 995-996
//Mid - 1490-1498
//Top - 1985-1991
//
//CH2 (Throttle)PWM Range~
//Idle - 1490-1496
//Break - 1496-1991
//Accelerate - 995-1490
//////////////////////////////

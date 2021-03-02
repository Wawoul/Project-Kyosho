//--------------------------------------------------------------------------------------
//  Project Kyosho - 29/01/2021
//  By Ewen Paterson - Rev 4
//
//  Code for fuel and temp sensor fitted to a RC nitro truggy
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
 lcd.print(sensors.getTempCByIndex(0), 1);    // print the temperature in Celsius
 lcd.print((char)223);      // print ° character
 lcd.print("C");
 //delay(500);


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

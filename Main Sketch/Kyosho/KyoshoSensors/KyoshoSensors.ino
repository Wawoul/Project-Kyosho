//--------------------------------------------------------------------------------------
//  Project Kyosho - 27/01/2021
//  By Ewen Paterson - Rev 3
//
//  Code for fuel and temp sensor fitted to a RC nitro truggy
//
//  ArduinoIDE ATmega328P Micro Controller
//--------------------------------------------------------------------------------------

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>  // Including the library of DS1820 Temperature module
#include <DallasTemperature.h>  // Including the library of DS1820 Temperature module

#define ONE_WIRE_BUS 2             // Initializing the Arduino pin 2 for temperature module

OneWire ourWire(ONE_WIRE_BUS);     // Declaring a variable named our wire
DallasTemperature sensors ( &ourWire ); // Asking the Dallas temperature library to use the one wire library
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2); // LCD Setup
int tempPin = 2; //Temp Sen
int introFlag = 0;

//-----------------------------------
// SETUP
//-----------------------------------

void setup() {
 lcd.init();    //LCD Screen
 lcd.backlight(); //LCD Screen
 sensors.begin(); //Temp Sensor
 pinMode(3, INPUT); //Fuel Sensor
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
 if (digitalRead(3) == HIGH) {
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
}

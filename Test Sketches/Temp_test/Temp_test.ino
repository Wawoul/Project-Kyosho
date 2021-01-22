#include <OneWire.h>  // Including the library of DS1820 Temperature module
#include <DallasTemperature.h>  // Including the library of DS1820 Temperature module
#define ONE_WIRE_BUS 2             // Initializing the Arduino pin 2 for temperature module
OneWire ourWire(ONE_WIRE_BUS);     // Declaring a variable named our wire
DallasTemperature sensors ( &ourWire ) ; // Asking the Dallas temperature library to use the one wire library

void setup() {

delay(1000) ;          // Wait for one second
Serial.begin(9600) ;   // Setting the baud rate at 9600
Serial.println( " Microcontrollerlab.com : This is the test code " ) ;
Serial.println( " Temperature Sensor :  DS18B20 " ) ;
delay(1000) ;         // Wait for one second
sensors.begin() ;     // The sensor will start working here
}

void loop() {

Serial.println () ;  // This will give some space in the output
Serial.print ( " Waiting for the temperature module to give value ... " ) ;                

// This will print “Waiting for the temperature module to give value … ” on the display.
sensors.requestTemperatures ( ) ;  // Sending the commands to get the temperature values from sensor
Serial.println ( " DONE " ) ;      // This will print “ done “ on the display
Serial.print  ( " Temperature in degree C is : " ) ; // This will print " Temperature in degree C is :" on the display
Serial.print ( sensors.getTempCByIndex ( 0 ) ) ; // This will show the temperature in degree C on the display
Serial.println ( "  Degrees C " ) ;             // This will print "  Degrees C " on the display
Serial.print ( " Temperature in degree Fahrenheit is : " ) ; // This will print " Temperature in degree Fahrenheit is : " on display
Serial.print ( sensors.getTempFByIndex ( 0 ) ) ;  // This will show the temperature in Fahrenheit on display
Serial.println ( "  Degrees F " ) ;               // This will print "  Degrees F " on the display
delay ( 5000 ) ;                                 // Waiting for 5 seconds.

}

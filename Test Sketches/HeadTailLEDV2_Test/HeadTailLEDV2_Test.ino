//#include <Adafruit_NeoPixel.h>
//#ifdef __AVR__
//#include <avr/power.h>
//#endif
//
//#define rcPin6 4   // Pin D4 Connected to CH6 of Transmitter;
//#define rcPin5 3   // Pin D3 onnected to CH5 of Transmitter;
//#define rcPin4 2   // Pin D2 Connected to CH4 of Transmitter;
//#define rcPin2 10   // Pin D10 Connected to CH2 of Transmitter;
//#define N_LEDS 44  // Num of Under LEDS
//#define PINU 5  // LED strip dat pin
//
//int ch6 = 0;  // Receiver Channel 6 PPM value
//int ch5 = 0;  // Receiver Channel 6 PPM value
//int ch4 = 0;  // Receiver Channel 6 PPM value
//int ch2 = 0;  // Receiver Channel 6 PPM value
//int ledHead = 6; // Head light LEDs
//int ledTail = 7; // Tail light LEDs
//int ledTailFlag = 0;
//int ledUnderFlagCH5 = 0;
//int ledUnderFlagCH6 = 0;
//
//void setup() {
//  // put your setup code here, to run once:
// //strip.begin(); //Under LED Start
// //strip.show(); //Initialize all pixels to 'off'
// //strip.setBrightness(10); //Sets LEDs brightness
// pinMode(ledHead, OUTPUT);
// pinMode(ledTail, OUTPUT);
//}
//
//void loop() {
//  // put your main code here, to run repeatedly:
//  ch4 = pulseIn(rcPin4, HIGH, 20000);  // (Pin, State, Timeout) //Brightness
//  ch2 = pulseIn(rcPin2, HIGH, 20000);  // (Pin, State, Timeout) //Break
//  ch4 = pulseIn(rcPin4, HIGH, 20000);  // (Pin, State, Timeout) //Brightness
//
//  if (ch2 >= 1500) {
//    digitalWrite(ledTail, HIGH); // sets the Tail light LED on
//   } else if (ch2 <= 1499) {
//    digitalWrite(ledTail, LOW); // sets the Tail light LED on
//   }
//
//
//  if (ch4 >= 950 && ch4 <= 1000) {
//        digitalWrite(ledHead, LOW);   // sets the LED off
//    }
//  if (ch4 >= 1450 && ch4 <= 1550) { //2- 1490-1498  - High Beam Head & Tail
//        //strip.setBrightness(10); //Sets LEDs brightness
//        digitalWrite(ledHead, HIGH);   // sets the Head light LED on
//    }
//   if (ch4 >= 1950 && ch4 <= 2000) {  //3- 1985-1991 - Under Leds full bright
//      //strip.setBrightness(100); //Sets LEDs brightness
//    }
//}


byte PWM_PIN1 = 3;
byte PWM_PIN2 = 10; // input from rcvr throttle to digi pin 2
byte PWM_PIN3 = 2; // input from rcvr  gear to digi pin 3

int pwm_value1;
int pwm_value2;
int pwm_value3;

const int ledPin8 = 5;
const int ledPin9 = 7;  // to brake light led
const int ledPin10 = 6; // to driving lights relay


void setup() {
  pinMode(PWM_PIN1, INPUT);
  pinMode(PWM_PIN2, INPUT);
  pinMode(PWM_PIN3, INPUT);

  pinMode(ledPin8, OUTPUT);
  pinMode(ledPin9, OUTPUT);
  pinMode(ledPin10, OUTPUT);

  Serial.begin(115200);
}

void loop() {
  pwm_value1 = pulseIn(PWM_PIN1, HIGH);
  pwm_value2 = pulseIn(PWM_PIN2, HIGH);
  pwm_value3 = pulseIn(PWM_PIN3, HIGH);

  if (pwm_value1 > 1470) {
    digitalWrite(ledPin8, LOW);
    Serial.println(pwm_value1);
  }
  else {
    digitalWrite(ledPin8, LOW);
  }
  if (pwm_value2 >= 1500) {
    digitalWrite(ledPin9, HIGH);  // turn brake light on
    Serial.println(pwm_value2);
  }
  else {
    digitalWrite(ledPin9, LOW);
  }
  if (pwm_value3 > 1470) {
    digitalWrite(ledPin10, HIGH);
    Serial.println(pwm_value3);
  }
  else {
    digitalWrite(ledPin10, LOW);
  }
}

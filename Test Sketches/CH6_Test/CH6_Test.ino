#define rcPin6 6   // Pin 4 Connected to CH6 of Transmitter;


int ch6 = 0;  // Receiver Channel 5 PPM value


void setup() {
  pinMode(rcPin6, INPUT);
  Serial.begin(9600);
}

void loop() {

// Read in the length of the signal in microseconds
  ch6 = pulseIn(rcPin6, HIGH, 20000);  // (Pin, State, Timeout)

  Serial.print("Channel #6: ");
  Serial.println(ch6);
  delay(500);
  
// Clear screen and move cursor Home, only works in PUTTY
  Serial.write(27);       // ESC command

}

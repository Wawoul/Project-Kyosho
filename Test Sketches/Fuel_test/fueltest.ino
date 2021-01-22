void setup(){
  //start serial connection
  Serial.begin(9600);
  pinMode(3, INPUT);
  pinMode(13, OUTPUT);
}

void loop(){
  //read the switch value into a variable
  int sensorVal = digitalRead(3);
  //print out the value of the liquid level
  Serial.println(sensorVal);
  if (sensorVal == HIGH) {
    digitalWrite(13, LOW);
  }
  else {
    digitalWrite(13, HIGH);
  }
}

String inString = "";
void setup() {
  Serial.begin(115200);
}
void loop() {
  if (Serial.available() > 0) {
    int inChar = Serial.read();
    Serial.print("Value : ");
    Serial.print(inChar);   
    if(isDigit(inChar)){
      inString += (char)inChar;  
    }
    int number = inString.toInt();
    Serial.print("You sent me: ");
    Serial.println(number);
  }
}

#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Adafruit_MLX90614.h>
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
char receivedChar;
boolean newData = false;
int incomingByte;
String inString = "";
byte buzzer = 9;
byte led1 = 2; //pin D0
byte led2 = 14; //pin D0
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);
void setup() {
  Serial.begin(115200);
  lcd.init();
  lcd.backlight();
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer,LOW);
  digitalWrite(led1,LOW);
  digitalWrite(led2,LOW);
}


void loop(){
  if (Serial.available() > 0) {
    // read the incoming byte:
    int inChar = Serial.read();  
    if(isDigit(inChar)){
      inString += (char)inChar;  
    }
    int number = inString.toInt();
    if(number == 1){
      digitalWrite(buzzer,HIGH);
      delay(300);
      digitalWrite(buzzer,LOW);
      lcd.setCursor(2,0);
      lcd.print("Temperature"); 
      // Display static text
      float temp = mlx.readObjectTempC() + 2.5;
      lcd.setCursor(5,1);
      lcd.print(temp);
      lcd.print(" C");
      if(temp >= 38){
        digitalWrite(led1,HIGH);
        delay(3000);
        digitalWrite(led1,LOW);
      }else{
        digitalWrite(led2,HIGH);
        delay(3000);
        digitalWrite(led2,LOW);
      }
      Serial.println(temp);
    }
    // say what you got:
    inString = "";
 }
}

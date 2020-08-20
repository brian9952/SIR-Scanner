
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_MLX90614.h>
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
  
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

char receivedChar;
boolean newData = false;
int incomingByte;
String inString = "";
byte led1 = 2; //pin D0
byte led2 = 14; //pin D0

void setup() {
  Serial.begin(115200);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  Serial.println("Adafruit MLX90614 test");  
  mlx.begin();  
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
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
      display.clearDisplay();
      display.setTextSize(3);
      display.setTextColor(WHITE);
      display.setCursor(0,5);
      // Display static text
      display.print(mlx.readObjectTempC()); 
      display.print(" C");
      display.display();
      int temp = mlx.readObjectTempC();
      if(temp >= 38){
        digitalWrite(led1,HIGH);
        delay(3000);
        digitalWrite(led1,LOW);
      }else{
        digitalWrite(led2,HIGH);
        delay(3000);
        digitalWrite(led2,LOW);
      }
    }
    // say what you got:
    inString = "";
  Serial.print("0");  
 }
}



  

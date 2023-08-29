#include <Arduino.h>

// put function declarations here:
int LED = 13;
int button = 12;


void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
    pinMode(LED, OUTPUT);
    pinMode(button, INPUT);

}

void loop() {
  if(serial.available() > 0){
    String msgP = serial.readString();

    if(msgP == "on"){
      if(digitalRead(button) == HIGH){
        digitalWrite(LED, HIGH);
        Serial.println("Button is pressed");
      
      }
        digitalWrite(LED, LOW);
      }
      else if(msgP == "off"){
        digitalWrite(LED, LOW);
      }
      else{
        Serial.println("Invalid input");
    }
  }



}


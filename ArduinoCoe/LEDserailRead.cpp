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
  if(Serial.available() > 0){
    String msgP = Serial.readString();

    if(msgP == "on"){
      digitalWrite(LED, HIGH);
      delay(1000);
      }
      else if(msgP == "off"){
        digitalWrite(LED, LOW);
      }
  }

}


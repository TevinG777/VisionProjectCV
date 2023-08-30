#include <Arduino.h>

// put function declarations here:
int LED = 13;
int LED2 = 12;
int LED3 = 11;

void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
    pinMode(LED, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(LED3, OUTPUT);

}

void loop() {
  if(Serial.available() > 0){
    unsigned long currentTime = millis();
    const long interval = 250;
    unsigned previousTime = 0;

    String msgP = Serial.readString();

    //Convert serial input to a float
    float msgPf = msgP.toFloat();
    
    //if the float is between 1000-15000 then set the LED to HIGH if not green LED On
    if(msgPf > 1000 && msgPf < 15000){
        digitalWrite(LED, HIGH);
        digitalWrite(LED2, LOW);
    }
    else{
        digitalWrite(LED, LOW);
        digitalWrite(LED2, HIGH);
    }
        
  }

  
  else{
    digitalWrite(LED3, HIGH);
  }
}


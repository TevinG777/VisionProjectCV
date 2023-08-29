#include <Arduino.h>

// put function declarations here:
int LED = 13;
int LED2 = 12;


void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
    pinMode(LED, OUTPUT);
    pinMode(LED2, OUTPUT);

}

void loop() {
  if(Serial.available() > 0){
    unsigned long currentTime = millis();
    const long interval = 250;
    unsigned previousTime = 0;

    String msgP = Serial.readString();

    //Convert serial input to a float
    float msgPf = msgP.toFloat();

    //take sample of data every .25 seconds 
    if(currentTime - previousTime >= interval){
        previousTime = currentTime;
    
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

  }

}


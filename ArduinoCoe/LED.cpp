#include <Arduino.h>
#include <SoftwareSerial.h>

const byte rxPin = 3; // Arduino RX = D3
const byte txPin = 2; // Arduino TX = D2
const int pwmPin1 = 6;
const int pwmPin2 = 11;

int in1 = 4; // variable names for the L298N
int in2 = 5; // variable names for the L298N
int in3 = 9; // variable names for the L298N
int in4 = 10; // variable names for the L298N

int in2_1 = 7; // variable names for the L298N
int in2_2 = 8; // variable names for the L298N
int in2_3 = 12; // variable names for the L298N
int in2_4 = 13; // variable names for the L298N

SoftwareSerial mySerial(rxPin, txPin); // Begin a software serial on pins D3 and D2 to talk to the Pi

void setup() {
  Serial.begin(115200); // Begin the hardware D0 and D1 - we can use this Serial for debugging
  mySerial.begin(9600); // Software serial for communicating with Pi

  // Motor 1
  pinMode(in1, OUTPUT); // all L298N digital pins are outputs
  pinMode(in2, OUTPUT); // all L298N digital pins are outputs
  pinMode(in3, OUTPUT); // all L298N digital pins are outputs
  pinMode(in4, OUTPUT); // all L298N digital pins are outputs

  // Motor 2
  pinMode(in2_1, OUTPUT); // all L298N digital pins are outputs
  pinMode(in2_2, OUTPUT); // all L298N digital pins are outputs
  pinMode(in2_3, OUTPUT); // all L298N digital pins are outputs
  pinMode(in2_4, OUTPUT); // all L298N digital pins are outputs

  // Configure PWM pins
  pinMode(pwmPin1, OUTPUT);
  pinMode(pwmPin2, OUTPUT);

}

void loop() {
  if(mySerial.available()){

    String msgP = Serial.readString();

    // Initialize variables to hold the float value for area and x pos
    float area = 0.0;
    int pos = 0;

    //  Find the comma in the string
    int commaIndex = msgP.indexOf(',');

    //  If the comma is found, then parse the string
    if (commaIndex != -1) {
      //  Get the position string
      String posStr = msgP.substring(commaIndex , 0);
      pos = posStr.toInt();

      //  Get the area string
      String areaStr = msgP.substring(commaIndex + 1);
      area = areaStr.toFloat();


    }

    //if the float is between 1000-15000 then set the LED to HIGH if not green LED On
    if(area > 6000 && area < 9000){

        //Stop motor
        digitalWrite(in1, LOW);
        digitalWrite(in2, LOW);
        digitalWrite(in3, LOW);
        digitalWrite(in4, LOW);

        
        digitalWrite(in2_1, LOW);
        digitalWrite(in2_2, LOW);
        digitalWrite(in2_3, LOW);
        digitalWrite(in2_4, LOW);

        // Set PWM values to stop the motors (0 for full stop)
        analogWrite(pwmPin1, 0);
        analogWrite(pwmPin2, 0);
        
    }
    else if(area == 0.0){
         //Stop motor
        digitalWrite(in1, LOW);
        digitalWrite(in2, LOW);
        digitalWrite(in3, LOW);
        digitalWrite(in4, LOW);

        //Stop motor
        digitalWrite(in2_1, LOW);
        digitalWrite(in2_2, LOW);
        digitalWrite(in2_3, LOW);
        digitalWrite(in2_4, LOW);


        // Set PWM values to stop the motors (0 for full stop)
        analogWrite(pwmPin1, 0);
        analogWrite(pwmPin2, 0);

    }
    else if(area <= 6000){

      // Set each group of motors to go forward
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      digitalWrite(in3, LOW);
      digitalWrite(in4, HIGH);

      digitalWrite(in2_1, HIGH);
      digitalWrite(in2_2, LOW);
      digitalWrite(in2_3, LOW);
      digitalWrite(in2_4, HIGH);

      // Set PWM values to control speed (0-255, adjust as needed)
      analogWrite(pwmPin1, 255); // Full speed
      analogWrite(pwmPin2, 255); // Full speed


    }
    else if(area >= 9000){
      //Robot is to close move back

      // Set each group of motors to go backward
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);


      digitalWrite(in2_1, LOW);
      digitalWrite(in2_2, HIGH);
      digitalWrite(in2_3, HIGH);
      digitalWrite(in2_4, LOW);

      // Set PWM values to control speed (0-255, adjust as needed)
      analogWrite(pwmPin1, 255); // Full speed
      analogWrite(pwmPin2, 255); // Full speed



    }
        
  }

}


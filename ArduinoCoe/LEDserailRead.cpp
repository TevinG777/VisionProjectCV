#include <SoftwareSerial.h>

const byte rxPin = 3; // Arduino RX = D3
const byte txPin = 2; // Arduino TX = D2

int in1 = 4; // variable names for the L298N
int in2 = 5; // variable names for the L298N
int in3 = 9; // variable names for the L298N
int in4 = 10; // variable names for the L298N

int in2_1 = 6; // variable names for the L298N
int in2_2 = 7; // variable names for the L298N
int in2_3 = 11; // variable names for the L298N
int in2_4 = 12; // variable names for the L298N


SoftwareSerial mySerial(rxPin, txPin); // Begin a software serial on pins D3 and D2 to talk to the Pi

void setup() {
  Serial.begin(115200); // Begin the hardware D0 and D1 - we can use this Serial for debugging
  mySerial.begin(9600); // Software serial for communicating with Pi

  // Motor 1
  pinMode (in1, OUTPUT); // all L298N digital pins are outputs
  pinMode (in2, OUTPUT); // all L298N digital pins are outputs
  pinMode (in3, OUTPUT); // all L298N digital pins are outputs
  pinMode (in4, OUTPUT); // all L298N digital pins are outputs

  //Motor 2
  pinMode (in2_1, OUTPUT); // all L298N digital pins are outputs
  pinMode (in2_2, OUTPUT); // all L298N digital pins are outputs
  pinMode (in2_3, OUTPUT); // all L298N digital pins are outputs
  pinMode (in2_4, OUTPUT); // all L298N digital pins are outputs

}

void loop() {
  if (mySerial.available()) {
    char receivedChar = mySerial.read();
    if (receivedChar == '1') {
      Serial.println("Received a 1");

      //Set each group of motors to go forward
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      digitalWrite(in3, LOW);
      digitalWrite(in4, HIGH);

      digitalWrite(in2_1, LOW);
      digitalWrite(in2_2, HIGH);
      digitalWrite(in2_3, HIGH);
      digitalWrite(in2_4, LOW);


    } else if (receivedChar == '0') {
      Serial.println("Received a 0");

      //Stop each group of motors
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
      digitalWrite(in3, LOW);
      digitalWrite(in4, LOW);

      digitalWrite(in2_1, LOW);
      digitalWrite(in2_2, LOW);
      digitalWrite(in2_3, LOW);
      digitalWrite(in2_4, LOW);


    }
  }
}

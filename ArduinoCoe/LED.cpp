#include <Arduino.h>
#include <SoftwareSerial.h>

const byte rxPin = 3; // Arduino RX = D3
const byte txPin = 2; // Arduino TX = D2
const int pwmPin1 = 6; // Right
const int pwmPin2 = 11; //Left

float area = 0.0;
  int pos = 0;

int in1 = 4; // variable names for the L298N
int in2 = 5; // variable names for the L298N
int in3 = 9; // variable names for the L298N
int in4 = 10; // variable names for the L298N

int in2_1 = 7; // variable names for the L298N
int in2_2 = 8; // variable names for the L298N
int in2_3 = 12; // variable names for the L298N
int in2_4 = 13; // variable names for the L298N

int debugPin = 0;

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
  static char buffer[64]; // Buffer Characters for incoming messages
  static byte bufferIndex = 0;
  

  if (mySerial.available()) {
    char receivedChar = mySerial.read();

    if (receivedChar == '\n') { // Using new line character to split messages
      buffer[bufferIndex] = '\0'; // Null-terminate the buffer
      bufferIndex = 0;

      // Parse the buffer
      char *posStr = strtok(buffer, ","); // Parse the first value (pos)
      char *areaStr = strtok(NULL, ","); // Parse the second value (area)

      if (posStr != NULL && areaStr != NULL) {
        pos = atoi(posStr); // Convert the string to an int
        area = atof(areaStr); // Convert the string to a float
      }
    } else {
      // If the buffer is full, reset it
      buffer[bufferIndex] = receivedChar;
      bufferIndex++;

      // Handle the case where the buffer is too small for your messages
      if (bufferIndex >= sizeof(buffer) - 1) {
        bufferIndex = 0; // Reset the buffer
      }
    }
  }

  Serial.println(pos); // Print the area to the serial monitor (for debugging
  Serial.println(area); // Print the position to the serial monitor (for debugging)

  if (area == 0.0) {
    // Stop motors
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
  else if(area > 500 && area < 7000){
    // Drive forward
    // Set each group of motors to go forward
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);

    digitalWrite(in2_1, HIGH);
    digitalWrite(in2_2, LOW);
    digitalWrite(in2_3, LOW);
    digitalWrite(in2_4, HIGH);

    if(pos>=0 && pos < 50){
      analogWrite(pwmPin1, 255); // right side
      analogWrite(pwmPin2, 0); // left

    }
    else if(pos>=50 && pos <105)
    {
      analogWrite(pwmPin1, 255); // Full speed
      analogWrite(pwmPin2, 0); // Full speed
    }
    else if(pos>=105 && pos <=210)
    {
      analogWrite(pwmPin1, 255); // Full speed
      analogWrite(pwmPin2, 255); // Full speed
    }
    else if(pos>=210 && pos <=265)
    {
      analogWrite(pwmPin1, 0); // Full speed
      analogWrite(pwmPin2, 255); // Full speed
    }
    else if(pos>265 && pos <=320)
    {
      analogWrite(pwmPin1, 0); // Full speed
      analogWrite(pwmPin2, 255); // Full speed
    }

    
  }
  else{
        // Stop motors
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
}

#include <Arduino.h

TCCR0B = TCCR0B & B11111000 | B00000010; // Set timer 0 to 1/1024 prescaler

int trigPin = 4;
int echoPin = 3;

int IR_right = 11;
int IR_left = 12;


int PWM_r = 6;
int PWM_l = 5;

int lMot1 = 9;
int lMot2 = 10;

int rMot1 = 7;
int rMot2 = 8;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(IR_right, INPUT);
  pinMode(IR_left, INPUT);
  pinMode(PWM_r, OUTPUT);
  pinMode(PWM_l, OUTPUT);
  pinMode(lMot1, OUTPUT);
  pinMode(lMot2, OUTPUT);
  pinMode(rMot1, OUTPUT);
  pinMode(rMot2, OUTPUT);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  long distance = (duration / 2) / 29.1;
  Serial.print(distance);
  Serial.println(" cm");

  delay(100);
  
  // if distance is less than or equal to 15 stop motor
    if (distance <= 15) {
        digitalWrite(lMot1, LOW);
        digitalWrite(lMot2, LOW);
        digitalWrite(rMot1, LOW);
        digitalWrite(rMot2, LOW);

        //Set pwn Pins
        analogWrite(PWM_r, 0);
        analogWrite(PWM_l, 0);
    }
    else {
        //Set pwn Pins
        analogWrite(PWM_r, 255);
        analogWrite(PWM_l, 255);

        //Set motor 1
        digitalWrite(lMot1, HIGH);
        digitalWrite(lMot2, LOW);

        //Set motor 2
        digitalWrite(rMot1, HIGH);
        digitalWrite(rMot2, LOW);
    }

}
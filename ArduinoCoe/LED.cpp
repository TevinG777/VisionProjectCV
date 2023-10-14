#include <Arduino.h>
#include <LiquidCrystal.h>

// put function declarations here:
int seconds = 0;
int in1 = 4; // variable names for the L298N
int in2 = 5; // variable names for the L298N
int in3 = 9; // variable names for the L298N
int in4 = 10; // variable names for the L298N

LiquidCrystal lcd_1(8, 7, 5, 4, 3, 2);

void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
    pinMode (in1, OUTPUT); // all L298N digital pins are outputs
    pinMode (in2, OUTPUT); // all L298N digital pins are outputs
    pinMode (in3, OUTPUT); // all L298N digital pins are outputs
    pinMode (in4, OUTPUT); // all L298N digital pins are outputs

    //Set up the LCD Display
    lcd_1.begin(16, 2);

}

void loop() {
  if(Serial.available() > 0){

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
    // Initilize strign vars
    String posTxt = "Unkown";

    //If the object is between the pos values 0, 100 set a posTxt variable to left, if it is from 100-350 set it to center, if it is 350-600 set it to right
    if(pos > 0 && pos < 100){
      posTxt = "Left";
    }
    else if(pos >= 100 && pos < 350){
      posTxt = "Center";
    }
    else{
      posTxt = "Right";
    }
    
    //if the float is between 1000-15000 then set the LED to HIGH if not green LED On
    if(area > 1000 && area < 9000){
        //Clear the LCD
        lcd_1.clear();

        //Stop motor
        digitalWrite(in1, LOW);
        digitalWrite(in2, LOW);
        digitalWrite(in3, LOW);
        digitalWrite(in4, LOW);
        
        //PRitn mid range to LCD
        lcd_1.setCursor(0, 0);
        lcd_1.print("Middle: " + posTxt);

        //Print the area to the LCD
        lcd_1.setCursor(0, 1);
        lcd_1.print("Area: " + String(area));

    }
    else if(area == 0.0){

      //Clear the LCD
      lcd_1.clear();

      //Print STOP to LCD
      lcd_1.setCursor(0, 0);
      lcd_1.print("STOP");

    }
    else if(area <= 1000){

        //Set the motor to go forward
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
        digitalWrite(in3, LOW);
        digitalWrite(in4, HIGH);

        //Clear the LCD
        lcd_1.clear();

        //Print mid range to LCD
        lcd_1.setCursor(0, 0);
        lcd_1.print("Far: " + posTxt);

        //Print the area to the LCD
        lcd_1.setCursor(0, 1);
        lcd_1.print("Area: " + String(area));
    }
    else{
      //Clear the LCD
      lcd_1.clear();   

      //Set motor to go backwards
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      digitalWrite(in3, LOW);
      digitalWrite(in4, HIGH);

      //PRitn mid range to LCD
      lcd_1.setCursor(0, 0);
      lcd_1.print("Close: " + posTxt);

      //Print the area to the LCD
      lcd_1.setCursor(0, 1);
      lcd_1.print("Area: " + String(area));

    }
        
  }

}


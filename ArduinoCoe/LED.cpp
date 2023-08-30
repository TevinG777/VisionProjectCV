#include <Arduino.h>
#include <LiquidCrystal.h>

// put function declarations here:
int LED = 13;
int LED2 = 12;
int LED3 = 11;
int seconds = 0;

LiquidCrystal lcd_1(8, 7, 5, 4, 3, 2);

void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
    pinMode(LED, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(LED3, OUTPUT);

    //Set up the LCD Display
    lcd_1.begin(16, 2);

}

void loop() {
  if(Serial.available() > 0){

    String msgP = Serial.readString();

    // Initialize variables to hold the float value for area and x pos
    float area = 0.0;
    int pos = 0;

    int commaIndex = msgP.indexOf(',');

    if (commaIndex != -1) {
      String areaStr = msgP.substring(0, commaIndex);
      area = areaStr.toFloat();

      String posStr = msgP.substring(commaIndex + 1);
      pos = posStr.toInt();
    }

    
    //if the float is between 1000-15000 then set the LED to HIGH if not green LED On
    if(area > 1000 && area < 9000){
        //Clear the LCD
        lcd_1.clear();
        
        digitalWrite(LED, HIGH);
        digitalWrite(LED2, LOW);
        digitalWrite(LED3, LOW);
        
        //PRitn mid range to LCD
        lcd_1.setCursor(0, 0);
        lcd_1.print("Mid Range");

        //Print the area to the LCD
        lcd_1.setCursor(0, 1);
        lcd_1.print("Area: " + String(area));

    }
    else if(area <= 1000){
        digitalWrite(LED, LOW);
        digitalWrite(LED2, HIGH);
        digitalWrite(LED3, LOW);

        //Clear the LCD
        lcd_1.clear();

        //Print mid range to LCD
        lcd_1.setCursor(0, 0);
        lcd_1.print("Far Range");

        //Print the area to the LCD
        lcd_1.setCursor(0, 1);
        lcd_1.print("Area: " + String(area));
    }
    else{
      //Clear the LCD
      lcd_1.clear();   

      digitalWrite(LED, LOW);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, HIGH);

      //PRitn mid range to LCD
      lcd_1.setCursor(0, 0);
      lcd_1.print("Close Range");

      //Print the area to the LCD
      lcd_1.setCursor(0, 1);
      lcd_1.print("Area: " + String(area));

    }
        
  }

  

}


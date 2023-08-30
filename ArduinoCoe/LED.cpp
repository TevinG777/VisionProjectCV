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

    //Convert serial input to a float
    float msgPf = msgP.toFloat();
    
    //if the float is between 1000-15000 then set the LED to HIGH if not green LED On
    if(msgPf > 1000 && msgPf < 15000){
        digitalWrite(LED, HIGH);
        digitalWrite(LED2, LOW);
        digitalWrite(LED3, LOW);
        
        //PRitn mid range to LCD
        lcd_1.setCursor(0, 0);
        lcd_1.print("Mid Range");
    }
    else if(msgPf <= 1000 || msgPf >= 15000){
        digitalWrite(LED, LOW);
        digitalWrite(LED2, HIGH);
        digitalWrite(LED3, LOW);
        
        //PRitn mid range to LCD
        lcd_1.setCursor(0, 0);
        lcd_1.print("FaR Range");
    }
    else{
      digitalWrite(LED, LOW);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, HIGH);
    }
        
  }

  

}


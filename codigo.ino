/*
  LiquidCrystal Library - Hello World

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch prints "Hello World!" to the LCD
 and shows the time.

  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystal
 */

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

float timer_aux = 0;
float maxTimer = 0;
unsigned long millisTimer1 = millis();

int flagStart = 0;
int buttonState = 0;
const int pinoBTN = 8; 
const int pinoMOTOR = 12; 
const int pinoLED_STATUS = LED_BUILTIN;  // LED_BUILTIN: 13

void setup() {
  Serial.begin(9600);
  Serial.println("Oi Euler");
  
  lcd.begin(0, 0);  // set up the LCD's number of columns and rows:
  lcd.print("Timer - OFF"); // Print a message to the LCD.
  
  pinMode(pinoBTN, INPUT);
  pinMode(pinoLED_STATUS, OUTPUT);
  pinMode(pinoMOTOR, OUTPUT);
  
  maxTimer = 1000; // limite padrão (1000 miliseguntos = 1 segundo)

}

void loop() {

  buttonState = digitalRead(pinoBTN);
  //Serial.print("buttonState: ");
  //Serial.println(buttonState);

  lcd.setCursor(12, 0);
  lcd.print(buttonState);
  lcd.setCursor(14, 0);
  lcd.print(flagStart);
  if(flagStart == 0) {
    if (buttonState == HIGH) {
      ligaTimer();
      delay(10); // Delay que serve p/ o sinal não desligar imediatamente o timer
    }
  } else {
    if (buttonState == HIGH) {
      desligaTimer();
      delay(10); // Delay que serve p/ o sinal não desligar imediatamente o timer
    } else {
      timer();
    }
  }
  //delay(10); // Delay a little bit to improve simulation performance
}

void timer(){
  long timerDiff = (millis() - millisTimer1);
  
  // Verifica se já passou 1000 milisegundos
  if(timerDiff < maxTimer){    
    //digitalWrite(8, HIGH);  // Acende o led do pino 8
    //flagStart = 1;
    //Serial.println("timer on");
  }else{    
    //digitalWrite(8, LOW);  // Apaga o led do pino 8
    //flagStart = 0;    
    Serial.println(">> timer off");
    desligaTimer();
  }
  // Verifica se já passou 2000 milisegundos .. religamento!
  //if(timerDiff > (maxTimer * 2)){
  //  millisTimer1 = millis();
  //}
  
  Serial.println(timerDiff);
  //timer_aux = (timerDiff / 1000);
  //Serial.println(timer_aux);
  lcd.setCursor(0, 1);
  //lcd.print(timer_aux); // print the number of seconds since reset:
  lcd.print(timerDiff); 

}

void ligaTimer(){  
  digitalWrite(pinoLED_STATUS, HIGH);  // turn LED on
  digitalWrite(pinoMOTOR, HIGH);
  
  millisTimer1 = millis(); // reseta timer
  maxTimer = 1000; // setando limite do timer (1000 miliseguntos = 1 segundo)
  flagStart = 1;
  
  lcd.begin(0, 0);
  lcd.print("Timer - ON");

  Serial.println("---- start timer ----");
}

void desligaTimer(){
  digitalWrite(pinoLED_STATUS, LOW);  // turn LED off
  digitalWrite(pinoMOTOR, LOW);
  
  flagStart = 0;
  
  lcd.begin(0, 0);
  lcd.print("Timer - OFF");
  
  Serial.println("---- end timer ----");
}
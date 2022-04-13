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

//const int pinoPOT = A5; //PINO ANALÓGICO UTILIZADO PELO POTENCIÔMETRO
//const int pinoLED = 10; //PINO DIGITAL UTILIZADO PELO LED
//const int pinoLED2 = 9; //PINO DIGITAL UTILIZADO PELO LED 2

//float luminosidadeLED = 0; //VARIÁVEL QUE ARMAZENA O VALOR DA LUMINOSIDADE QUE SERÁ APLICADA AO LED
float timer_aux = 0;

int flagStart = 0;
int buttonState = 0;
const int pinoBTN = 8; 

void setup() {
  Serial.begin(9600);
  Serial.println("Oi Euler");
  
  lcd.begin(0, 0);  // set up the LCD's number of columns and rows:
  lcd.print("Timer - OFF"); // Print a message to the LCD.
  
  //pinMode(pinoLED2, OUTPUT);    // sets the digital pin 13 as output

  //pinMode(pinoPOT, INPUT); //DEFINE O PINO COMO ENTRADA
  //pinMode(pinoLED, OUTPUT); //DEFINE O PINO COMO SAÍDA
  
  
  pinMode(pinoBTN, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);

}

void loop() {
  //// set the cursor to column 0, line 1
  //// (note: line 1 is the second row, since counting begins with 0):
  //lcd.setCursor(0, 1);
  //// print the number of seconds since reset:
  ////lcd.print(millis() / 1000);
  //timer_aux = (millis() / 1000);
  //lcd.print(timer_aux);
  //Serial.print("Timer: ");
  //Serial.println(timer_aux);
  //// delay a bit
  //delay(50);
  
  //------------------------------
  //digitalWrite(pinoLED2, HIGH); // sets the digital pin 13 on
  //delay(1000);            // wai for a second
  //digitalWrite(pinoLED2, LOW);  // sets the digital pin 13 off
  //delay(1000);            // waits for a second
  ////Serial.print("HIGH: ");
  ////Serial.println(HIGH);

  //------------------------------
  //luminosidadeLED = map(analogRead(pinoPOT), 0, 1023, 0, 255); //EXECUTA A FUNÇÃO "map" DE ACORDO COM OS PARÂMETROS PASSADOS
  //analogWrite(pinoLED, luminosidadeLED); //APLICA AO LED O VALOR DE LUMINOSIDADE GERADO PELA FUNÇÃO "map"
  
  //Serial.print("Led: ");
  //Serial.println(luminosidadeLED);
  //lcd.print(luminosidadeLED);

  //------------------------------
  // read the state of the pushbutton value
  buttonState = digitalRead(pinoBTN);
  // check if pushbutton is pressed.  if it is, the
  // buttonState is HIGH
  //Serial.print("buttonState: ");
  //Serial.println(buttonState);
  lcd.setCursor(0, 1);
  lcd.print(buttonState);
  lcd.setCursor(3, 1);
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
    }
  }
  //delay(10); // Delay a little bit to improve simulation performance
}

void ligaTimer(){
  // turn LED on
  digitalWrite(LED_BUILTIN, HIGH);
  flagStart = 1;
  lcd.begin(0, 0);
  lcd.print("Timer - ON");

  Serial.println("---- start timer ----");
}

void desligaTimer(){
  // turn LED off
  digitalWrite(LED_BUILTIN, LOW);
  flagStart = 0;
  lcd.begin(0, 0);
  lcd.print("Timer - OFF");
  
  Serial.println("---- end timer ----");
}
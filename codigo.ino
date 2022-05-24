// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

float timer_aux = 0;
float maxTimer = 0;
unsigned long millisTimer1 = millis();

int flagStart = 0;
int buttonState = 0;
int buttonStateAdd = 0;
int buttonStateSub = 0;
int buttonStatePlus = 0;
const int pinoBTN_START = 11; 
const int pinoBTN_ADD = 10; 
const int pinoBTN_SUB = 9; 
const int pinoBTN_PLUS = 8; 
const int pinoMOTOR = 12; 
const int pinoLED_STATUS = LED_BUILTIN;  // LED_BUILTIN: 13

void setup() {
  Serial.begin(9600);
  Serial.println("=========================================================");
  Serial.println("Oi Euler");
  delay(10);
  
  lcd.begin(16, 2); //Configuracoes LCD 16x2
  lcd.clear(); //apagando tela do monitor serial
  lcd.begin(0, 0);  // set up the LCD's number of columns and rows:
  lcd.print("Timer - OFF"); // Print a message to the LCD.
  delay(10);

  pinMode(pinoBTN_START, INPUT);
  pinMode(pinoBTN_ADD, INPUT);
  pinMode(pinoBTN_SUB, INPUT);
  pinMode(pinoBTN_PLUS, INPUT);
  pinMode(pinoLED_STATUS, OUTPUT);
  pinMode(pinoMOTOR, OUTPUT);
  
  maxTimer = 1000; // limite padrão (1000 miliseguntos = 1 segundo)
  lcd.setCursor(0, 1);
  lcd.print(0); 
  //lcd.write('0');
  delay(10);
  lcd.print(maxTimer);
  Serial.println("---- default timer ----");
  Serial.println(maxTimer);  

}

void loop() {
  
  buttonState = digitalRead(pinoBTN_START);
  buttonStateAdd = digitalRead(pinoBTN_ADD);
  buttonStateSub = digitalRead(pinoBTN_SUB);
  buttonStatePlus = digitalRead(pinoBTN_PLUS);
  //Serial.print("buttonState: ");
  //Serial.println(buttonState);

  lcd.setCursor(12, 0);
  lcd.print(buttonState);
  lcd.setCursor(14, 0);
  lcd.print(flagStart);
  if(flagStart == 0) {
    if (buttonState == HIGH) {
      ligaTimer();
      delay(100); // Delay que serve p/ o sinal não desligar imediatamente o timer
    } else {
      if (buttonStateAdd == HIGH) {
        addTimer(maxTimer);
        delay(100); // Delay que serve p/ não duplicar o sinal
      } else if (buttonStateSub == HIGH) {
        subtractTimer(maxTimer);
        delay(100); // Delay que serve p/ não duplicar o sinal
      } else if (buttonStatePlus == HIGH) {
        multiplyTimer(maxTimer);
        delay(100); // Delay que serve p/ não duplicar o sinal
      }
    }
  } else {
    if (buttonState == HIGH) {
      desligaTimer();
      delay(100); // Delay que serve p/ o sinal não desligar imediatamente o timer
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
  ////timer_aux = (timerDiff / 1000);
  ////Serial.println(timer_aux);
  //lcd.setCursor(0, 1);
  ////lcd.print(timer_aux); // print the number of seconds since reset:
  lcd.setCursor(0, 1);
  lcd.print(timerDiff); 
  ////delay(10);
}

void ligaTimer(){  
  digitalWrite(pinoLED_STATUS, HIGH);  // turn LED on
  digitalWrite(pinoMOTOR, HIGH);
  
  millisTimer1 = millis(); // reseta timer
  //maxTimer = 1000; // setando limite do timer (1000 miliseguntos = 1 segundo)
  flagStart = 1;
  
  lcd.begin(0, 0);
  lcd.print("Timer - ON");

  Serial.println("---- start timer ----");
  Serial.println(maxTimer);  
}

void desligaTimer(){
  digitalWrite(pinoLED_STATUS, LOW);  // turn LED off
  digitalWrite(pinoMOTOR, LOW);
  
  long timerDiff = (millis() - millisTimer1);
  flagStart = 0;
  
  lcd.begin(0, 0);
  lcd.print("Timer - OFF");
  lcd.setCursor(0, 1);
  lcd.print(timerDiff); 
  
  Serial.println("---- end timer ----");
}



void addTimer(float maxTimerAux){
  maxTimer = maxTimerAux + 100;
  lcd.setCursor(0, 1);
  lcd.print(maxTimer);
  Serial.println("---- add timer ----");
  Serial.println(maxTimer);  
}


void subtractTimer(float maxTimerAux){
  maxTimer = maxTimerAux - 100;
  lcd.setCursor(0, 1);
  lcd.print(maxTimer);
  Serial.println("---- subtract timer ----");
  Serial.println(maxTimer);  
}


void multiplyTimer(float maxTimerAux){
  maxTimer = maxTimerAux * 2;
  lcd.setCursor(0, 1);
  lcd.print(maxTimer);
  Serial.println("---- multiply timer ----");
  Serial.println(maxTimer);  
}

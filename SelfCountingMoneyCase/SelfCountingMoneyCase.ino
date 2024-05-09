#include <TM1637Display.h>

// Module connection pins (Digital Pins)
#define CLK 2
#define DIO 3

TM1637Display display(CLK, DIO);
const int pinMoney1 = 9;
const int pinMoney2 = 8;
const int pinMoney5 = 7;
const int pinMoney10 = 6;
const int pinMoney20 = 5;
const unsigned long timeToWait = 5000;

int currentMoney = 0;
int flgWaitOnTime = 0;
int flgClear = 1;
unsigned long timeSnap;

void setup() {
  Serial.begin(9600);
  pinMode(pinMoney1, INPUT);
  pinMode(pinMoney2, INPUT);
  pinMode(pinMoney5, INPUT);
  pinMode(pinMoney10, INPUT);
  pinMode(pinMoney20, INPUT);
  display.setBrightness(0x0f);
  clearDisplay();
}

void loop() {

  if(digitalRead(pinMoney1) == LOW) {
    addMoney(pinMoney1, 1);
  }

  if(digitalRead(pinMoney2) == LOW) {
    addMoney(pinMoney2, 2);
  }

  if(digitalRead(pinMoney5) == LOW) {
    addMoney(pinMoney5, 5);
  }

  if(digitalRead(pinMoney10) == LOW) {
    addMoney(pinMoney10, 10);
  }

  if(digitalRead(pinMoney20) == LOW) {
    addMoney(pinMoney20, 20);
  }

   if (flgWaitOnTime == 0 && flgClear == 0 ) {
     clearDisplay();
   }

   if(flgWaitOnTime == 1 && (timeSnap + timeToWait) < abs(millis())) {
     flgWaitOnTime = 0;
   }
}

void displayNumber(int number) {
  display.showNumberDec(number, false);
  timeSnap = abs(millis());
  flgClear = 0;
  flgWaitOnTime = 1;

  Serial.println(timeSnap);
}

void clearDisplay () {
  display.clear();
  flgClear = 1;
}

void addMoney (int pin, int moneyToAdd) {

  currentMoney += moneyToAdd;
  displayNumber(currentMoney);
  Serial.println("Added");
  Serial.println(moneyToAdd);
  while (digitalRead(pin) == LOW) {
    delay(20);
  }

  delay(20);
}

void printAllSensors() {
  Serial.println("sadasdad");
  Serial.println(digitalRead(pinMoney1));
  Serial.println(digitalRead(pinMoney2));
  Serial.println(digitalRead(pinMoney5));
  Serial.println(digitalRead(pinMoney10));
  Serial.println(digitalRead(pinMoney20));
}

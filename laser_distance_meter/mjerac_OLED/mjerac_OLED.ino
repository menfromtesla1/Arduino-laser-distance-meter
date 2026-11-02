#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

int udaljenost;
long duration;
int button=8;
int button1=9;
int trigpin=10;
int echopin=11;
int buzzer=7;

int radnja_arduina;
bool potvrda=false;
unsigned long zadnji_pritisak=0;
int duzina=0;


void setup() {
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.clearDisplay();
  pinMode(trigpin, OUTPUT);
  pinMode(echopin, INPUT);
  pinMode(button, INPUT_PULLUP);
  pinMode(button1, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT);
}


void loop() {
  zadnji_pritisak=millis();
  while(potvrda==false){
    if (digitalRead(button)==LOW){
      ++duzina;
      display.clearDisplay();
      display.setCursor(0, 0);
      display.print("izaberi udaljenost");
      display.println(duzina);
      display.display();
      zadnji_pritisak=millis();
      delay(100);
    }
    else{
      display.clearDisplay();
      display.setCursor(0, 0);
      display.print("izaberi udaljenost");
      display.println(duzina);
      display.display();
      delay(100);
    }
    if (digitalRead(button1)==LOW){
      --duzina;
      display.clearDisplay();
      display.setCursor(0, 0);
      display.print("izaberi udaljenost");
      display.println(duzina);
      display.display();
      zadnji_pritisak=millis();
      delay(100);
    }
    else{
      display.clearDisplay();
      display.setCursor(0, 0);
      display.print("izaberi udaljenost");
      display.println(duzina);
      display.display();
      delay(100);
    }
    if (millis()- zadnji_pritisak>=3000){
      potvrda=true;
    }
    else{
      display.clearDisplay();
      display.setCursor(0, 0);
      display.print("izaberi udaljenost");
      display.println(duzina);
      display.display();
      delay(100);
    }
    delay(110);
    
    
  }
  while(true){
    digitalWrite(trigpin, LOW);
    delayMicroseconds(2);

    digitalWrite(trigpin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigpin, LOW);

    duration= pulseIn(echopin, HIGH);
    udaljenost= duration*0.034/2;
    display.setTextColor(WHITE);
    display.setCursor(55,15);
    display.setTextSize(2);
    display.print(udaljenost);
    display.println(" cm");
    display.display();
    display.clearDisplay();
    delay(110);
    if (udaljenost==duzina){
      digitalWrite(buzzer, HIGH);
      delay(100);
      digitalWrite(buzzer, LOW);

    }
    else{
      digitalWrite(buzzer, LOW);
    }
  
    
  }
}
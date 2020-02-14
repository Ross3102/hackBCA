#include <LiquidCrystal.h>

LiquidCrystal lcd(2, 3, 12, 11, 10, 9);

String letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
String encodings[] = {
  ".-",
  "-...",
  "-.-.",
  "-..",
  ".",
  "..-.",
  "--.",
  "....",
  "..",
  ".---",
  "-.-",
  ".-..",
  "--",
  "-.",
  "---",
  ".--.",
  "--.-",
  ".-.",
  "...",
  "-",
  "..-",
  "...-",
  ".--",
  "-..-",
  "-.--",
  "--..",
  ".----",
  "..---",
  "...--",
  "....-",
  ".....",
  "-....",
  "--...",
  "---..",
  "----.",
  "-----"
};

const int dotLen = 20;
const int dashLen = 500;
const int between = 500;
const int betweenWords = 2500;

const int btnPin = 6;

String currentLetter = "";
String str = "";

int state = 0;
int prev = 0;

long counter = -1;

void setup() {
  lcd.begin(16, 2);
  pinMode(btnPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  state = digitalRead(btnPin);

  if (state != prev) {
    if (state == 0) {
      if (millis() - counter >= dashLen) {
        Serial.print("-");
        currentLetter += "-";
      } else if (millis() - counter >= dotLen) {
        Serial.print(".");
        currentLetter += ".";
      }
    } else if (millis() - counter >= betweenWords && counter != -1) {
      str += " ";
      lcd.print(" ");
      currentLetter = "";
    }
    counter = millis();
  }

  if (state == 0 && millis() - counter >= between) {
    for (int i=0; i<letters.length(); i++) {
      if (encodings[i] == currentLetter) {
        str += letters.charAt(i);
        lcd.print(letters.charAt(i));
        currentLetter = "";
      }
    }
  }
  
  if (str.length() == 16) {
    lcd.setCursor(0, 1);
  }
  if (str.length() == 32) {
    str = str.substring(16);
    lcd.clear();
    lcd.print(str);
    lcd.setCursor(0, 1);
  }

  prev = state;
}

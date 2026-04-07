#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Piny pro potenciometry
const int potPin1 = A2;
const int potPin2 = A3;
const int potPin3 = A4;

// Správné piny pro relé
#define START_GAME_PIN 4 // ESP ➝ relé ➝ Arduino (INPUT)
#define GAME_DONE_PIN 2  // Arduino ➝ relé ➝ ESP (OUTPUT)

// Hodnoty cílových pozic a proměnné
int target1, target2, target3;
int potValue1, potValue2, potValue3;
int position1, position2, position3;

LiquidCrystal_I2C lcd(0x27, 16, 3);

// Morseovka pro čísla 0–9
String morseCode[] = {
  "-----", ".----", "..---", "...--", "....-",
  ".....", "-....", "--...", "---..", "----."
};

// Náhodné číslo 1–9
int generateRandomPosition() {
  return random(1, 10);
}

// Vygeneruj 3 unikátní pozice
void generateUniquePositions() {
  do {
    target1 = generateRandomPosition();
    target2 = generateRandomPosition();
    target3 = generateRandomPosition();
  } while (target1 == target2 || target1 == target3 || target2 == target3);
}

// Číslo na morseovku
String numberToMorse(int number) {
  if (number >= 0 && number <= 9) {
    return morseCode[number];
  }
  return "";
}

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0));

  lcd.begin(16, 3);
  lcd.setBacklight(1);
  lcd.setCursor(0, 0);
  lcd.print("Inicializace...");

  // Nastavení pinů pro relé
  pinMode(START_GAME_PIN, INPUT);
  pinMode(GAME_DONE_PIN, OUTPUT);
  digitalWrite(GAME_DONE_PIN, LOW); // Na začátku neposíláme nic

  Serial.println(">> Kontroluji stav výstupu...");

  // Ochrana: pokud je výstupní relé (pin 2) aktivní, něco je špatně
  if (digitalRead(GAME_DONE_PIN) == HIGH) {
    Serial.println("CHYBA: Výstupní relé (pin 2) je AKTIVNÍ! Zkontroluj zapojení!");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("CHYBA RELÉ PIN 2");
    while (true); // zastaví program
  }

  lcd.clear();
  lcd.print("Cekam na ESP...");
  Serial.println(">> Cekam na START z ESP (pin 4)...");

  // Čekání na start hry od ESP
  while (digitalRead(START_GAME_PIN) == LOW) {
    delay(100); 
  }

  Serial.println(">> START potvrzen. Spoustim hru.");
  lcd.clear();
  lcd.print("Start hry!");
  delay(1000);

  // Vygeneruj cílové hodnoty
  generateUniquePositions();

  Serial.print("Pot1: "); Serial.print(target1);
  Serial.print(" | Pot2: "); Serial.print(target2);
  Serial.print(" | Pot3: "); Serial.println(target3);

  // Zobraz Morse kód na LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("P1: "); lcd.print(numberToMorse(target1));
  lcd.setCursor(0, 1);
  lcd.print("P2: "); lcd.print(numberToMorse(target2));
  lcd.setCursor(0, 2);
  lcd.print("P3: "); lcd.print(numberToMorse(target3));
  delay(2000);
}

void loop() {
  potValue1 = analogRead(potPin1);
  potValue2 = analogRead(potPin2);
  potValue3 = analogRead(potPin3);

  position1 = map(potValue1, 0, 1023, 1, 10);
  position2 = map(potValue2, 0, 1023, 1, 10);
  position3 = map(potValue3, 0, 1023, 1, 10);

  Serial.print("Pozice 1: "); Serial.print(position1);
  Serial.print(" | Pozice 2: "); Serial.print(position2);
  Serial.print(" | Pozice 3: "); Serial.println(position3);

  if (position1 == target1 && position2 == target2 && position3 == target3) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Hotovo!");

    Serial.println(">> Hra dokoncena, posilam signal ESP");

    // Pošle signál zpět na ESP přes relé (pin 2)
    digitalWrite(GAME_DONE_PIN, HIGH);
    delay(1000);
    digitalWrite(GAME_DONE_PIN, LOW);

    while (true); // hra skončila, zůstane viset
  }

  delay(1000);
}

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

// Inicializace LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

const byte ROWS = 4; // Počet řádků klávesnice
const byte COLS = 3; // Počet sloupců klávesnice

// Mapa klávesnice
char keys[ROWS][COLS] = {
  { '1', '2', '3' },
  { '4', '5', '6' },
  { '7', '8', '9' },
  { '*', '0', '#' }
};

// Piny pro řádky a sloupce
byte rowPins[ROWS] = { 9, 8, 7, 6 };
byte colPins[COLS] = { 12, 11, 10 };

// Inicializace klávesnice
Keypad kpd = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Proměnné pro hru
String userInput = "";  
int correctAnswer = 0;
String mathProblem = ""; 
int correctCount = 0;

// Definice pinů
#define START_GAME_PIN 4 // Pin pro spuštění hry (ESP -> Arduino)
#define GAME_DONE_PIN 2  // Pin pro signalizaci dokončení hry (Arduino -> ESP)

void setup() {
  Serial.begin(9600);
  
  // Inicializace LCD
  lcd.init();
  lcd.backlight();

  // Nastavení pinů
  pinMode(START_GAME_PIN, INPUT);
  pinMode(GAME_DONE_PIN, OUTPUT);
  digitalWrite(GAME_DONE_PIN, LOW); // Relé na začátku vypnuté

  // Čekání na signál od ESP
  lcd.setCursor(0, 0);
  lcd.print("Cekam na ESP...");
  Serial.println("Cekam na signal od ESP...");

  while (digitalRead(START_GAME_PIN) == LOW) {
    // Dokud ESP neposle signal, hra se nespusti
  }

  // Jakmile ESP pošle signál, hra začne
  lcd.clear();
  Serial.println("Hra zacina!");
  generateNewProblem();
}

void loop() {
  // Pokud je dosaženo 4 správných odpovědí, hra končí
  if (correctCount >= 4) {
    // Hra dokončena
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("VYBORNE!");
    Serial.println("Hra byla dokoncena.");

    // Pošleme signál zpět na ESP (1 sekunda)
    digitalWrite(GAME_DONE_PIN, HIGH);
    delay(1000);
    digitalWrite(GAME_DONE_PIN, LOW);

    // Hra končí - zůstane viset na této obrazovce
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Hotovo :)");
    
    // Neprovádí žádnou další akci - čeká na restart
    while (true) {
      // Hra je vypnutá, čeká na restart
    }
  }

  char key = kpd.getKey();

  if (key) {
    userInput += key;
    Serial.println(userInput);

    lcd.setCursor(0, 1);
    lcd.print("Odpoved: ");
    lcd.print(userInput);

    if (key == '#') {
      int answer = userInput.toInt();
      
      lcd.clear();
      lcd.setCursor(0, 0);
      
      if (answer == correctAnswer) {
        lcd.print("Spravne!");
        correctCount++;
      } else {
        lcd.print("Spatne!");
      }

      delay(3000);
      
      if (correctCount < 4) {
        generateNewProblem();
      }

      userInput = "";
    }
  }
}

void generateNewProblem() {
  int num1 = random(1, 11);
  int num2 = random(1, 11);

  if (num1 < num2) {
    int temp = num1;
    num1 = num2;
    num2 = temp;
  }
  
  int operatorType = random(1, 4);
  
  if (operatorType == 1) {
    mathProblem = String(num1) + " + " + String(num2) + " = ?";
    correctAnswer = num1 + num2;
  } else if (operatorType == 2) {
    mathProblem = String(num1) + " - " + String(num2) + " = ?";
    correctAnswer = num1 - num2;
  } else if (operatorType == 3) {
    mathProblem = String(num1) + " * " + String(num2) + " = ?";
    correctAnswer = num1 * num2;
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(mathProblem);
}

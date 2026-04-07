#define RELAY_PIN_ESP 12   // Pin D14 pro sepnutí relé na ESP
#define RELAY_PIN_ARDUINO 13 // Pin D4 pro čtení stavu relé z Arduina

void setup() {
  // Inicializace sériového portu pro komunikaci
  Serial.begin(115200);

  // Nastavení pinů
  pinMode(RELAY_PIN_ESP, OUTPUT);   // Pin pro sepnutí relé na ESP
  pinMode(RELAY_PIN_ARDUINO, INPUT); // Pin pro čtení stavu relé z Arduina

  // Sepneme relé na pinu 14 (ESP sepne relé a hra začíná)
  digitalWrite(RELAY_PIN_ESP, HIGH);
  Serial.println("Relé sepnuté. Hra začala.");


  delay(1000);
}

void loop() {
  // Čteme stav pinu pro relé z Arduina
  int relayState = digitalRead(RELAY_PIN_ARDUINO); 
   Serial.println(relayState);

  // Pokud je relé na pinu 4 sepnuté (HIGH), hra skončila
  if (relayState == HIGH) {
    Serial.println("Relé z Arduina sepnuté. Hra dokončena.");
  
    while (digitalRead(RELAY_PIN_ARDUINO) == HIGH) {
      delay(100); 
    }
  }

  delay(100); 
}

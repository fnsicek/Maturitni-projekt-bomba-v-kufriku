// Definice pinů
const int buzzerPin = 9;    // Pin pro bzučák
const int ledPin = 8;       // Pin pro LED
const int wirePin = 7;      // Pin pro detekci dotyku

void setup() {
    pinMode(buzzerPin, OUTPUT);
    pinMode(ledPin, OUTPUT);
    pinMode(wirePin, INPUT); 
}

void loop() {
    if (digitalRead(wirePin) == HIGH) { // Dotyk detekován (připojeno k plusu)
        digitalWrite(ledPin, HIGH);   // Rozsvítí LED
        tone(buzzerPin, 1000);        // Zapne bzučák (1kHz)
        delay(500);                   // Krátká prodleva
        noTone(buzzerPin);            // Vypne bzučák
        digitalWrite(ledPin, LOW);    // Zhasne LED
    }
}

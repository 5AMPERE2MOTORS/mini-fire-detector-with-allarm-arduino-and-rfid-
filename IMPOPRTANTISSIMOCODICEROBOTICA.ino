//before loading the code install MFRC522 library
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Creazione dell'oggetto MFRC522

int buzzerPin = 8;
int blue = A4;
int red = A5;
int t = 60;
#define DO_PIN 2  // Arduino's pin connected to DO pin of the flame sensor

void setup() {
  Serial.begin(9600);
  pinMode(2, OUTPUT); 
  pinMode(A5, OUTPUT);
  pinMode(A4, OUTPUT);
  pinMode(SS_PIN, OUTPUT);
  pinMode(RST_PIN, OUTPUT);
  Serial.begin(9600);
  // initialize the Arduino's pin as an input
  pinMode(DO_PIN, INPUT);
  pinMode (buzzerPin, OUTPUT);
  SPI.begin();      // Inizializzazione SPI bus
  mfrc522.PCD_Init(); // Inizializzazione della libreria MFRC522
}

void loop() {
  // Cerca nuove card
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    // Lettura del UID
    Serial.print(F("Card UID:"));
    String content = "";
    byte letter;
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
      Serial.print(mfrc522.uid.uidByte[i], HEX);
      content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
      content.concat(String(mfrc522.uid.uidByte[i], HEX));
    }
    Serial.println();
    Serial.print("Message : ");
    content.toUpperCase();
    // Verifica se la card è autorizzata
    if (content.substring(1) == "03 87 BA 34") { // Modificare questo UID con quello della tua card
      Serial.println("Accesso consentito");
      // Esegui il codice quando l'accesso è consentito
      int flame_state = digitalRead(DO_PIN);
      if (flame_state == HIGH) {
        Serial.println("The flame is present => The fire is detected");
        policeSirenLights();
        digitalWrite(buzzerPin, HIGH);
        delay(10);
        digitalWrite(buzzerPin, HIGH);
        delay(100);
      } else {
        Serial.println("The flame is NOT present => The fire is NOT detected");
      }
    } else {
      Serial.println("Accesso non consentito");
    }
    delay(1000); // Ritardo prima di cercare una nuova card
  }
}

void policeSirenLights() {
  digitalWrite(A4, HIGH);
  delay(t);
  digitalWrite(A4, LOW);
  delay(t);
  
  digitalWrite(A4, HIGH);
  delay(t);
  digitalWrite(A4, LOW);
  delay(t);
  
  digitalWrite(A4, HIGH);
  delay(t);
  digitalWrite(A4, LOW);
  delay(t);
  
  digitalWrite(A5, HIGH);
  delay(t);
  digitalWrite(A5, LOW);
  delay(t);
  
  digitalWrite(A5, HIGH);
  delay(t);
  digitalWrite(A5, LOW);
  delay(t);
  
  digitalWrite(A5, HIGH);
  delay(t);
  digitalWrite(A5, LOW);
  delay(t);
  
  digitalWrite(A4, HIGH);
  digitalWrite(A5, HIGH);
  delay(t);
  digitalWrite(A4, LOW);
  digitalWrite(A5, LOW);
  delay(t);
  
  digitalWrite(A4, HIGH);
  digitalWrite(A5, HIGH);
  delay(t);
  digitalWrite(A4, LOW);
  digitalWrite(A5, LOW);
  delay(t);
  
  digitalWrite(A4, HIGH);
  digitalWrite(A5, HIGH);
  delay(t);
  digitalWrite(A4, LOW);
  digitalWrite(A5, LOW);
  delay(t);
  
  digitalWrite(A4, HIGH);
  digitalWrite(A5, HIGH);
  delay(t);
  digitalWrite(A4, LOW);
  digitalWrite(A5, LOW);
  delay(t);
}

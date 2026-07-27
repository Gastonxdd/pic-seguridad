#include <SPI.h>
#include <MFRC522.h>

// --- PINES PARA ARDUINO MEGA ---
#define RST_PIN  9
#define SS_PIN   53 // Pin SDA/SS en el Mega

// Creamos el objeto para el lector RFID
MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600); // Iniciamos la comunicación serial
  while (!Serial);    // Esperamos a que abra el monitor serial (útil en algunas placas)
  
  SPI.begin();        // Iniciamos el bus SPI
  mfrc522.PCD_Init(); // Iniciamos el lector MFRC522

  Serial.println("--- TEST DE MÓDULO RFID MFRC522 ---");
  
  // ESTA ES LA LÍNEA MÁGICA PARA DEBUGGEAR:
  // Lee la versión del firmware del chip. Si los cables están mal, dirá 0x00 o 0xFF.
  mfrc522.PCD_DumpVersionToSerial(); 
  
  Serial.println("Acerca una tarjeta o llavero al lector...");
  Serial.println("-----------------------------------------");
}

void loop() {
  // 1. Revisamos si hay una nueva tarjeta presente
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return; // Si no hay tarjeta, volvemos a empezar el loop
  }

  // 2. Seleccionamos una de las tarjetas para leerla
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return; // Si no se pudo leer, volvemos a empezar
  }

  // 3. Si llegó hasta acá, ¡leyó algo! Mostramos el UID por el monitor serial
  Serial.print("¡Tarjeta detectada! UID en HEX: ");
  
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
  }
  
  Serial.println(); // Salto de línea

  // 4. Detenemos la lectura de esta tarjeta para no leerla 1000 veces por segundo
  mfrc522.PICC_HaltA();
}

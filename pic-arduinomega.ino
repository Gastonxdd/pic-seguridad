#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h> 

// --- PINES ---
#define RST_PIN  9
#define SS_PIN   53 // <--- ¡ÚNICO CAMBIO! Pin 53 para Arduino Mega
const int pinRojo = 6;
const int pinVerde = 5;
const int pinAzul = 4;
const int pinBuzzer = 8;
const int pinTrig = 2; 
const int pinEcho = 3; 
const int pinServo = 7; 

// --- OBJETOS ---
MFRC522 mfrc522(SS_PIN, RST_PIN);
Servo miPuerta;

// --- CONFIGURACIÓN SERVO ---
const int ANGULO_ABIERTO = 0;
const int ANGULO_CERRADO = 170;

// --- TUS IDs ---
byte ID_Triangulo[4] = {0x63, 0xC6, 0x33, 0x16};
byte ID_Estrella[4]  = {0x52, 0xA1, 0x94, 0x04};

// --- CONFIGURACIÓN DE DISTANCIA ---
const int DISTANCIA_PISO = 18; 
const int MARGEN_SEGURIDAD = 3; 
const int UMBRAL_CORTE = DISTANCIA_PISO - MARGEN_SEGURIDAD; 

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();

  pinMode(pinRojo, OUTPUT);
  pinMode(pinVerde, OUTPUT);
  pinMode(pinAzul, OUTPUT);
  pinMode(pinBuzzer, OUTPUT);
  pinMode(pinTrig, OUTPUT);
  pinMode(pinEcho, INPUT);

  miPuerta.attach(pinServo);
  miPuerta.write(ANGULO_CERRADO); 

  colorRGB(255, 255, 255); 
  Serial.println("SISTEMA INICIADO.");
}

void loop() {
  // MEDIDA ANTI-CONGELAMIENTO: Reiniciar comunicación con lector en cada vuelta
  mfrc522.PCD_Init(); 

  // 1. Lectura RFID
  if (!mfrc522.PICC_IsNewCardPresent()) return;
  if (!mfrc522.PICC_ReadCardSerial()) return;

  // 2. Validación
  if (compararUID(mfrc522.uid.uidByte, ID_Triangulo) || 
      compararUID(mfrc522.uid.uidByte, ID_Estrella)) {
    accesoConcedido(); 
  } else {
    accesoDenegado();
  }

  mfrc522.PICC_HaltA();
  colorRGB(255, 255, 255); 
}

// --- FUNCIONES ---

void accesoConcedido() {
  Serial.println(" -> ACCESO PERMITIDO: Abriendo...");
  
  miPuerta.write(ANGULO_ABIERTO); 
  colorRGB(0, 255, 0); 
  
  tone(pinBuzzer, 1500, 100); 
  delay(150);
  tone(pinBuzzer, 1500, 100); 

  // IMPORTANTE: Esperar a que el servo llegue físicamente y el voltaje se calme
  // antes de encender el sensor ultrasónico.
  delay(1000); 
  
  // Tiempo extra de puerta abierta
  delay(2000); 

  // LÓGICA DE SEGURIDAD CON TIMEOUT (Para evitar bucle infinito)
  long distanciaActual = medirDistancia();
  unsigned long tiempoInicioEspera = millis(); // Guardamos la hora actual
  
  // Esperamos mientras haya obstáculo Y no hayan pasado más de 10 segundos
  while (distanciaActual < UMBRAL_CORTE && distanciaActual > 0) {
    
    // Si pasaron 10 segundos y sigue detectando algo, asumimos error y salimos
    if (millis() - tiempoInicioEspera > 10000) {
      Serial.println("TIEMPO EXCEDIDO. Forzando cierre...");
      tone(pinBuzzer, 500, 500); // Sonido de advertencia grave
      break; 
    }

    Serial.print("OBSTÁCULO (");
    Serial.print(distanciaActual);
    Serial.println("cm) - ESPERANDO...");
    
    colorRGB(0, 0, 0); delay(100);
    colorRGB(0, 255, 0); delay(400);
    
    distanciaActual = medirDistancia();
  }

  Serial.println("Cerrando puerta...");
  miPuerta.write(ANGULO_CERRADO);
  delay(1000); 
}

void accesoDenegado() {
  Serial.println(" -> ACCESO DENEGADO");
  colorRGB(255, 0, 0); 
  tone(pinBuzzer, 200, 800); 
  delay(1000);
  miPuerta.write(ANGULO_CERRADO); 
}

boolean compararUID(byte lectura[], byte usuario[]) {
  for (byte i = 0; i < 4; i++) {
    if (lectura[i] != usuario[i]) return false;
  }
  return true;
}

void colorRGB(int r, int g, int b) {
  analogWrite(pinRojo, r);
  analogWrite(pinVerde, g);
  analogWrite(pinAzul, b);
}

long medirDistancia() {
  digitalWrite(pinTrig, LOW);
  delayMicroseconds(2);
  digitalWrite(pinTrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinTrig, LOW);
  
  long duracion = pulseIn(pinEcho, HIGH, 25000); // Bajamos timeout a 25ms
  if (duracion == 0) return 999; 
  
  return duracion * 0.034 / 2;
}

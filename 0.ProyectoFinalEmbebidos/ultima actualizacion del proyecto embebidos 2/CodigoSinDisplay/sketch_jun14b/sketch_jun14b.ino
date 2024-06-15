#include <Arduino.h>

const int startButtonPin = 9;
const int resetButtonPin = 10;
const int ledPin = 2;
const int relayPin = 27; // Pin para controlar el relé

volatile bool startFlag = false;
volatile bool resetFlag = false;
bool running = false; // Indicador de si el contador está en ejecución
unsigned long startTime = 0;
unsigned long duration = 30000; // 30 segundos

const unsigned long debounceDelay = 100; // Tiempo de debounce en milisegundos
volatile unsigned long lastStartPressTime = 0;
volatile unsigned long lastResetPressTime = 0;

void IRAM_ATTR onStartButtonPress() {
  unsigned long currentTime = millis();
  if (currentTime - lastStartPressTime > debounceDelay) {
    startFlag = true;
    lastStartPressTime = currentTime;
  }
}

void IRAM_ATTR onResetButtonPress() {
  unsigned long currentTime = millis();
  if (currentTime - lastResetPressTime > debounceDelay) {
    resetFlag = true;
    lastResetPressTime = currentTime;
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(startButtonPin, INPUT_PULLUP);
  pinMode(resetButtonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  pinMode(relayPin, OUTPUT);

  digitalWrite(relayPin, LOW); // Inicialmente apaga el relé

  attachInterrupt(digitalPinToInterrupt(startButtonPin), onStartButtonPress, FALLING);
  attachInterrupt(digitalPinToInterrupt(resetButtonPin), onResetButtonPress, FALLING);
}

void loop() {
  if (startFlag) {
    startFlag = false;
    startTime = millis();
    running = true;
    digitalWrite(ledPin, HIGH);
    digitalWrite(relayPin, HIGH); // Enciende el relé
    Serial.println("---------------Rele encendido.------------");
    Serial.println("Contador iniciado.");
    Serial.flush(); // Asegura que se envíen todos los datos antes de continuar
  }

  if (resetFlag) {
    resetFlag = false;
    running = false;
    digitalWrite(ledPin, LOW);
    digitalWrite(relayPin, LOW); // Apaga el relé
    Serial.println("---------------Rele apagado.------------");
    Serial.println("Contador reseteado.");
    Serial.flush(); // Asegura que se envíen todos los datos antes de continuar
  }

  if (running) {
    unsigned long elapsedTime = millis() - startTime;
    Serial.print("Tiempo transcurrido: ");
    Serial.print(elapsedTime);
    Serial.println(" ms");
  }

  if (millis() - startTime >= duration && digitalRead(ledPin) == HIGH) {
    running = false;
    digitalWrite(ledPin, LOW);
    digitalWrite(relayPin, LOW); // Apaga el relé
    Serial.println("---------------Rele Apagado.------------");
    Serial.println("Contador finalizado.");
    Serial.flush(); // Asegura que se envíen todos los datos antes de continuar
  }

  // Pequeña pausa para evitar un loop demasiado rápido
  delay(1000); // Mostrar el tiempo transcurrido cada segundo
}
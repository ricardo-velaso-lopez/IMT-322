#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>

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

// Definición de pines para ESP32 y pantalla TFT
#define TFT_CS    5 // Pin de chip select
#define TFT_RST   4 // Pin de reset
#define TFT_DC    2 // Pin de RS/DC (Data/Command)

// Inicializar la pantalla ST7735 con SPI
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

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

  // Inicializar SPI y pantalla
  SPI.begin();
  tft.initR(INITR_BLACKTAB); // Inicialización específica para pantalla ST7735
  tft.fillScreen(ST7735_BLACK); // Fondo negro
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

    // Mostrar mensajes en la pantalla TFT
    tft.setTextColor(ST7735_WHITE); // Color de texto blanco
    tft.setTextSize(1); // Tamaño del texto
    tft.setCursor(10, 30); // Posición del texto en la pantalla
    tft.println("Rele encendido");
    tft.println("Contador iniciado");
  }

  if (resetFlag) {
    resetFlag = false;
    running = false;
    digitalWrite(ledPin, LOW);
    digitalWrite(relayPin, LOW); // Apaga el relé
    Serial.println("---------------Rele apagado.------------");
    Serial.println("Contador reseteado.");
    Serial.flush(); // Asegura que se envíen todos los datos antes de continuar

    // Mostrar mensajes en la pantalla TFT
    tft.setTextColor(ST7735_WHITE); // Color de texto blanco
    tft.setTextSize(1); // Tamaño del texto
    tft.setCursor(10, 30); // Posición del texto en la pantalla
    tft.println("Rele apagado");
    tft.println("Contador reseteado");
  }

  if (running) {
    unsigned long elapsedTime = millis() - startTime;
    Serial.print("Tiempo transcurrido: ");
    Serial.print(elapsedTime);
    Serial.println(" ms");

    // Mostrar tiempo transcurrido en la pantalla TFT
    tft.setTextColor(ST7735_WHITE); // Color de texto blanco
    tft.setTextSize(1); // Tamaño del texto
    tft.setCursor(10, 60); // Posición del texto en la pantalla
    tft.print("Tiempo: ");
    tft.print(elapsedTime / 1000); // Mostrar tiempo en segundos
    tft.println(" s");
  }

  if (millis() - startTime >= duration && digitalRead(ledPin) == HIGH) {
    running = false;
    digitalWrite(ledPin, LOW);
    digitalWrite(relayPin, LOW); // Apaga el relé
    Serial.println("---------------Rele Apagado.------------");
    Serial.println("Contador finalizado.");
    Serial.flush(); // Asegura que se envíen todos los datos antes de continuar

    // Mostrar mensajes en la pantalla TFT
    tft.setTextColor(ST7735_WHITE); // Color de texto blanco
    tft.setTextSize(1); // Tamaño del texto
    tft.setCursor(10, 90); // Posición del texto en la pantalla
    tft.println("Rele apagado");
    tft.println("Contador finalizado");
  }

  // Pequeña pausa para evitar un loop demasiado rápido
  delay(1000); // Mostrar el tiempo transcurrido cada segundo
}


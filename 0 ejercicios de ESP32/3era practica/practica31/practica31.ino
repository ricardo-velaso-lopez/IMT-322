// Definición de pines para pulsadores
#define      CONT   23
#define      RESET  22
#define      BAUDRATE 9600
#define      LED  12  
// Variables para el manejo de pulsadores

volatile unsigned long lasttime = 0;
volatile unsigned long debounceDelay = 10; // Tiempo de antirrebote

// Contador
volatile int contador = 0;

void setup() {
  // Configurar pines de entrada para pulsadores
  pinMode(CONT, INPUT_PULLUP);
  pinMode(RESET, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
  // Configurar interrupciones para pulsadores
  attachInterrupt(digitalPinToInterrupt(CONT), Contador, RISING);
  attachInterrupt(digitalPinToInterrupt(RESET), reset, RISING);

  // Iniciar comunicación serial 
  Serial.begin(BAUDRATE);
}

void loop() {
  // Verificar si el pulsador 1 fue presionado
  digitalWrite(LED,1);
  delay(400);
  digitalWrite(LED,0);
  delay(400);
}

// Función de interrupción para el pulsador 1
void Contador() {

  if (millis() - lasttime > debounceDelay) {
    contador++;
    lasttime = millis();
    Serial.println(contador);
  }
}

// Función de interrupción para el pulsador 2
void reset() {
  if (millis() - lasttime > debounceDelay) {
    contador=0;
    lasttime = millis();
    Serial.println("Contador reiniciado");
  }
}












// Variables para el manejo de pulsadores
volatile unsigned long lasttime = 0;
volatile unsigned long debounceDelay = 10;  // Tiempo de antirrebote
volatile bool resetRequested = false;       // Bandera para indicar si se solicita reinicio




#define led1 12
#define pul1 23
#define pul2 22



void setup() {

  pinMode(led1, OUTPUT);
  pinMode(pul1, INPUT_PULLUP);
  pinMode(pul2, INPUT_PULLUP);

  Serial.begin(9600);

  //configuracion de interrupciones para los pulsadores
  attachInterrupt(digitalPinToInterrupt(pul1), ContandoAndo, FALLING);
  
}

void loop() {
}


//Declarmos la clase

void ContandoAndo() {

  if (millis() - lasttime > debounceDelay) {

    if (digitalRead(pul1) == LOW) {
      digitalWrite(led1,!digitalRead(led1));
    }
  }
}




// Variables para el manejo de pulsadores
volatile unsigned long lasttime = 0;
volatile unsigned long debounceDelay = 10;  // Tiempo de antirrebote
volatile bool resetRequested = false;       // Bandera para indicar si se solicita reinicio



//declaramos los leds y pulsadores

#define led1 12
#define led2 14
#define led3 27
int temp = 1500;

#define pul1 23


void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(pul1, INPUT_PULLUP);

  //configuracion de interrupciones para los pulsadores
  attachInterrupt(digitalPinToInterrupt(pul1), SecuenciandoAndo, FALLING);
}

void loop() {
  digitalWrite(led2, LOW);
  digitalWrite(led1, HIGH);
  digitalWrite(led3, LOW);
  delay(temp);

  digitalWrite(led2, HIGH);
  digitalWrite(led1, LOW);
  delay(temp);

  digitalWrite(led3, HIGH);
  digitalWrite(led2, LOW);
  delay(temp);
}








//Creamos la clase SecuanciandoAndo

void SecuenciandoAndo() {
  if (millis() - lasttime > debounceDelay) {


    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    delay(temp);

    digitalWrite(led3, HIGH);
    digitalWrite(led1, LOW);
    delay(temp);

    digitalWrite(led2, HIGH);
    digitalWrite(led3, LOW);
    delay(temp);
  }
}

#include "funciones.h"
#define BAUDRATE 115200
//DECLARACION DE VARUIABLES
#define pull1 23
#define pull2 22
#define pull3 19
#define pull4 18
int valor = 0;

int dinero = 20;
//Comando de Antirevote
volatile uint16_t cont = 0;
volatile unsigned long lasttime = 0;
volatile unsigned long debounceDelay = 2000;
volatile bool btnflag = false;
volatile bool btnflag2 = false;
int piso;

typedef enum {
  reposo,
  op1,
  op2,
  op3,
  op4
} Menu;
Menu opciones = reposo;
void setup() {
  // put your setup code here, to run once:
  pinMode(pull1, INPUT_PULLUP);
  pinMode(pull2, INPUT_PULLUP);
  pinMode(pull3, INPUT_PULLUP);
  pinMode(pull4, INPUT_PULLUP);


  attachInterrupt(digitalPinToInterrupt(pull1), soda1, RISING);
  attachInterrupt(digitalPinToInterrupt(pull2), soda2, RISING);
  attachInterrupt(digitalPinToInterrupt(pull3), soda3, RISING);
  attachInterrupt(digitalPinToInterrupt(pull4), retiro, RISING);

  Serial.begin(BAUDRATE);
    Serial.println("Bienvenido por favor selecciona la bebida");

}

void loop() {
  switch (opciones) {
    case reposo:

      break;
    case op1:
      if (dinero > valor) {
        Serial.println("se esta llenado el baso con la bebida soda1");
        mostrarBarraDeCarga(2000);

        opciones = reposo;
      } else {
        Serial.println("no le alcanza el dinero para seleccionar esta bebida");
      }
      break;
    case op2:
      if (dinero > valor) {
        mostrarBarraDeCarga(4000);
        Serial.println("se esta llenado el baso con la bebida soda2");
        opciones = reposo;
      } else {
        Serial.println("no le alcanza el dinero para seleccionar esta bebida");
      }
      break;
    case op3:
      if (dinero > valor) {
        mostrarBarraDeCarga(6000);
        Serial.println("se esta llenado el baso con la bebida soda3");
        opciones = reposo;
      } else {
        Serial.println("no le alcanza el dinero para seleccionar esta bebida");
      }
      break;
    case op4:
      if (dinero > valor) {
        Serial.println("se esta retirado el vaso de la maquina de soda");
        opciones = reposo;
      }
  }
}
void soda1() {
  if (millis() - lasttime > debounceDelay) {
    lasttime = millis();
    valor = 2;
    opciones = op1;
  }
}

void soda2() {
  if (millis() - lasttime > debounceDelay) {
    lasttime = millis();
    valor = 5;
    opciones = op2;
  }
}

void soda3() {
  if (millis() - lasttime > debounceDelay) {
    lasttime = millis();
    valor = 7;
    opciones = op3;
  }
}
void retiro() {
  if (millis() - lasttime > debounceDelay) {
    lasttime = millis();
    opciones = op4;
  }
}
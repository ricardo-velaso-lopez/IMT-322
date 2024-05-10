typedef enum {
  MOVIMIENTO,
  PISO1,
  PISO2,
  PISO3
}estados;
estados ascensor = PISO1;
bool mostrar_mensaje = true;
int piso_actual=0;
int piso_nuevo=0;

void setup() 
{
  Serial.begin(9600);
  Serial.println();
}

void loop() 
{
  switch (ascensor)
  {
    case PISO1:
    piso_actual=1;
    movimiento();
    break;
    case PISO2:
    piso_actual=2;
    movimiento();
    break;
    case PISO3:
    piso_actual=3;
    movimiento();
    break;
    case MOVIMIENTO:
    if (piso_nuevo>piso_actual)
    {
      subir();
    }
    else
    {
      bajar();
    }
    break;
  }
}

void movimiento()
{
  if (mostrar_mensaje)
  {
    Serial.print("Usted se encuentra en el piso ");
    Serial.print(piso_actual);
    Serial.println(".");
    Serial.println("Si desea cambiar de piso, ingrese el número de piso al que desea ir.");
  }
  mostrar_mensaje=false;
  piso_nuevo=Serial.parseInt();
  if (piso_nuevo==1 || piso_nuevo==2 || piso_nuevo==3)
  {
    if (piso_nuevo!=piso_actual)
    {
      ascensor = MOVIMIENTO;
      mostrar_mensaje=true;
    }
    else
    {
      Serial.println("Usted se encuentra en el piso solicitado, si desea cambiar de piso, ingrese otro.");
    }
  }
  else if (piso_nuevo!=0)
  {
    Serial.println("El piso ingresado no existe, ingrese otro.");
  }
}

void subir()
{
  for (int n=piso_actual; n<piso_nuevo; n++)
  {
    for (int i=0; i<5; i++)
    {
      Serial.println("//SUBIENDO//");
      delay(300);
    }
  }
  Serial.println("Usted llegó al piso solicitado.");
  if (piso_nuevo==1)
  {
    ascensor=PISO1;
  }
  if (piso_nuevo==2)
  {
    ascensor=PISO2;
  }
  if (piso_nuevo==3)
  {
    ascensor=PISO3;
  }
}

void bajar()
{
  for (int n=piso_actual; n>piso_nuevo; n--)
  {
    for (int i=0; i<5; i++)
    {
      Serial.println("//BAJANDO//");
      delay(300);
    }
  }
  Serial.println("Usted llegó al piso solicitado.");
  if (piso_nuevo==1)
  {
    ascensor=PISO1;
  }
  if (piso_nuevo==2)
  {
    ascensor=PISO2;
  }
  if (piso_nuevo==3)
  {
    ascensor=PISO3;
  }
}
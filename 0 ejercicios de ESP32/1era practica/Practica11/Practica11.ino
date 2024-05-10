
//declaramos los leds 

#define led1 12
#define led2 14
#define led3 27

void setup() {
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);


}

void loop() {
  digitalWrite(led1,HIGH);
  digitalWrite(led3,LOW);
  delay(800);

  digitalWrite(led2,HIGH);
  digitalWrite(led1,LOW);
  delay(800);

  digitalWrite(led3,HIGH);
   digitalWrite(led2,LOW);
  delay(800);
}

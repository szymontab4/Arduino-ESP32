#include<Servo.h>

Servo serwo;
float potencjometr;
int obrot;

void setup() {
  // put your setup code here, to run once:
  serwo.attach(9);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  potencjometr=analogRead(A5);
  Serial.println(potencjometr);
  obrot=(potencjometr/1023.0) * 180.0;
  serwo.write(obrot);
  delay(20);
}

#include<Servo.h>

Servo serwomechanizm;
int pozycja=0;
String pom;

void setup() {
  // put your setup code here, to run once:
  serwomechanizm.attach(9);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  
if(Serial.available()>0)
{
  pom=Serial.readStringUntil('\n');
  pozycja=pom.toInt();

  if(pozycja<180 && pozycja>=0)
  {
    serwomechanizm.write(pozycja);
  }
  else
  {
    Serial.println("Liczba spoza zakresu obortu serwa");
  }
}

  
  

}

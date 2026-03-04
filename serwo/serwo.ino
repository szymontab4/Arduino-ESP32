#include<Servo.h>

Servo serwomechanizm;
int pozycja=0, zmiana=170;

void setup() {
  // put your setup code here, to run once:
  serwomechanizm.attach(9);
  System.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  

  if(pozycja<180)
    serwomechanizm.write(pozycja);
  else
    pozycja=0;

  pozycja+=zmiana;
  delay(1000);
  

}

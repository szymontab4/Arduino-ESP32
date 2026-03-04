int potencjometr, WartoscPrzycisk, dane;
String dane_string;

#define ledczer 8
#define ledzol1 9
#define ledzol2 10
#define ledziel 11
#define przycisk 12

void reset()
{
  pinMode(ledczer, OUTPUT);
  pinMode(ledzol1, OUTPUT);
  pinMode(ledzol2, OUTPUT);
  pinMode(ledziel, OUTPUT);
}

void setup() {
  // put your setup code here, to run once:
  pinMode(ledczer, OUTPUT);
  pinMode(ledzol1, OUTPUT);
  pinMode(ledzol2, OUTPUT);
  pinMode(ledziel, OUTPUT);
  pinMode(przycisk, INPUT_PULLUP);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i=0; i<3;)
  {
    if(digitalRead(przycisk)==LOW)
    {
      potencjometr=analogRead(A5);
      
      if(Serial.available()>0)
      {
        dane_string=Serial.readStringUntil('\n');
        dane=dane_string.toInt();
        if((potencjometr-dane)>-50 && (potencjometr-dane)<50)
        {
          Serial.println("Wynik poprawny!");
          digitalWrite(ledczer, LOW);
          digitalWrite(ledzol1, LOW);
          digitalWrite(ledzol2, LOW);
          digitalWrite(ledziel, HIGH);
          i=4;
        }
        else
        {
          i++;
          if(i==1)
          digitalWrite(ledzol1, HIGH);
          
          if(i==2)
          digitalWrite(ledzol2, HIGH);

          if(i==3)
          digitalWrite(ledczer, HIGH);
        
        }
      }

      delay(500);
    }

    

  }

  //Serial.println(prog);
  //Serial.println(odczytana);

  

}

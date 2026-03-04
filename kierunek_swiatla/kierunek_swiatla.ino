int fot1, fot2;
int tab[5]={8,9,10,11,12};

void reset()
{
  for(int i=0; i<5; i++)
  {
    digitalWrite(tab[i], LOW);
  }
}

void setup() {
  // put your setup code here, to run once:
  for(int i=0; i<5; i++)
  {
    pinMode(tab[i], OUTPUT);
    digitalWrite(tab[i], LOW);
  }

  Serial.begin(9600);


}

void loop() {
  // put your main code here, to run repeatedly:
  fot1=analogRead(A5);
  fot2=analogRead(A4);
  Serial.println(fot1);
  Serial.println(fot2);

  int roznica=fot1-fot2;
  if(fot1>fot2)
  {
    if(roznica>150)
    {
      digitalWrite(8, HIGH);
    }
    else
    {
      if(roznica>50)
      {
        digitalWrite(9, HIGH);
      }
      else
      digitalWrite(10, HIGH);
    }
  }
  else
  {
    if(roznica<-150)
    {
      digitalWrite(12, HIGH);
    }
    else
    {
      if(roznica<-50)
      {
        digitalWrite(11, HIGH);
      }
      else
      {
        digitalWrite(10, HIGH);
      }
    }
  }
  delay(200);
  reset();
}

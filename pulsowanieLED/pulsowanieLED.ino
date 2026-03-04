void pulsowanieLED(int pin, int ilosc_migniec, int czas_wlaczona, int czas_wylaczona)
{
  int i;

  for(int j=0; j<ilosc_migniec; j++)
  {
    for(i=0; i<250; i+=5)
    {
      analogWrite(pin, i);
      delay(20);
    }
    delay(czas_wlaczona);

    for(;i>=0; i-=5)
    {
      analogWrite(pin, i);
      delay(20);
    }
    delay(czas_wylaczona);
  }
}

void setup() { 
  pinMode(9, OUTPUT);

  pulsowanieLED(9, 19, 1000, 1000);

} 

void loop()  { 
                        
}
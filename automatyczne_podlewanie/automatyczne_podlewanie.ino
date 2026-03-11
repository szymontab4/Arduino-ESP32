const int pompa=4, zasilanie=2, odczyt=A0;

void setup() {
  // put your setup code here, to run once:
  pinMode(pompa, OUTPUT);
  pinMode(zasilanie, OUTPUT);
  pinMode(odczyt, INPUT);
  Serial.begin(9600);

  
}

void loop() {
  delay(2000);
  digitalWrite(pompa, HIGH);
  delay(500);
  digitalWrite(pompa, LOW);
  for(int i=0; i<5; i++)
  {
    delay(1000);
    digitalWrite(pompa, HIGH);
    delay(2000);
    digitalWrite(pompa, LOW);
  }
  // put your main code here, to run repeatedly:
  /*digitalWrite(zasilanie, HIGH);
  delay(500);
  int wartosc=analogRead(odczyt);
  Serial.println(wartosc);
  digitalWrite(zasilanie, LOW);
  if(wartosc>2000);
  {
    digitalWrite(pompa, HIGH);
    delay(5000);
    digitalWrite(pompa, LOW);
  }
  delay(5000);*/
}

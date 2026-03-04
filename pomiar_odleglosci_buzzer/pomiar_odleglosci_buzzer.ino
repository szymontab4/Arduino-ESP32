#define trigPin 12
#define echoPin 11

int wynik;

void setup()
{
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
}

void loop()
{
  wynik=pomiar_odleglosci();
  Serial.println(wynik);
  if(wynik<100)
  {
    digitalWrite(13,HIGH);
    delay(100);
    digitalWrite(13, LOW);
  }
}

int pomiar_odleglosci()
{
  int wynik;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  wynik=pulseIn(echoPin, HIGH);
  wynik/=58;
  delay(100);
  return wynik;
}
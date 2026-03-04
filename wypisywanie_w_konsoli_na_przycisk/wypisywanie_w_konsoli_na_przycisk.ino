int potencjometr, fot1, fot2;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(8, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(8)==LOW)
  {
    potencjometr=analogRead(A3);
    fot1=analogRead(A4);
    fot2=analogRead(A5);

    Serial.print("\n fot1: ");
    Serial.print(fot1, DEC);
    Serial.print("  fot2: ");
    Serial.print(fot2, DEC);
    Serial.print("  potencjometr: ");
    Serial.print(potencjometr, DEC);
    delay(200);
  }
}

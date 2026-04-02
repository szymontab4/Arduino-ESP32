#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include<WiFi.h>
#include<HTTPClient.h>



#define I2C_SDA 3
#define I2C_SCL 4

Adafruit_BME280 bme;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin(I2C_SDA, I2C_SCL);
  bme.begin(0x76, &Wire);

}



void loop() {
  // put your main code here, to run repeatedly:
  //odczyty
  double temp=bme.readTemperature();
  Serial.println(temp);

  double hum=bme.readHumidity();
  Serial.println(hum);

  double cis=bme.readPressure()/100.0F;
  Serial.println(cis);

  delay(5000);
}

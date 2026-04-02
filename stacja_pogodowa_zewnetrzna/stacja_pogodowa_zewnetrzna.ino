#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include<WiFi.h>
#include<HTTPClient.h>
#include<esp_now.h>
#include<esp_wifi.h>


uint8_t adresmac[]={0xE8, 0x3D, 0xC1, 0x87, 0x7C, 0xB0};


#define I2C_SDA 3
#define I2C_SCL 4
#define uS_TO_S_FACTOR 1000000ULL  // Conversion factor for micro seconds to seconds
#define TIME_TO_SLEEP  60 //w sekundach

Adafruit_BME280 bme;

typedef struct wiadomosc{
  double temperatura;
  double wilgotnosc;
  double cisnienie;
};
struct wiadomosc daneBME280;

esp_now_peer_info_t peerInfo;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin(I2C_SDA, I2C_SCL);
  bme.begin(0x76, &Wire);

  WiFi.mode(WIFI_STA);
  esp_wifi_set_channel(1, WIFI_SECOND_CHAN_NONE); // Set channel to 1
  
  if (esp_now_init() != ESP_OK) return;

  memcpy(peerInfo.peer_addr, adresmac, 6);
  peerInfo.channel = 1;
  peerInfo.encrypt = false;
  
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Nie udalo sie dodac odbiornika");
    return;
  }

  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
}



void loop() {
  // put your main code here, to run repeatedly:
  //odczyty
  delay(1000); //aby miec dobre odczyty
  double temp=bme.readTemperature();
  Serial.println(temp);

  double hum=bme.readHumidity();
  Serial.println(hum);

  double cis=bme.readPressure()/100.0F;
  Serial.println(cis);

  daneBME280.temperatura=temp;
  daneBME280.wilgotnosc=hum;
  daneBME280.cisnienie=cis;

  //wysylanie
  esp_err_t result = esp_now_send(adresmac, (uint8_t *) &daneBME280, sizeof(daneBME280));
  if(result==ESP_OK)
  Serial.println("Udalo sie wyslac");
  else
  Serial.println("Nie udalo sie wyslac");

  delay(1000);
  esp_deep_sleep_start();
}

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include<WiFi.h>
#include<HTTPClient.h>
#include<esp_now.h>
#include<esp_wifi.h>


const char* ssid = "FunBox2-33BF";
const char* password = "";

String pobierzSuroweDane(String url) {
  HTTPClient http;
  String payload = "";

  //pobieranie danych o jakosci powietrza ze strony, poprzez wlasny kod w google
  http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
  if (http.begin(url)) {
    int httpCode = http.GET();
    if (httpCode == HTTP_CODE_OK) {
      payload = http.getString();
    }
    http.end();
  }
  return payload;
}


//struktura dla odbierania danych z zewnatrz
typedef struct wiadomosc{
  double temperatura_out;
  double wilgotnosc_out;
  double cisnienie_out;
};
struct wiadomosc daneBME280;

//funkcja do odbioru danych
void dataRecv(const esp_now_recv_info_t *esp_now_info, const uint8_t *incomingData, int len){
  memcpy(&daneBME280, incomingData, sizeof(wiadomosc));
}


#define I2C_SDA 3
#define I2C_SCL 4

Adafruit_BME280 bme;
Adafruit_SH1106G ekran(128, 64, &Wire, -1);

void setup() {
  // put your setup code here, to run once:
  //wywolanie wszysystkiego i inicjalizacja
  Serial.begin(9600);
  Wire.begin(I2C_SDA, I2C_SCL);
  bme.begin(0x76, &Wire);
  ekran.begin(0x3C, true);
  ekran.setTextSize(1);
  ekran.setTextColor(SH110X_WHITE);
  ekran.setContrast(0);

  //polaczenie z wifi
  WiFi.begin(ssid, password);
  unsigned long startAttemptTime = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 10000) {
    delay(500);
    Serial.print(".");
  }

  //inicjalizacja esp now
  WiFi.mode(WIFI_STA);
  
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_register_recv_cb(dataRecv);
}

//wywolanie elementow do stopera i jakosci powietrza
unsigned long czasostatni=0;
const unsigned long minuta=60000;
String pm25="0";
String pm10="0";
String jakosc="Brak";

void loop() {
  // put your main code here, to run repeatedly:
  //odczyty
  double temp=bme.readTemperature();
  //Serial.println(temp);

  double hum=bme.readHumidity();
  //Serial.println(hum);

  double cis=bme.readPressure()/100.0F;
  //Serial.println(cis);



  //wczytanie jakosci powietrza
  unsigned long teraz=millis();
  if(teraz-czasostatni>=minuta)
  {
    String dane=pobierzSuroweDane("https://script.google.com/macros/s/AKfycbwgFNFWqKAJGSK6iGZ5CNQK-fGm3TDS_L6GleTPogITNX_HnC3Qtq9gQkgp4JmTq1A0iw/exec");
    if(dane.length()>0)
    {
      int poz1=dane.indexOf(';');
      int poz2=dane.indexOf(';', poz1+1);

      pm25=dane.substring(0, poz1);
      pm10=dane.substring(poz1+1, poz2);
      jakosc=dane.substring(poz2+1);

      czasostatni=teraz;
      Serial.println("Dane powietrza OK");
    }
  }



  //manipulacja ekranem
  ekran.clearDisplay();
  ekran.drawLine(0, 42, 127, 42, SH110X_WHITE);
  ekran.drawLine(64, 0, 64, 42, SH110X_WHITE);

  //wypisanie warunkow w domu
  ekran.setCursor(0, 0);
  ekran.printf("DOM");
  ekran.setCursor(0, 9);
  ekran.printf("%.1lf C", temp);
  ekran.setCursor(0, 18);
  ekran.printf("%.1lf %%", hum);
  ekran.setCursor(0, 27);
  ekran.printf("%.1lf hPa", cis);

  //wypisanie warunkow na zewnatrz
  ekran.setCursor(66, 0);
  ekran.printf("DWOR");
  ekran.setCursor(66, 9);
  ekran.printf("%.1lf C", daneBME280.temperatura_out);
  ekran.setCursor(66, 18);
  ekran.printf("%.1lf %%", daneBME280.wilgotnosc_out);
  ekran.setCursor(66, 27);
  ekran.printf("%.1lf hPa", daneBME280.cisnienie_out);

  //wypisywanie jakosci powietrza
  ekran.setCursor(0, 44);
  ekran.print("PM2.5: ");
  ekran.print(pm25);
  ekran.print("   PM10: ");
  ekran.println(pm10);
  ekran.print("Jakosc: ");
  ekran.print(jakosc);

  ekran.display();


  delay(5000);
}

#include <WiFi.h>
#include <HTTPClient.h>

// --- DANE DO KONFIGURACJI ---
const char* ssid = "FunBox2-33BF";
const char* password = "Falafelwpowietrzu";
const char* discord_url = "https://discord.com/api/webhooks/1481352509392945233/W6FFZ42COL14CrWsFM5sIO5ZfmKaDS1oQH8RXgjz98ZZjN0IE61rRzJyz3wS7iyBUm3f";

const int pompa=4, zasilanie=2, odczyt=A0; //piny
const int czas_pompy=3 /*w sekundach*/, czas_snu=/*2*60*60*/30*60 /*w godzinach*/, wilgotnosc_0=2600, wilgotnosc_100=1100; /*wartosc z konsoli*/  //zmienne

#define uS_TO_S_FACTOR 1000000ULL

void setup() {
  //setup
  pinMode(pompa, OUTPUT);
  pinMode(zasilanie, OUTPUT);
  pinMode(odczyt, INPUT);
  Serial.begin(9600);

  // Odczyt z czujnika
  digitalWrite(zasilanie, HIGH); //wlaczenie zasilania dla czujnika wilgotnosci
  delay(500);
  
  // Seria 10 pomiarów do średniej
  int suma_odczytow = 0;
  for(int i = 0; i < 10; i++) {
    suma_odczytow += analogRead(odczyt);
    delay(50);
  }
  int wartosc_czujnika = suma_odczytow / 10; // Obliczenie średniej
  
  Serial.println(wartosc_czujnika);
  digitalWrite(zasilanie, LOW);

  String status_podlewania="Nie";

  // Wyznaczanie procentu wilgotnosci
  int odczytana_wilgotnosc = map(wartosc_czujnika, wilgotnosc_0, wilgotnosc_100, 0, 100);
  odczytana_wilgotnosc = constrain(odczytana_wilgotnosc, 0, 100);

  //Podlewanie
  if(odczytana_wilgotnosc<45)
  {
    digitalWrite(pompa, HIGH);
    delay(czas_pompy*1000);
    digitalWrite(pompa, LOW);
    status_podlewania="Tak";
  }

  //WIFI
  WiFi.begin(ssid, password);
  unsigned long startAttemptTime = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 10000) {
    delay(500);
    Serial.print(".");
  }

  //DISCORD
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(discord_url);
    http.addHeader("Content-Type", "application/json");

    String msg = "{\"content\": \"Wilgotnosc: " + String(odczytana_wilgotnosc) + "%. Podlewanie: " + status_podlewania + "\"}";
    http.POST(msg);
    http.end();
  }

  //USPIENIE
  Serial.flush();
  esp_sleep_enable_timer_wakeup(uS_TO_S_FACTOR*czas_snu);
  esp_deep_sleep_start();
}

void loop() {
  
}

#include <WiFi.h>
#include <HTTPClient.h>

// --- DANE DO KONFIGURACJI ---
const char* ssid = "FunBox2-33BF";
const char* password = "Falafelwpowietrzu";
const char* discord_url = "https://discord.com/api/webhooks/1481352509392945233/W6FFZ42COL14CrWsFM5sIO5ZfmKaDS1oQH8RXgjz98ZZjN0IE61rRzJyz3wS7iyBUm3f";


const int pompa=4, zasilanie=2, odczyt=A0; //piny
const int czas_pompy=3 /*w sekundach*/, czas_snu=1*60*60 /*w godzinach*/, wartosc_graniczna_czujnika=2000; /*wartosc z konsoli*/  //zmienne

#define uS_TO_S_FACTOR 1000000ULL

void setup() {
  //setup
  pinMode(pompa, OUTPUT);
  pinMode(zasilanie, OUTPUT);
  pinMode(odczyt, INPUT);
  Serial.begin(9600);

  //POŁĄCZENIE Z WIFI
  WiFi.begin(ssid, password);
  unsigned long startAttemptTime = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 10000) {
    delay(500);
    Serial.print(".");
  }


  digitalWrite(zasilanie, HIGH); //wlaczenie zasilania dla czujnika wilgotnosci
  delay(500);
  int wartosc_czujnika=analogRead(odczyt);
  Serial.println(wartosc_czujnika);
  digitalWrite(zasilanie, LOW);

  String status_podlewania="Nie";

  if(wartosc_czujnika>wartosc_graniczna_czujnika)
  {
    digitalWrite(pompa, HIGH);
    delay(czas_pompy*1000);
    digitalWrite(pompa, LOW);
    status_podlewania="Tak";
  }

  //Wysylanie danych na discord
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(discord_url);
    http.addHeader("Content-Type", "application/json");

    String msg = "{\"content\": \"Wilgotnosc: " + String(wartosc_czujnika) + ". Podlewanie: " + status_podlewania + "\"}";
    http.POST(msg);
    http.end();
  }


  //usypianie
  Serial.flush();
  esp_sleep_enable_timer_wakeup(uS_TO_S_FACTOR*10);
  esp_deep_sleep_start();

  
}

void loop() {
  
}

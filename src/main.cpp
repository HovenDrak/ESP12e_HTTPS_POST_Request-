#include <Arduino.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

const char *ssid = "Nome da rede WIFI";
const char *password = "Senha da rede WIFI";


String host = "Host name";
String path = "path";
String token = "";
boolean option = true; //Variavel que determina http ou https, true = https e false = http.
#define sensor 16

int contagem = 0;

WiFiClient client;

void setup(){
  
  Serial.begin(115200);

  pinMode(sensor, INPUT);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED){

    delay(1000);
    Serial.println("Conectando no WiFi...");
  }
  Serial.println("Conectado no Wifi");
  Serial.println();
}

void loop(){
  if (digitalRead(sensor) == HIGH){

    if (WiFi.status() == WL_CONNECTED){

      HTTPClient http;

      http.begin(client, host, option);
      http.addHeader("Authorization", token);

      int httpCode = http.POST(path);
      String payload = http.getString();

      Serial.print("Código de resposta da REQUEST >> ");
      Serial.println(httpCode);
      Serial.println(payload);

      http.end();
    }else{

      Serial.println("Wifi não conectado...");
    }
  }
  delay(3000);
}
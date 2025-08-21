#include <WiFi.h>
#include <ThingSpeak.h>
#include "DHT.h"

// Definições do DHT22
#define DHTPIN 4     // Pin onde o sensor DHT22 está conectado
#define DHTTYPE DHT22 // Tipo de sensor DHT

DHT dht(DHTPIN, DHTTYPE);

// Credenciais WiFi
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// ThingSpeak API Key e Channel ID
unsigned long myChannelNumber = 3026174;
const char * myWriteAPIKey = "ZAXERPZF2EX6YBO7";

// Variável para armazenar o cliente WiFi
WiFiClient client;

void setup() {
  Serial.begin(115200);
  
  // Inicialização do sensor DHT
  dht.begin();

  // Conexão WiFi
  WiFi.begin(ssid, password, 6);
  Serial.println("Connecting to WiFi");
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi connected");

  // Inicialização do ThingSpeak
  ThingSpeak.begin(client);
}

void loop() {
  // Leitura de temperatura e umidade
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  

  // Definir campos do ThingSpeak
  ThingSpeak.setField(1, t);
  ThingSpeak.setField(2, h);

  // Enviar dados ao ThingSpeak
  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  Serial.print("Temperatura = ");
  Serial.println(t);
  Serial.print("Umidade = ");
  Serial.println(h);
  // Esperar 5 segundos antes da próxima leitura
  delay(10000);
}
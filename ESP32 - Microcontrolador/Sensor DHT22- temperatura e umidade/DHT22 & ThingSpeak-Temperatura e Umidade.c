#include <WiFi.h>
#include <ThingSpeak.h>
#include "DHT.h"

// Definições do DHT22
#define DHTPIN 4     // Pin onde o sensor DHT22 está conectado: 4
#define DHTTYPE DHT22 // Tipo de sensor DHT

DHT dht(DHTPIN, DHTTYPE);

// Credenciais WiFi
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// ThingSpeak API Key e Channel ID
unsigned long myChannelNumber = XXXXXXX; //digite o número de canal criado no ThingSpeak
const char * myWriteAPIKey = "XXXXX";  // digite uma senha visível na aba API Keys no canal

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
  ThingSpeak.setField(1, t);  // campo/Field 1 no TS receberá as leituras de temperatura 
  ThingSpeak.setField(2, h);  // campo/Field 2 no TS receberá as leituras de umidade 

  // Enviar dados ao ThingSpeak
  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  Serial.print("Temperatura = ");
  Serial.println(t);
  Serial.print("Umidade = ");
  Serial.println(h);
  // Esperar 5 segundos antes da próxima leitura
  delay(10000);
}
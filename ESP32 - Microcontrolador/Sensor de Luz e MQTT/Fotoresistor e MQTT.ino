#include <LiquidCrystal_I2C.h>
#include <WiFi.h>
#include <PubSubClient.h>

#define LDR_PIN 34
#define LED_PIN 2  // LED que acende no estado "Dark"

// —————— Características do LDR ——————
const float GAMMA = 0.7;
const float RL10  = 50;

// —————— Wi-Fi ——————
const char* ssid       = "Wokwi-GUEST";
const char* password   = "";

// —————— MQTT ——————
const char* mqtt_server   = "broker.hivemq.com";
const int   mqtt_port     = 1883;
const char* topic_lux     = "esp32/ldr/lux";
const char* topic_estado  = "esp32/ldr/estado";
const char* topic_led     = "esp32/ldr/led";     // NOVO: status do LED

WiFiClient espClient;
PubSubClient client(espClient);
LiquidCrystal_I2C lcd(0x27, 20, 4);

void setup_wifi() {
  Serial.print("Conectando ao Wi-Fi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWi-Fi conectado. IP: " + WiFi.localIP().toString());
}

void reconnect_mqtt() {
  while (!client.connected()) {
    Serial.print("Conectando ao broker MQTT...");
    if (client.connect("asdfg5h6jklç")) {
      Serial.println(" conectado.");
    } else {
      Serial.print(" falhou (rc=");
      Serial.print(client.state());
      Serial.println("). Tentando novamente em 5 s.");
      delay(5000);
    }
  }
}

void setup() {
  pinMode(LDR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW); // LED inicia desligado

  Serial.begin(115200);
  Wire.begin(21, 22); // SDA 21, SCL 22
  lcd.init();
  lcd.backlight();

  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
}

void loop() {
  if (!client.connected()) reconnect_mqtt();
  client.loop();

  // ——— Leitura do LDR ———
  int analogValue = analogRead(LDR_PIN);
  int valorMap = map(analogValue, 1, 4095, 1, 1024);
  float voltage = valorMap / 1024.0 * 5.0;
  float resistance = 2000 * voltage / (1.0 - voltage / 5.0);
  float lux = pow(RL10 * 1e3 * pow(10, GAMMA) / resistance, 1.0 / GAMMA);

  // ——— Determina estado de luz ———
  const char* estado = (lux > 50) ? "Light" : "Dark";
  bool ledLigado = false;
  const char* LED;


  if (strcmp(estado, "Dark") == 0) {
    digitalWrite(LED_PIN, HIGH);
    ledLigado = true;
  } else {
    digitalWrite(LED_PIN, LOW);
    ledLigado = false;
 
  }

  // ——— LCD ———
  lcd.setCursor(0, 0);
  lcd.print("Room: ");
  lcd.print(estado);
 

  lcd.setCursor(0, 1);
  lcd.print("Lux: ");
  lcd.print(lux);
  lcd.print("     ");

  // ——— MQTT ———
  char msgLux[16];
  dtostrf(lux, 1, 2, msgLux);
  client.publish(topic_lux, msgLux);
  client.publish(topic_estado, estado);
  client.publish(topic_led, ledLigado ? "ON" : "OFF");

  delay(1000);
}

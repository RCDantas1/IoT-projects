#include <LiquidCrystal_I2C.h> 

LiquidCrystal_I2C lcd(0x27, 20, 4); 

const float BETA = 3950;    // Coeficiente Beta do NTC 
int led = 26;              // Define o LED no pino 26

void setup() { 
  Serial.begin(115200); 
  pinMode(led, OUTPUT);
  lcd.init(); 
  lcd.backlight(); 
} 

void loop() { 
  int analogValue = analogRead(35);    // Lê o sensor no pino 35.

  float celsius = 1 / (log(1 / (4095. / analogValue - 1)) / BETA + 1.0 / 298.15) - 273.15; 

  char valor[10];   // mantém o valor em 2 casas decimais após o ponto.
  sprintf(valor, "%.2f", celsius); 

  String temp = ("Temperatura: " + String(valor) + (char)223 + "C "); 

  Serial.println(celsius); 
  lcd.setCursor(3, 0); 
  lcd.print("Monitorando..."); 
  lcd.setCursor(0, 1);  
  lcd.print(temp); 

  if(celsius >= 50){         // Temperatura >= a 50°C = acende o LED.
    digitalWrite(led, HIGH);
  }
  else{
    digitalWrite(led, LOW);
  }

  delay(1000); 
}

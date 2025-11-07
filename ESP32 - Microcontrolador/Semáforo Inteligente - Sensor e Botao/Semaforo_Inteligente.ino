//AUTOR: RAFAEL DANTAS
// PROJETO: SEMÁFORO COM ACIONAMENTO PARA PEDESTRES


#include<LiquidCrystal_I2C.h>
#include<Wire.h>

  short int vermelho = 17, amarelo = 16, verde = 4;
  short int pedestre_verde = 33, pedestre_vermelho = 32;
  short int botao = 14, sensor = 34;
 short int flag = 0;
  short int estadoBotao = 0, estadoSensor = 0;

LiquidCrystal_I2C lcd(0x27, 16, 2); 

void setup() {
  Serial.begin(115200);
  pinMode(vermelho, OUTPUT);
  pinMode(amarelo, OUTPUT);
  pinMode(verde, OUTPUT);
  pinMode(pedestre_verde, OUTPUT);
  pinMode(pedestre_vermelho, OUTPUT);
  pinMode(botao, INPUT);
  pinMode(sensor, INPUT);

  lcd.init();       // inicia o LCD
  lcd.backlight();  // Liga a luz de fundo
}

void loop() {

  estadoBotao = digitalRead(botao);  // lê o botão
  estadoSensor = digitalRead(sensor); //lê o sensor de movimento

  if(flag == 0){

      // acende o vermelho para pedestres
    digitalWrite(pedestre_vermelho, HIGH);
    digitalWrite(pedestre_verde, LOW);
      lcd.clear(); 
      lcd.setCursor(5, 0);  // Coluna 0, linha 0
      lcd.print("STOP");
    delay(2000);

      // acende o verde para carros
    digitalWrite(vermelho, LOW);
    digitalWrite(verde, HIGH);
      flag = 1;
  }
   
  if(((estadoBotao == HIGH) || (estadoSensor == HIGH)) && (flag = 1)) {
      //Botão acionado    OU   Detecção de movimento no sensor

      // acende o amarelo para carros
    digitalWrite(verde, LOW);
    digitalWrite(amarelo, HIGH);
      delay(2000);
  
      // acende o vermelho para carros
    digitalWrite(amarelo, LOW);
    digitalWrite(verde, LOW);
    digitalWrite(vermelho, HIGH);
      delay(1000);

      // acende o verde para pedestres
    digitalWrite(pedestre_vermelho, LOW);
    digitalWrite(pedestre_verde, HIGH);
      lcd.clear(); 
      lcd.setCursor(5, 0);  
      lcd.print("GO");
      delay(5000);

      flag = 0;
    }
  
}

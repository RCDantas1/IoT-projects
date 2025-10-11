//Circuito de irrigação automático para microcontrolador
 
int umidade = A1; 
int motor = 12;

void setup() {
pinMode(umidade, INPUT); // Declara o pino A1 como Entrada do sinal analógico
pinMode(motor, OUTPUT); // Declara o pino 12 como Saída do sinal digital
Serial.begin(9600);
}
 
void loop() {
umidade = analogRead(A1);  
 		
  //Se a umidade estiver abaixo de 200 -> liga o motor e LED.
if (umidade < 200) {    
  digitalWrite(motor, HIGH);
}
 
else { 
 digitalWrite(motor, LOW);
}
  delay(100);
}

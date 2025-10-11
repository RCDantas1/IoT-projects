// Acendimento de lâmpada a partir de sinal digital do microcontrolador.
// Alteração no código permite adicionar comando a partir de comunicação sem fio, como protocolo MQTT.
//A corrente emitida pela placa (insuficiente para o relé) ativa o transistor.
//Uma fonte menor (5v) alimenta o relé quando o transistor é ativado. O relé libera caminho para corrente que parte da fonte ac 10v alimente a lâmpada.

const byte lampada =13;  //define a porta digital 13 como GPIO emissora do sinal.

void setup()
{
  pinMode(lampada, OUTPUT);  //define como saída de sinal.
}

void loop()
{
    //exemplo simples: lâmpada pisca a cada 2 segundos
  digitalWrite(lampada, HIGH);
  delay(2000); // Wait for 2000 millisecond(s)
  digitalWrite(lampada, LOW);
  delay(2000); // Wait for 2000 millisecond(s)
}

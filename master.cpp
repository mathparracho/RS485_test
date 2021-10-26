#include <SoftwareSerial.h>
//Pinos de comunicacao serial do modulo RS485
#define Pino_RS485_RX    10
#define Pino_RS485_TX    11
//Pino de controle transmissao/recepcao
#define SSerialTxControl 3
#define RS485Transmit    HIGH
#define RS485Receive     LOW
//Define led 13 para mostrar atividade na comunicacao
#define Pin13LED         13
//Cria a serial por sofware para conexao com modulo RS485
SoftwareSerial RS485Serial(Pino_RS485_RX, Pino_RS485_TX);
void setup()
{
  //Inicializa a serial do Arduino
  Serial.begin(9600);
  Serial.println("Modulo Transmissor");
  Serial.println("Pressione o botao para enviar os dados...");
  pinMode(Pin13LED, OUTPUT);
  pinMode(SSerialTxControl, OUTPUT);
  //Inicializa a serial do modulo RS485
  RS485Serial.begin(4800);
  //Seta o pino A0 como entrada e habilita o pull up
  pinMode(A0, INPUT_PULLUP);
}
void loop()
{
  //Verifica se o botao foi pressionado
  int  valor = digitalRead(A0);
  if (valor == 0)
  {
    Serial.println("Botao pressionado. Enviando dados!");
    
    //Habilita o modulo para transmissao
    digitalWrite(SSerialTxControl, RS485Transmit);
    //Envia a string
    RS485Serial.println("Botao acionado");
    //Liga o led 13 para mostrar que ha conexao
    digitalWrite(Pin13LED, HIGH);
    delay(10);
    digitalWrite(Pin13LED, LOW);
    //Desabilita o modulo para transmissao
    digitalWrite(SSerialTxControl, RS485Receive);
    while (digitalRead(A0) == 0)
    {
      delay(50);
    }
  }
}
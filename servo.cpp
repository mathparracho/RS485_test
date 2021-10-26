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
//Armazena os dados que chegam pela serial
String inputString = "";
//Variavel de string completa
boolean stringComplete = false;
void setup()
{
  //Inicializa a serial do Arduino
  Serial.begin(9600);
  Serial.println("Modulo Receptor");
  Serial.println("Aguardando dados...");
  pinMode(Pin13LED, OUTPUT);
  pinMode(SSerialTxControl, OUTPUT);
  //Coloca o modulo RS485 em modo de recepcao
  digitalWrite(SSerialTxControl, RS485Receive);
  //Inicializa a serial do modulo RS485
  RS485Serial.begin(4800);
}
void loop()
{
  //Recebe os dados do RS485 via porta serial
  if (RS485Serial.available())
  {
    while (RS485Serial.available())
    {
      //Recebe os dados e monta a string
      char inChar = (char)RS485Serial.read();
      inputString += inChar;
      
      if (inChar == 'n')
      {
        //Mostra no Serial Monitor a string recebida
        Serial.print(inputString);
        stringComplete = true;
        inputString = "";
      }
    }
  }
}
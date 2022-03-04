#include <SPI.h>
const int slaveSelect=10;
const int decodeMode=9;
const int intensity=10;
const int scanLimit=11;
const int shutDown=12;
const int dispTest=15;
int ch;
byte i;
const byte character[10][8]=  //PABCDEFG		
  { {0x00,0x00,0x7f,0x41,0x41,0x7f,0x00,0x00},    //0
    {0x00,0x00,0x00,0x00,0x00,0x7f,0x00,0x00},    //1
    {0x00,0x00,0x79,0x49,0x49,0x4f,0x00,0x00},    //2
    {0x00,0x00,0x49,0x49,0x49,0x7f,0x00,0x00},    //3
    {0x00,0x00,0x0f,0x08,0x08,0x7f,0x00,0x00},    //4
    {0x00,0x00,0x4f,0x49,0x49,0x79,0x00,0x00},    //5
    {0x00,0x00,0x7f,0x49,0x49,0x79,0x00,0x00},    //6
    {0x00,0x00,0x01,0x01,0x01,0x7f,0x00,0x00},    //7
    {0x00,0x00,0x7f,0x49,0x49,0x7f,0x00,0x00},    //8
    {0x00,0x00,0x4f,0x49,0x49,0x7f,0x00,0x00} };  //9    	  
void setup() 
{
  Serial.begin(9600);
  SPI.begin();
  pinMode(slaveSelect,OUTPUT);
  digitalWrite(slaveSelect,HIGH);
  sendCommand(shutDown,1);
  sendCommand(dispTest,0);
  sendCommand(intensity,1);
  sendCommand(scanLimit,7);
  sendCommand(decodeMode,0); 
  for(i=0;i<8;i++)
    sendCommand(i+1,character[0][0]); 
}   
void loop() 
{
  if(Serial.available())
  {
    ch=Serial.read();   
  } 
  if(ch>='0' && ch<='9')
  {
    for(i=0;i<8;i++)
      sendCommand(i+1,character[ch-'0'][i]); 
delay(500);
      sendCommand(shutDown,0);
  delay(500);  
    sendCommand(shutDown,1);
    delay(500); 
      }   
}
void sendCommand(byte command,byte value)
{
  digitalWrite(slaveSelect,LOW);
  SPI.transfer(command);
  SPI.transfer(value);
  digitalWrite(slaveSelect,HIGH);
}    

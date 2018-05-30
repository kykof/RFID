#include <SPI.h>  
#include <MFRC522.h>
#include "BluetoothSerial.h"

const int RST_PIN = 22;
const int SDA_PIN = 21; 

BluetoothSerial SerialBT;
 
MFRC522 rfid(SDA_PIN, RST_PIN); 
 
void setup() { 
SerialBT.begin("ESP32");
SPI.begin();
rfid.PCD_Init(); 

}
 
void loop() {

if ( ! rfid.PICC_IsNewCardPresent()) {
return;
}
 
if ( ! rfid.PICC_ReadCardSerial()) { 
return;
}

MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);

vypisHex(rfid.uid.uidByte, rfid.uid.size);
SerialBT.println();

delay(1500);  
}   

void vypisHex(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    SerialBT.print(buffer[i] < 0x10 ? " 0" : " ");
    delay(250);                                                   //max 250
    SerialBT.print(buffer[i],HEX);
  }
}



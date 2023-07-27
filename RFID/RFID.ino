#include <SPI.h>
#include <MFRC522.h>
 
#define SS_PIN 5
#define RST_PIN 22
#define BUZZER 13 //buzzer pin
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

 
void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  pinMode(BUZZER, OUTPUT);
  Serial.println("Put your card to the reader...");
  Serial.println();

}
void loop() 
{
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
  //Show UID on serial monitor
  Serial.print(" ");
  Serial.print("UID tag :");
  byte letter;
  String content= "";
  for (byte i = 0; i < 10; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " " : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " " : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(0) == "45 43 4F 50") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access");
    digitalWrite(BUZZER, HIGH);
    delay(1000);
    digitalWrite(BUZZER, LOW);
  }
 
 else   {
    Serial.println(" Access denied");
    digitalWrite(BUZZER, HIGH);
    delay(100);
    digitalWrite(BUZZER, LOW);
    delay(100);
    digitalWrite(BUZZER, HIGH);
    delay(100);
    digitalWrite(BUZZER, LOW);
  }
} 
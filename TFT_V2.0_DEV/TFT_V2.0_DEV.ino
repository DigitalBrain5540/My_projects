#include <SPI.h>
#include <TFT_eSPI.h>
#include <Free_Fonts.h>
#include <Wire.h>
#include <PN532_I2C.h>
#include <PN532.h>
#include <NfcAdapter.h>
PN532_I2C pn532_i2c(Wire);
NfcAdapter nfc = NfcAdapter(pn532_i2c);
String tagId;
byte nuidPICC[4];

const byte data = 8;
const int numbyte = 8;

TFT_eSPI tft = TFT_eSPI();
String sat *ndefMessage;
void setup(void) {
  
 Serial.begin(9600);
 nfc.begin();
 tft.begin();
 tft.init();
 tft.setRotation(1);
  
 tft.fillScreen(TFT_SKYBLUE);
 tft.setTextColor(TFT_WHITE, TFT_SKYBLUE);
 tft.fillRect(130, 120, 60, 100, TFT_ORANGE);
 tft.fillRect(135, 100, 50, 20, TFT_ORANGE);
 tft.fillRect(140, 110, 40, 5, TFT_BLACK);
 tft.fillRect(260, 120, 60, 100, TFT_GREEN);
 tft.fillRect(265, 100, 50, 20, TFT_GREEN);
 tft.fillRect(270, 110, 40, 5, TFT_BLACK);
 tft.setCursor(87, 180);
 tft.setFreeFont(FSS24);
 tft.print("s   e   w   a   c");
 delay(2000);
 tft.fillScreen(TFT_SKYBLUE);
 tft.setTextColor(TFT_BLACK, TFT_BLUE);
 tft.fillRect(140, 110, 70, 100, TFT_WHITE);
 tft.fillRect(90, 120, 70, 100, TFT_RED);
 tft.fillRect(115, 165, 45, 30, TFT_SKYBLUE);
 tft.fillRect(160, 125, 30, 55, TFT_SKYBLUE);
 tft.setCursor(230, 150);
 tft.setFreeFont(FSS24);
 tft.print("eco");
 tft.setCursor(230, 200);
 tft.setFreeFont(FSS24);
 tft.print("paradigm");
 delay(2000);
 
 tft.fillScreen(TFT_SKYBLUE);
 tft.setTextColor(TFT_WHITE, TFT_BLUE);
 tft.setCursor(100, 160);
 tft.setFreeFont(FSS24);
 tft.print("Loading");
 
  for(int i=160; i<400; i++){
   Serial.println(i);
   tft.setTextColor(TFT_GREEN, TFT_BLUE);
   tft.setFreeFont(FSS12);
   tft.drawRect(164, 175, 237, 19, TFT_RED);
   tft.setCursor(i, 190);
   tft.print("|");
   delay(50);
  }
 
 tft.fillScreen(TFT_SKYBLUE);
 tft.setTextColor(TFT_WHITE);
 tft.setFreeFont(FSS18);
 tft.setCursor(40, 40);
 tft.print("COLLECTION DETAILS");

 tft.setFreeFont(FSS12);
 tft.setCursor(10, 100);
 tft.print("CARD HOLDER NAME :");

 tft.setCursor(100, 140);
 tft.setTextColor(TFT_GREEN);
 tft.print("PRAVINJITH K P");

 tft.setTextColor(TFT_WHITE);
 tft.setCursor(10, 180);
 tft.print("HOUSE      NO. :");
 tft.setCursor(200, 180);
 tft.setTextColor(TFT_GREEN);
 tft.print("150");

 tft.setTextColor(TFT_WHITE);
 tft.setCursor(10, 220);
 tft.print("DRY     WASTE :");
 tft.setCursor(300, 220);
 tft.print("KG");

 tft.setTextColor(TFT_WHITE);
 tft.setCursor(10, 260);
 tft.print("WET     WASTE :");
 tft.setCursor(300, 260);
 tft.print("KG");

 tft.setTextColor(TFT_WHITE);
 tft.setCursor(10, 300);
 tft.print("MIXED WASTE :");
 tft.setCursor(300, 300);
 tft.print("KG");

}

void loop() {
 readNFC();
 tft.print(tagId);
 //NdefMessage(data, numbyte);
 //nfc.write(bool==1);
 //NfcAdapter.write();
 //NfcAdapter::write(NdefMessage);
 //NfcTag::getNdefMessage();
 Serial.print(sat);
}

void readNFC()
{
  if (nfc.tagPresent())
  {
    NfcTag tag = nfc.read();
    tagId = tag.getUidString();
    Serial.println("Tag id");
    Serial.println(tagId);
  }
  delay(1000);
}

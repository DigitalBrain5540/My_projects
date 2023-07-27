#include "BluetoothSerial.h"

BluetoothSerial ESP_BT;

void setup() {
  Serial.begin(9600);
  ESP_BT.begin("ESP32");

  pinMode(12, INPUT);
  pinMode(15, INPUT);
  pinMode(32, INPUT);

}

void loop() {
  ESP_BT.print('E');
  ESP_BT.print(touchRead(12));
  ESP_BT.print('E');
  ESP_BT.print(touchRead(15));
  ESP_BT.print('E');
  ESP_BT.println(touchRead(32));

  Serial.print(touchRead(12));
  Serial.print(" ");
  Serial.print(touchRead(15));
  Serial.print(" ");
  Serial.println(touchRead(32));
  delay(100);
}

#include<Arduino.h>
#define a touchRead(T3)

void callback(){
}
void setup(){
Serial.begin(9600);
delay(1000);
pinMode(2, OUTPUT);
touchAttachInterrupt(T3, callback, 40);
}

void loop(){
Serial.println(a);

esp_sleep_enable_touchpad_wakeup();
if(a < 30){
 digitalWrite(2, HIGH);
 Serial.println("on");
}

else{
 delay(1000);
 digitalWrite(2, LOW);
 Serial.println("i'm going to sleep");
 esp_deep_sleep_start();
}
}
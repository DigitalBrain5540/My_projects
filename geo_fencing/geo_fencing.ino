#include <SoftwareSerial.h>
#include <TinyGPSPlus.h>
#include "BluetoothSerial.h"

BluetoothSerial ESP_BT;
#define rxPin 16
#define txPin 17
SoftwareSerial ss(rxPin,txPin);
TinyGPSPlus gps;
//--------------------------------------------------------------
#define BUZZER 2
 
// Alarm
int buzzer_timer = 0;
//bool alarm = 0;
boolean send_alert_once = true;

unsigned long previousMillis=0;
unsigned long int previoussecs = 0; 
unsigned long int currentsecs = 0; 
unsigned long currentMillis = 0; 
int secs = 0; 
int pmints = 0; 
int mints = 0; // current mints
int interval= 1 ; // updated every 1 second
 
 
//--------------------------------------------------------------
// Size of the geo fence (in meters)
const float maxDistance = 20;
 
//--------------------------------------------------------------
float initialLatitude = 12.932878;
float initialLongitude = 77.632776;



 
//float latitude, longitude;
 
//--------------------------------------------------------------
 
 
 //void getGps(float& latitude, float& longitude);
 
 
/*****************************************************************************************
 * setup() function
 *****************************************************************************************/
void setup(){
  //--------------------------------------------------------------
  //Serial.println("Arduino serial initialize");
  Serial.begin(9600);
  //--------------------------------------------------------------
  //Serial.println("SIM800L serial initialize");
  ss.begin(9600);
  ESP_BT.begin("ESP32");
  //--------------------------------------------------------------
  //Serial.println("NEO6M serial initialize");

  //--------------------------------------------------------------
  pinMode(BUZZER, OUTPUT);
  //--------------------------------------------------------------
  
  //AT +CNMI = 2,1,0,0,0 - AT +CNMI = 2,2,0,0,0 (both are same)
  //--------------------------------------------------------------
  delay(20000);
  buzzer_timer = millis();
}
 
 
 
 
 
/*****************************************************************************************
 * loop() function
 *****************************************************************************************/
void loop(){
float latitude1 = gps.location.lat();
float longitude1 = gps.location.lng();
while (ss.available() > 0){
 if (gps.encode(ss.read())){
   Serial.print(F("Location: ")); 
   if (gps.location.isValid()){
     Serial.print(gps.location.lat(), 7);
     ESP_BT.print(gps.location.lat(), 7);
     Serial.print(F(", "));
     Serial.println(gps.location.lng(), 7);
     ESP_BT.println(gps.location.lng(), 7);
     digitalWrite(2, HIGH);
     float distance = getDistance(latitude1, longitude1, initialLatitude, initialLongitude);
     Serial.print("Latitude= "); Serial.println(latitude1, 6);
     Serial.print("Lngitude= "); Serial.println(longitude1, 6);
     Serial.print("initialLatitude= "); Serial.println(initialLatitude, 6);
     Serial.print("initialLngitude= "); Serial.println(initialLongitude, 6);
     Serial.print("current Distance= "); Serial.println(distance);
  
     ESP_BT.print("Latitude= "); ESP_BT.println(latitude1, 6);
     ESP_BT.print("Lngitude= "); ESP_BT.println(longitude1, 6);
     ESP_BT.print("initialLatitude= "); ESP_BT.println(initialLatitude, 6);
     ESP_BT.print("initialLngitude= "); ESP_BT.println(initialLongitude, 6);
     ESP_BT.print("current Distance= "); ESP_BT.println(distance);

     delay(2000);
  }
    else{
     digitalWrite(2, HIGH);
     delay(500);
     digitalWrite(2, LOW);
     delay(500);
     Serial.println(F("INVALID"));
     }
  }
 }

  

  //--------------------------------------------------------------
  //getGps(latitude, longitude);
  //--------------------------------------------------------------
   
  //--------------------------------------------------------------
  // Set alarm on?
  /*if(distance > maxDistance) {
    
    //------------------------------------------
    if(send_alert_once == true){
      digitalWrite(BUZZER, HIGH);
      
      //alarm = 1;
      send_alert_once = false;
      buzzer_timer = millis();
      
    }
    //------------------------------------------
  }
  else{
    send_alert_once = true;
    
  }
  //--------------------------------------------------------------
 
  // Handle alarm
  if (alarm == 1) {
    if (millis() - buzzer_timer > 5000) {
      digitalWrite(BUZZER, LOW);
      alarm = 1;
      buzzer_timer = 0;
      
    }
  }*/
 

 /* //--------------------------------------------------------------  
  while(ss.available()){
    Serial.println(ss.readString());
    

  }
  //--------------------------------------------------------------
  while(Serial.available())  {
    ss.println(Serial.readString());

  }
  //--------------------------------------------------------------
 */
 
}
 
 
 
/*****************************************************************************************
* getDistance() function
*****************************************************************************************/
 
// Calculate distance between two points
float getDistance(float flat1, float flon1, float flat2, float flon2) {
 
  // Variables
  float dist_calc=0;
  float dist_calc2=0;
  float diflat=0;
  float diflon=0;
 
  // Calculations
  diflat  = radians(flat2-flat1);
  flat1 = radians(flat1);
  flat2 = radians(flat2);
  diflon = radians((flon2)-(flon1));
 
  dist_calc = (sin(diflat/2.0)*sin(diflat/2.0));
  dist_calc2 = cos(flat1);
  dist_calc2*=cos(flat2);
  dist_calc2*=sin(diflon/2.0);
  dist_calc2*=sin(diflon/2.0);
  dist_calc +=dist_calc2;
 
  dist_calc=(2*atan2(sqrt(dist_calc),sqrt(1.0-dist_calc)));
  
  dist_calc*=6371000.0; //Converting to meters
 
  return dist_calc;
}
 
 
/*****************************************************************************************
 * getGps() Function
*****************************************************************************************/
/*
void getGps(float& latitude, float& longitude)
{
  // Can take up to 60 seconds
  boolean newData = false;
  for (unsigned long start = millis(); millis() - start < 2000;){
    while (ss.available()){
      if (gps.encode(ss.read())){
        newData = true;
        break;
      }
    }
  }
  
  if (newData) //If newData is true
  {
    latitude = gps.location.lat();
    longitude = gps.location.lng();
    newData = false;
  }
  else {
    Serial.println("No GPS data is available");
    latitude = 0;
    longitude = 0;
  }
}
 */
 
 
 
/*****************************************************************************************
* sendAlert() function
*****************************************************************************************/

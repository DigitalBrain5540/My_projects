#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

#define WIFI_SSID "SEWAC"
#define WIFI_PASSWORD "EcoparadigM"
#define API_KEY "AIzaSyD5xAF322fOaupEmXAPbKN-5z-2Tw452j4"
#define DATABASE_URL "https://test-4a12b-default-rtdb.firebaseio.com/" 

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
const long sendDataIntervalMillis = 5000;
bool signupOK = false;
float store_random_Float_Val;
int store_random_Int_Val;

void setup() {
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  pinMode(13, OUTPUT);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    digitalWrite(2, LOW);
  }
  digitalWrite(2, HIGH);
  Serial.println();
  Serial.print("Connected to WIFI: ");
  Serial.println(WIFI_SSID);
  Serial.print("IP : ");
  Serial.println(WiFi.localIP());
  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;
  Serial.print("Firebase Connection: ");
  if (Firebase.signUp(&config, &auth, "", "")){
    Serial.println("ok");
    signupOK = true;
  }
  else{
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }
  config.token_status_callback = tokenStatusCallback;
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}
void loop() {
  
  if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > sendDataIntervalMillis || sendDataPrevMillis == 0)){
    sendDataPrevMillis = millis();
    int randNumber = random(15, 40);
    float f = (float)randNumber / 1.01;
    int i = (int(f*100));
    store_random_Float_Val = float(i) / 100;
    store_random_Int_Val = random(10, 99);
    Serial.print("Random Float_Val : ");
    Serial.println(store_random_Float_Val);
    Serial.print("Random Int_Val : ");
    Serial.println(store_random_Int_Val);
    if (Firebase.RTDB.setFloat(&fbdo, "Test/random_Float_Val", store_random_Float_Val)) {
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }
    if (Firebase.RTDB.setInt(&fbdo, "Test/my_Int_Val", store_random_Int_Val)){
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }
    digitalWrite(13, HIGH);
    delay(500);
    digitalWrite(13, LOW);
  }
}
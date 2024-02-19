#include <Arduino.h>
#if defined(ESP32)
  #include <WiFi.h>
#elif defined(ESP8266)
  #include <ESP8266WiFi.h>
#endif
#include <Firebase_ESP_Client.h>

#include "addons/TokenHelper.h"
//Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

#define WIFI_SSID "Pixel"
#define WIFI_PASSWORD "Sunil@17"
#define API_KEY "AIzaSyAOImgVooRy3PYPhOxhveIJGEeJu7RSXNw"

#define USER_EMAIL "abcd@gmail.com"
#define USER_PASSWORD "123456"

#define DATABASE_URL "https://smartglow-7b555-default-rtdb.firebaseio.com/"

#define DATABASE_SECRET "Xth9lwdhlbo8W8DN2p8qsDEOOfSUk2y7B2dZzZWk"

FirebaseData fbdo,fbd1,light;
FirebaseAuth auth;
FirebaseConfig config;



const int pir = D6;  //PIR sensor 2 input pin
const int ldr = D0;   // LDR sensor input pin
const int led = D2;
int a_mode;
int m_mode;

void setup() {
 
  pinMode(pir, INPUT);
  pinMode(led, OUTPUT);
  pinMode(ldr, INPUT);
  Serial.begin(115200);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }

  Serial.println("\nConnected with IP: " + WiFi.localIP().toString());

  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;

  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;

  config.token_status_callback = tokenStatusCallback;

  Firebase.begin(&config,&auth);
  Firebase.reconnectWiFi(true);
}

void loop() {
  if (Firebase.ready()) {

    if (Firebase.RTDB.getInt(&fbdo, "/Automatic") && Firebase.RTDB.getInt(&fbd1,"/Manual")) {
      if ((fbdo.dataType() == "int") && (fbd1.dataType()=="int")) {
         a_mode = fbdo.intData();
         m_mode = fbd1.intData();
        
        if (a_mode == 1)
        {
          int ldr_state = digitalRead(ldr);

          if (ldr_state == LOW) // LDR == LOW --> NIGHT
          
          {
              Firebase.RTDB.setInt(&fbdo, "/LDR_Status", 0);
              Serial.println("-------NIGHT--------");

          if (digitalRead(pir) == HIGH) {
      // Motion detected
      //Serial.println("LED2 is on");
          digitalWrite(led, HIGH); // Turn on the LED
         Firebase.RTDB.setInt(&fbdo, "/LED_Status", 1);  // ON
          delay(5000);        
          digitalWrite(led, LOW);  // Turn off the LED
          Firebase.RTDB.setInt(&fbdo, "/LED_Status", 0);
    }

    delay(500);
      } 
      else {
          Serial.println("-------DAY-------");
          Firebase.RTDB.setInt(&fbdo, "/LDR_Status", 1); 
          digitalWrite(led, LOW);
          Firebase.RTDB.setInt(&fbdo, "/LED_Status", 0);
          delay(1000);
  }
      }

      else if(m_mode==1)
      {
          if (Firebase.RTDB.getInt(&light, "/LED")) {
          if (light.dataType() == "int") {
        int b = light.intData();
        Serial.println(b);
        if (b == 1){
          digitalWrite(D2,HIGH);
          Firebase.RTDB.setInt(&fbd1, "/LED_Status", 1);
        }else{
          digitalWrite(D2,LOW);
          Firebase.RTDB.setInt(&fbd1, "/LED_Status", 0);
        }
      }
    }
      }


    }

}
Serial.print("Automatic Mode = ");
Serial.println(a_mode);
Serial.print("Manual Mode = ");
Serial.println(m_mode);
  }
}


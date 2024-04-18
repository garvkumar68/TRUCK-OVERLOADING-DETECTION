#include <HX711.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>


#define V1 1   
#define V2 2   
#define DOUT  23    // HX711 DOUT pin
#define CLK   22    // HX711 CLK pin
#define LED_PIN 2   // LED pin
#define BLYNK_TEMPLATE_ID "TMPL3nLQzxg3Y"
#define BLYNK_TEMPLATE_NAME "garv"
char auth[] = "SUg9QukDNsTowuVHpXBWNy6f4reIOwB7";  //Blynk auth token
char ssid[] = "LAPTOP-605PG7DB 2369";   //WiFi SSID
char pass[] = "garv1234";   //WiFi password

HX711 scale;
int switchValue = 0; 

BLYNK_CONNECTED() {
  Blynk.syncVirtual(V2); 
}

BLYNK_WRITE(V2) {
  switchValue = param.asInt();  
}

void setup() {
  Serial.begin(115200);
  Serial.print("ready");
  pinMode(LED_PIN, OUTPUT);

  Blynk.begin(auth, ssid, pass);

  while (!Blynk.connected()) {
    delay(100);
  }

  scale.begin(DOUT, CLK); 
  scale.set_scale(2280.0);  
  scale.tare();             
}

void loop() {
  
  float weight = scale.get_units(10);  
  Serial.println(weight);

  Blynk.virtualWrite(V1, weight);  
  if (weight < 50 || switchValue == HIGH) {  
    digitalWrite(LED_PIN, HIGH);  
  } else {
    digitalWrite(LED_PIN, LOW); 
  }

  delay(1000);  
}


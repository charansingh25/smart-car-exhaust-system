#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Wire.h>
#include "MQ135.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
 
#define SCREEN_WIDTH 128    // OLED display width, in pixels
#define SCREEN_HEIGHT 64    // OLED display height, in pixels
#define OLED_RESET -1       // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


#define BLYNK_TEMPLATE_ID "TMPL3UtUgPoMP";
#define BLYNK_TEMPLATE_NAME "AIR Quality";
#define BLYNK_AUTH_TOKEN "eMB4Du7iNFWk9J15bBesiYDcF7oSWEdp";
char auth[] = "eMB4Du7iNFWk9J15bBesiYDcF7oSWEdp"; // Blynk authentication token
const char *ssid = "pseudo"; // replace with your wifi ssid and wpa2 key
const char *pass = "25082002";

BlynkTimer timer;

void setup() {
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Initialize with the I2C addr 0x3C (128x64)

  // Your existing setup code...
}

void loop() {
  Blynk.run();
  timer.run();
  
  // Your existing loop code...
}

void sendSensorData() {
  MQ135 gasSensor = MQ135(A0);
  float air_quality = gasSensor.getPPM();
  
  Blynk.virtualWrite(V1, air_quality); // Send air quality value to V1 on Blynk app
  
  display.clearDisplay();
  display.setCursor(0,0);  // OLED display
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.println("Air Quality Index");
  
  display.setCursor(0,20);  // OLED display
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.print(air_quality);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.println(" PPM");
  display.display();
}

BLYNK_WRITE(V0) {
  // This function will be called every time the V0 slider on Blynk app changes
  int sliderValue = param.asInt(); // Get the value from the slider
  
  // Use sliderValue for any custom processing if needed
}

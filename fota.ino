// esp32 version 1.0.5
// json 6.9.0
#include <Arduino.h>
#include <WiFi.h>
#include <FS.h>
#include <SPIFFS.h>
#include <esp32fota.h>

#define WIFI_SSID         "5/105_2.4G"
#define WIFI_PASSWORD     "11357902"

esp32FOTA esp32FOTA("esp32-fota-http", "0.0.1", false, true);

void setup() {
  SPIFFS.begin(true);
  esp32FOTA.checkURL = "https://makerzcoding.com/fota/fota.json";
  Serial.begin(115200);
  setup_wifi();
}

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.println("-------------------------------------");
  Serial.println("Running!");
  Serial.println("-------------------------------------");
  // Connect to Wifi.
  Serial.println();
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.printf("WiFi Connecting to %s\n", WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.printf("\nWiFi connected\nIP : ");
  Serial.println(WiFi.localIP());
  Serial.println();
}

void loop() {

  bool updatedNeeded = esp32FOTA.execHTTPcheck();
  if (updatedNeeded) {
    esp32FOTA.execOTA();
  }
  Serial.println("New version 0.0.1");
  delay(2000);
}

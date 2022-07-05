// esp32 version 1.0.5
// json 6.9.0
#include <Arduino.h>
#include <WiFi.h>
#include <FS.h>
#include <SPIFFS.h>
#include <esp32fota.h>

#define WIFI_STA_NAME "TP-Link_C8EA"
#define WIFI_STA_PASS "89663042"

esp32FOTA esp32FOTA("esp32-fota-http", "3.0.3", false, true);

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
  WiFi.begin(WIFI_STA_NAME, WIFI_STA_PASS);
  Serial.printf("WiFi Connecting to %s\n", WIFI_STA_NAME);
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
  Serial.println("New version 3.0.3");
  delay(2000);
}

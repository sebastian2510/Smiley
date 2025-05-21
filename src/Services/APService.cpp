#include <Arduino.h>
#include <WiFi.h>
#include "APService.h"

const char *ssid = "IoT_H3/4";
const char *password = "98806829";

void APService::setup()
{
    Serial.println("Setting up AP...");
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi ..");

    unsigned long startAttemptTime = millis();
    const unsigned long wifiTimeout = 15000; // 15 seconds

    while (WiFi.status() != WL_CONNECTED && (millis() - startAttemptTime) < wifiTimeout) {
        Serial.print('.');
        delay(500);
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.print("\nConnected to WiFi ");
        Serial.println(WiFi.localIP());
    } else {
        Serial.println("WiFi connection failed!");
    }
}

bool APService::isConnected()
{
    return WiFi.status() == WL_CONNECTED;
}

void APService::Disconnect()
{
    WiFi.disconnect();
}
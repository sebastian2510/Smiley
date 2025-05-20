#include <Arduino.h>
#include <WiFiManager.h>
#include "APService.h"

WiFiManager wm;

/**
 * @brief Sets up the Access Point (AP) service for the ESP32.
 * 
 * This function initializes the WiFi in station mode and starts the serial communication at a baud rate of 115200.
 * It attempts to auto-connect to a WiFi network using the WiFiManager library. If the auto-connect fails, it tries to 
 * connect using a specified SSID and password. If the connection still fails, 
 * it resets the WiFi settings and restarts the ESP32. If the connection is successful, it prints a success message 
 * to the serial monitor.
 */
void APService::setup()
{
    WiFi.mode(WIFI_STA);
    
    bool res = wm.autoConnect(); // auto generated AP name from chipid
    if (!res)
    {
        res = wm.autoConnect("Sebastians ESP32", "password"); // password protected ap
    }

    if (!res)
    {
        Serial.println("Failed to connect");
        wm.resetSettings();
        ESP.restart();
    }
    else
    {

        Serial.println("connected...yeey :)");
    }
}

void APService::Disconnect()
{
    WiFi.disconnect();
    wm.resetSettings();
}
// Guest_HX912433
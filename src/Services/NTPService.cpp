#include <Arduino.h>
#include "NTPService.h"
#include <WiFi.h>
#include "time.h"
#include <iostream>
#include "./NTPService.h"
#include "./APService.h"

const char *ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 3600;
const int daylightOffset_sec = 3600;

/**
 * @brief Sets up the NTP service by configuring the time with the specified
 *        GMT offset, daylight offset, and NTP server.
 * 
 * This function attempts to configure the system time using the provided
 * GMT offset, daylight offset, and NTP server. If an exception occurs during
 * the configuration, it catches the exception and prints the error message
 * to the standard error output.
 * 
 * @throws std::exception If an error occurs during the configuration of the time.
 */
void NTPService::setup()
{
    try
    {
        configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

/**
 * @brief Retrieves the current local time.
 * 
 * This function attempts to obtain the current local time and returns it as a 
 * `struct tm`. If the local time cannot be obtained, it prints an error message
 * to the standard output and disconnects the ESP32 from the current WiFi network.
 * 
 * @return struct tm The current local time.
 */ 
struct tm* NTPService::getTime()
{
    struct tm* timeinfo;
    if (!getLocalTime(timeinfo))
    {
        Serial.println("Failed to obtain time");
        APService::Disconnect();
        APService::setup();

    }
    return timeinfo;
}
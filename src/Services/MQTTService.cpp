#include "MQTTService.h"
#include <ArduinoMQTTClient.h>

#include <WiFiClient.h>
#include "APService.h"

const char endpoint[] = "sensor/device09";
const char deviceName[] = "device09"; // Works as topic too
const char password[] = "device09-password";
const char broker[] = "192.168.0.130";
const int port = 1883;

char *failedMessages[5] = {nullptr, nullptr, nullptr, nullptr, nullptr};
int lastValue = 0;

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);
void MQTTService::setup()
{
    if (!APService::isConnected())
    {
        Serial.println("APService is not connected");
        return;
    }
    mqttClient.setUsernamePassword(deviceName, password);
    if (!mqttClient.connect(broker, port))
    {
        Serial.print("MQTT connection failed! Error code = ");
        Serial.println(mqttClient.connectError());
        int count = 0; 
        while (!mqttClient.connected())
        {
            Serial.print(".");
            delay(500);
            count++;

            if(count == 3){
                Serial.println("\nERROR: MQTT request timed out");
                return;
            }
        }
        Serial.println("");
    }

    Serial.println("Connected to MQTT broker");
}

bool MQTTService::sendMessage(const char *message, bool resend)
{
    if (!mqttClient.connected())
    {
        Serial.println("MQTT client is not connected");
        return false;
    }

    mqttClient.beginMessage(endpoint);
    mqttClient.print(message);

    if (!mqttClient.endMessage())
    {
        for (int i = 0; i < 5; i++)
        {
            if (failedMessages[i] == nullptr)
            {
                failedMessages[i] = (char *)malloc(strlen(message) + 1);
                strcpy(failedMessages[i], message);
                lastValue = i;
                return false;
            }
        }

        lastValue = (lastValue + 1) % 5;
        if (failedMessages[lastValue] != nullptr)
        {
            free(failedMessages[lastValue]);
        }
        failedMessages[lastValue] = (char *)malloc(strlen(message) + 1);
        strcpy(failedMessages[lastValue], message);
    }
    if (resend)
    {
        reSendMessages();
    }
    return true;
}

void MQTTService::reSendMessages()
{

    for (int i = 0; failedMessages[i] != NULL; i++)
    {
        int status = sendMessage(failedMessages[i], false);
        if (status)
        {
            free(failedMessages[i]);
            failedMessages[i] = nullptr;
        }

        delay(200);
    }
}

bool MQTTService::isConnected()
{
    return mqttClient.connected();
}
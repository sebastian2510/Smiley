#include <ArduinoMqttClient.h>
class MQTTService {
public:
    static void setup();
    static bool sendMessage(const char* message, bool resend = true);
    static bool isConnected();
private:
    static void reSendMessages();
};
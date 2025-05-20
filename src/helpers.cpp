#include "helpers.h"

void Helpers::formatTime(tm *time, std::string &buffer)
{
    char timeString[20];
    strftime(timeString, sizeof(timeString), "%d-%m-%Y %H:%M:%S", time);
    buffer = std::string(timeString);
}
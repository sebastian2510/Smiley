#pragma once

class NTPService
{
public:
    static void setup();
    static struct tm* getTime();
};
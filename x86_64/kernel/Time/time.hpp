#pragma once
#include "../sources.hpp"
namespace System
{
    struct Time
    {
        uint8_t second;
        uint8_t minute;
        uint8_t hour;
        uint8_t day;
        uint8_t month;
        uint32_t year;
    };
    Time get_time();
    void wait(int seconds);
    int Minutes(int minutes);
    int Hours(int hours);
    int Weeks(int weeks);
    int Months(int months, int type);
    int Years(int years);
}
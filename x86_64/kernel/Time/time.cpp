#include "../sources.hpp"
#include "../IO/IO.hpp"
#include "time.hpp"
#define CMOS_ADRESS 0x70
#define CMOS_DATA 0X71
#define CURRENT_YEAR 2022
namespace System
{
    int century_register = 0x00;
    int get_update_in_progress()
    {
        outb(CMOS_ADRESS, 0x0a);
        return (inb(CMOS_DATA) & 0x80);
    }

    uint8_t get_RTC_register(int reg)
    {
        outb(CMOS_ADRESS, reg);
        return inb(CMOS_DATA);
    }

    Time get_time()
    {
        Time time;
        uint8_t century;
        uint8_t last_second;
        uint8_t last_minute;
        uint8_t last_hour;
        uint8_t last_day;
        uint8_t last_month;
        uint8_t last_year;
        uint8_t last_century;
        uint8_t register2;

        while (get_update_in_progress())
            ;
        time.second = get_RTC_register(0x00);
        time.minute = get_RTC_register(0x02);
        time.hour = get_RTC_register(0x04);
        time.day = get_RTC_register(0x07);
        time.month = get_RTC_register(0x08);
        time.year = get_RTC_register(0x09);
        if (century_register != 0)
        {
            century = get_RTC_register(century_register);
        }
        do
        {
            last_second = time.second;
            last_minute = time.minute;
            last_hour = time.hour;
            last_day = time.day;
            last_month = time.month;
            last_year = time.year;
            last_century = century;
            while (get_update_in_progress())
                ;
            time.second = get_RTC_register(0x00);
            time.minute = get_RTC_register(0x02);
            time.hour = get_RTC_register(0x04);
            time.day = get_RTC_register(0x07);
            time.month = get_RTC_register(0x08);
            time.year = get_RTC_register(0x09);
            if (century_register != 0)
            {
                century = get_RTC_register(century_register);
            }
            if (century_register != 0)
            {
                century = get_RTC_register(century_register);
            }
        } while (last_second != time.second or last_minute != time.minute or last_hour != time.hour or last_day != time.day or last_month != time.month or last_year != time.year or last_century != century);

        if (century_register != 0)
        {
            time.year += century * 100;
        }
        else
        {
            time.year += (CURRENT_YEAR / 100) * 100;
            if (time.year < CURRENT_YEAR)
                time.year += 100;
        }

        return time;
    }

    void wait(int seconds)
    {
        for (int i = 0; i < seconds; i++)
        {
            Time time = get_time();
            int old_second = time.second;
            int current_second = time.second;
            do
            {
                time = get_time();
                current_second = time.second;
            } while (current_second == old_second);
        }
    }
    int Minutes(int minutes){
        return minutes * 60; 
    }
    
    int Hours(int hours){
        return (hours * 60) * 60;
    }

    int Weeks(int weeks){
        return (((weeks * 60) * 60) * 24) * 7;
    }
    ///Types: 0 = 31 days, 1 = 30 days, 2 = 29 days
    int Months(int months, int type = 0){
        if(type == 0){
            return ((((months * 60) * 60) * 24) * 7) * 31;
        }else if(type == 1){
            return ((((months * 60) * 60) * 24) * 7) * 30;
        }else if(type == 2){
            return ((((months * 60) * 60) * 24) * 7) * 29;
        }
        return 0;
    }

    int Years(int years){
        return (((((years * 60) * 60) * 24) * 7) * 31) * 12;
    }

}

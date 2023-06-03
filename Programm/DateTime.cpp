/**
 * Project Time Project
 * @author Niklas Linsler
 * @version 1.0
 */

#include "DateTime.h"
const int DateTime::LEAP_YEAR_ARRAY[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
const int DateTime::NON_LEAP_YEAR_ARRAY[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
const uint32_t DateTime::SECONDS_FOR_SMALLEST_MONTH = 2419200;

#if defined(CONSOLE_HMI_USED)
    HMI &DateTime::hmi = ConsoleHMI::getInstance();
#else
    HMI &DateTime::hmi = HardwareHMI::getInstance();
#endif // CONSOLE_HMI_USED

void DateTime::run()
{
    if (hmi.checkShow())
    {
        hmi.showDateTime(
            day.getCount(),
            month.getCount(),
            year.getCount(),
            hour.getCount(),
            minute.getCount(),
            second.getCount());
    }
    if (hmi.checkRun())
    {
        countSecond();
    }

}

void DateTime::countSecond()
{
    // only update days every 28 days. This is more performant because it does not need to call the functions
    if (updateDaysCounter >= SECONDS_FOR_SMALLEST_MONTH)
    {
        day.setStopCountingAt(getMonthDays(month.getCount()));
        updateDaysCounter = 0;
    }

    second.increment();

    return;
}

int DateTime::getMonthDays(int thisMonth)
{
    if (isLeapYear(year.getCount()))
    {
        return LEAP_YEAR_ARRAY[thisMonth - 1];
    }
    return NON_LEAP_YEAR_ARRAY[thisMonth - 1];
}

bool DateTime::isLeapYear(int year)
{
    if (year % 400 == 0)
        return true;
    else if (year % 100 == 0)
        return false;
    else if (year % 4 == 0)
        return true;
    return false;
}
/**
 * Project Time Project
 * @author Niklas Linsler
 * @version 1.0
 */

#include "HardwareHMI.h"

HardwareHMI *HardwareHMI::hmi = nullptr;

void HardwareHMI::setupHardware()
{
    // output
    gpioA.SetPinMode(LED_1_A, 0b01); // red
    gpioA.SetPinMode(LED_2_A, 0b01); // yellow
    gpioA.SetPinMode(LED_3_A, 0b01); // green
    gpioB.SetPinMode(LED_4_B, 0b01); // blue
    // input
    gpioB.SetPinMode(SW_1_B, 0b00); // sw 1
    gpioB.SetPinMode(SW_2_B, 0b00); // sw 2

    // pushPull
    gpioA.SetOTyp(LED_1_A, true); // red
    gpioA.SetOTyp(LED_2_A, true); // yellow
    gpioA.SetOTyp(LED_3_A, true); // green
    gpioB.SetOTyp(LED_4_B, true); // blue
    gpioB.SetOTyp(SW_1_B, true);  // sw 1
    gpioB.SetOTyp(SW_2_B, true);  // sw 2

    // 2MHz gpio speed
    gpioA.SetOSpeed(LED_1_A, 0); // red
    gpioA.SetOSpeed(LED_2_A, 0); // yellow
    gpioA.SetOSpeed(LED_3_A, 0); // green
    gpioB.SetOSpeed(LED_4_B, 0); // blue
    gpioB.SetOSpeed(SW_1_B, 0);  // sw 1
    gpioB.SetOSpeed(SW_2_B, 0);  // sw 2

    // No pull-up, pull-down push pull
    gpioA.SetPullUpPullDown(LED_1_A, 0); // red
    gpioA.SetPullUpPullDown(LED_2_A, 0); // yellow
    gpioA.SetPullUpPullDown(LED_3_A, 0); // green
    gpioB.SetPullUpPullDown(LED_4_B, 0); // blue

    gpioB.SetPullUpPullDown(SW_1_B, 0); // sw 1
    gpioB.SetPullUpPullDown(SW_2_B, 0); // sw 2

    return;
}

void HardwareHMI::setLEDs(bool led_1, bool led_2, bool led_3, bool led_4)
{
    if (led_1)
        gpioA.SetPin(LED_1_A);
    else
        gpioA.ClearPin(LED_1_A);

    if (led_2)
        gpioA.SetPin(LED_2_A);
    else
        gpioA.ClearPin(LED_2_A);

    if (led_3)
        gpioA.SetPin(LED_3_A);
    else
        gpioA.ClearPin(LED_3_A);

    if (led_4)
        gpioB.SetPin(LED_4_B);
    else
        gpioB.ClearPin(LED_4_B);
}

HardwareHMI *HardwareHMI::getInstance()
{
    if (hmi == nullptr)
    {
        hmi = new HardwareHMI();
    }

    return hmi;
}

void HardwareHMI::showDate(int day, int month, int year)
{
    // separator
    setLEDs(true, false, true, false);
    sleep();
    setLEDs(false, true, false, true);
    sleep();
    setLEDs(true, false, true, false);
    sleep();
    // day
    showNumber((day - day % 10) / 10);
    sleepLong();
    showNumber(day % 10);
    sleepLong();
    // separator
    setLEDs(true, false, true, false);
    sleep();
    setLEDs(false, true, false, true);
    sleep();
    setLEDs(true, false, true, false);
    sleep();
    // month
    showNumber((month - month % 10) / 10);
    sleepLong();
    showNumber(month % 10);
    sleepLong();
    // separator
    setLEDs(true, false, true, false);
    sleep();
    setLEDs(false, true, false, true);
    sleep();
    setLEDs(true, false, true, false);
    sleep();
    // year
    showNumber(year / 1000);
    sleepLong();
    showNumber((year % 1000 - year % 100 - year % 10) / 100);
    sleepLong();
    showNumber((year % 100 - year % 10) / 10);
    sleepLong();
    showNumber(year % 10);
    sleepLong();
    // separator
    setLEDs(true, false, true, false);
    sleep();
    setLEDs(false, true, false, true);
    sleep();
    setLEDs(true, false, true, false);
    sleep();

    // set LEDs to running status 
    setLEDs(isRunning, isRunning, isRunning, isRunning);
    return;
}

void HardwareHMI::showTime(int hour, int minute, int second)
{
    // separator
    setLEDs(true, false, true, false);
    sleep();
    setLEDs(false, true, false, true);
    sleep();
    setLEDs(true, false, true, false);
    sleep();
    // hour
    showNumber((hour - hour % 10) / 10);
    sleepLong();
    showNumber(hour % 10);
    sleepLong();
    // separator
    setLEDs(true, false, true, false);
    sleep();
    setLEDs(false, true, false, true);
    sleep();
    setLEDs(true, false, true, false);
    sleep();
    // minute
    showNumber((minute - minute % 10) / 10);
    sleepLong();
    showNumber(minute % 10);
    sleepLong();
    // separator
    setLEDs(true, false, true, false);
    sleep();
    setLEDs(false, true, false, true);
    sleep();
    setLEDs(true, false, true, false);
    sleep();
    // hour
    showNumber((second - second % 10) / 10);
    sleepLong();
    showNumber(second % 10);
    sleepLong();
    // separator
    setLEDs(true, false, true, false);
    sleep();
    setLEDs(false, true, false, true);
    sleep();
    setLEDs(true, false, true, false);
    sleep();

    // set LEDs to running status
    setLEDs(isRunning, isRunning, isRunning, isRunning);
    return;
}

bool HardwareHMI::checkRun()
{
    // check if run is pressed
    if (gpioB.ReadPin(SW_1_B))
    {
        sleep();
        // debounce
        if (gpioB.ReadPin(SW_1_B))
            // toggle running
            isRunning = !isRunning;
        // show start/stop
        setLEDs(isRunning, isRunning, isRunning, isRunning);
        sleep();
        return isRunning;
    }

    return isRunning;
}

bool HardwareHMI::checkShow()
{
    if (gpioB.ReadPin(SW_2_B))
    {
        // debounce
        sleep();
        return gpioB.ReadPin(SW_2_B);
    }
    return false;
}
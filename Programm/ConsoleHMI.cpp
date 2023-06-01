/**
 * Project Time Project
 * @author Niklas Linsler
 * @version 1.0
 */

#include "ConsoleHMI.h"

ConsoleHMI *ConsoleHMI::hmi = nullptr;

ConsoleHMI *ConsoleHMI::getInstance()
{
    if (hmi == nullptr)
    {
        hmi = new ConsoleHMI();
    }

    return hmi;
}

void ConsoleHMI::showDate(int day, int month, int year)
{
    cout << "Date: "
         << setfill('0') << setw(2) << day << "."
         << setfill('0') << setw(2) << month << "."
         << setfill('0') << setw(2) << year << endl;
    return;
}

void ConsoleHMI::showTime(int hour, int minute, int second)
{
    cout << "Time: "
         << setfill('0') << setw(2) << hour << ":"
         << setfill('0') << setw(2) << minute << ":"
         << setfill('0') << setw(2) << second << endl;
    return;
}

void ConsoleHMI::showDateTime(int day, int month, int year, int hour, int minute, int second)
{
    cout << "Date and Time: "
         << setfill('0') << setw(2) << day << "."
         << setfill('0') << setw(2) << month << "."
         << setfill('0') << setw(4) << year << " - "
         << setfill('0') << setw(2) << hour << ":"
         << setfill('0') << setw(2) << minute << ":"
         << setfill('0') << setw(2) << second << endl;
    return;
}

bool ConsoleHMI::checkRun()
{
    // Finished Counting
    if (this->runNumber == 0)
    {
        runNumber--;
        return false;
    }
    // Still counting
    else if (runNumber > 0)
    {
        this->runNumber--;
        return true;
    }
    // Read new counting value
    else
    {
        runNumber = 0;
        while (runNumber <= 0)
        {
            cout << "Wie viele Sekunden soll der Zähler laufen?" << endl;
            cin >> runNumber;
        }

        if (runNumber > 0)
        {
            return true;
        }
        return false;
    }
}

bool ConsoleHMI::checkShow()
{
    // Finished Counting
    if (this->runNumber == 0)
    {
        return true;
    }
    return false;
}
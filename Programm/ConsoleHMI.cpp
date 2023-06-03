/**
 * Project Time Project
 * @author Niklas Linsler
 * @version 1.0
 */

#include "ConsoleHMI.h"

void ConsoleHMI::showDate(int day, int month, int year)
{
    cout << "Datum: "
         << setfill('0') << setw(2) << day << "."
         << setfill('0') << setw(2) << month << "."
         << setfill('0') << setw(2) << year << endl;
    return;
}

void ConsoleHMI::showTime(int hour, int minute, int second)
{
    cout << "Uhrzeit: "
         << setfill('0') << setw(2) << hour << ":"
         << setfill('0') << setw(2) << minute << ":"
         << setfill('0') << setw(2) << second << endl;
    return;
}

void ConsoleHMI::showDateTime(int day, int month, int year, int hour, int minute, int second)
{
    cout << "Datum und Uhrzeit: "
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
    // Read in new Value
    if (this->runNumber == 0)
    {
        runNumber = 0;
        while (runNumber <= 0)
        {
            cout << "Wie viele Sekunden soll der Zähler laufen?" << endl;
            cin >> runNumber;
                }

        if (runNumber > 0)
        {
            runNumber--;
            return true;
        }
        return false;
    }
    
    // Run one step
    if (runNumber > 0)
    {
        runNumber--;
        return true;
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
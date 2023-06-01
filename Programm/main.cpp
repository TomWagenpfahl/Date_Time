#include <iostream>
#include "DateTime.h"

#include "HMI.h"

using namespace std;

int main()
{
    DateTime dateTime = DateTime(55, 55, 23, 30, 12, 2007);

    // Loop the DateTime Programm
    while (true)
    {
        dateTime.runDateTime();
    }
    return 0;
}

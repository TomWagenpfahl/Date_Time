/**
 * Project Time Project
 * @author Niklas Linsler
 * @version 1.0
 */

#ifndef _DATETIME_H
#define _DATETIME_H

#define CONSOLE_HMI_USED

#include <iostream>

#include "Counter.h"
#include "ModuloCounter.h"
#include "OffsetCounter.h"
#include "HMI.h"
#include "HardwareHMI.h"
#include "ConsoleHMI.h"
#include "DateTime.h"

class DateTime
{
public:
	/**
	 * @brief Construct a new Date Time object and start running
	 *
	 * @param startSecond Seconds to start with
	 * @param startMinute Minutes to start with
	 * @param startHour Hours to start with
	 * @param startDay Days to start with
	 * @param startMonth Month to start with
	 * @param startYear Year to start with
	 */
	DateTime(int startSecond = 0, int startMinute = 0, int startHour = 0, int startDay = 1, int startMonth = 1, int startYear = 2000) : year(startYear),
																																		month(&year, startMonth, 1, 12),
																																		day(&month, startDay, 1, getMonthDays(startMonth)),
																																		hour(&day, startHour, 24),
																																		minute(&hour, startMinute, 60),
																																		second(&minute, startSecond, 60)
	{

	};

	/**
	 * @brief This will run the dateTime Class. Each call may result in one increment
	 *
	 */
	void run();

private:

	/**
	 * @brief Counts up by one second
	 *
	 */
	void countSecond();

	/**
	 * @brief Check if the year provided is a leap year. This is needed to check if february is 28 days or 29 days.
	 *
	 * @param year the year which should be checked
	 * @return true It is a leap year
	 * @return false It is no leap year
	 */
	bool isLeapYear(int year = 2000);

	/**
	 * @brief get how many days the current month has. This means Jan = 31, Feb = 28 or 29 and so on
	 *
	 * @return int
	 */
	int getMonthDays(int thisMonth);

	static HMI &hmi; //! The human machine interface which can either be console or hardware of STM32

	Counter year;		  //! The year counter object
	OffsetCounter month;  //! The month counter object
	OffsetCounter day;	  //! The day counter object
	ModuloCounter hour;	  //! The hour counter object
	ModuloCounter minute; //! The minute counter object
	ModuloCounter second; //! The second counter object

	uint32_t updateDaysCounter; // counts the seconds to update the date of the month once every month period.

	static const uint32_t SECONDS_FOR_SMALLEST_MONTH; //! 60s * 60min * 24h * 28days The time that the smallest month could be. This is needed to update the days not every second but every month.
	static const int LEAP_YEAR_ARRAY[12];			  //! an array which stores all the values of days each month for leap years
	static const int NON_LEAP_YEAR_ARRAY[12];		  //! an array which stores all the values of days each month non for leap years
};

#endif //_DATETIME_H
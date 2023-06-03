/**
 * Project Time Project
 * @author Niklas Linsler
 * @version 1.0
 */

#ifndef _CONSOLEHMI_H
#define _CONSOLEHMI_H

#include "HMI.h"
#include <iomanip>
#include <iostream>
using namespace std;

class ConsoleHMI : public HMI
{
private:
	/**
	 * @brief Construct a console HMI as (Singleton Implementation because it's only one Console)
	 *
	 */
	ConsoleHMI() : runNumber(0){};

	/**
	 * @brief Deleted Copy Constructor. Singleton should not be able to be copied
	 *
	 */
	ConsoleHMI(const ConsoleHMI &) = delete;

	/**
	 * @brief Delete assignment operator (for Singleton)
	 *
	 */
	void operator=(const ConsoleHMI &) = delete;

public:
	/**
	 * @brief Get the instance of ConsoleHMI (Singleton Implementation because it's only one Console)
	 *
	 * @return ConsoleHMI
	 */
	static ConsoleHMI &getInstance()
	{
		static ConsoleHMI hmi; // stores the ConsoleHMI object (Singleton implementation)
		return hmi;
	};

	/**
	 * @brief Show the date in the console (12.10.2000)
	 *
	 * @param day value of the date
	 * @param month value of the month
	 * @param year value of the year
	 */
	void showDate(int day, int month, int year);

	/**
	 * @brief Show the Time in the console (12:35:59)
	 *
	 * @param hour value of the hour
	 * @param minute value of the minute
	 * @param second value of the second
	 */
	void showTime(int hour, int minute, int second);

	/**
	 * @brief Show the date and time in the console (12.10.2000 - 12:35:59)
	 *
	 * @param day value of the date
	 * @param month value of the month
	 * @param year value of the year
	 * @param hour value of the hour
	 * @param minute value of the minute
	 * @param second value of the second
	 */
	void showDateTime(int day, int month, int year, int hour, int minute, int second);

	/**
	 * @brief Should be called in a loop and returns false if min is reached.
	 * 		  returns true if the time should still run
	 */
	bool checkRun();

	/**
	 * @brief Should be called in a loop and returns false date and time should not be shown.
	 * 		  returns true if they should be shown.
	 */
	bool checkShow();

private:
	int32_t runNumber;		//! how often should increment be run
};

#endif //_CONSOLEHMI_H
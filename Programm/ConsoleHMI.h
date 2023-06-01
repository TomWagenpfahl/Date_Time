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
	 * @brief Construct a new Console H M I object
	 * 
	 */
	ConsoleHMI() : runNumber(0){};

public:
	/**
	 * @brief Get the Instance object
	 * 
	 * @return ConsoleHMI* 
	 */
	static ConsoleHMI *getInstance();

	/**
	 * @brief 
	 * 
	 * @param day 
	 * @param month 
	 * @param year 
	 */
	void showDate(int day, int month, int year);

	/**
	 * @brief 
	 * 
	 * @param hour 
	 * @param minute 
	 * @param second 
	 */
	void showTime(int hour, int minute, int second);

	/**
	 * @brief 
	 * 
	 * @param day 
	 * @param month 
	 * @param year 
	 * @param hour 
	 * @param minute 
	 * @param second 
	 */
	void showDateTime(int day, int month, int year, int hour, int minute, int second);

	/**
	 * @brief 
	 * 
	 * @return true 
	 * @return false 
	 */
	bool checkRun();

	/**
	 * @brief 
	 * 
	 * @return true 
	 * @return false 
	 */
	bool checkShow();

private:
	static ConsoleHMI *hmi; // stores the Singleton object
	int32_t runNumber;		// how often should increment be run
};

#endif //_CONSOLEHMI_H
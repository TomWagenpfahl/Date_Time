/**
 * Project Time Project
 * @author Niklas Linsler
 * @version 1.0
 */

#ifndef _HARDWAREHMI_H
#define _HARDWAREHMI_H

#include "HMI.h"
#include "ConsoleHMI.h"
#include "stm_gpio.h"

class HardwareHMI : public HMI
{
private:
	/**
	 * @brief Construct a new Hardware H M I object
	 * 
	 */
	HardwareHMI() : gpioA(GPIOA_ADDRESS),
					gpioB(GPIOB_ADDRESS)
	{
		setupHardware();
	};

	/**
	 * @brief 
	 * 
	 */
	void setupHardware();

	/**
	 * @brief 
	 * 
	 * @param led_1 
	 * @param led_2 
	 * @param led_3 
	 * @param led_4 
	 */
	void setLEDs(bool led_1, bool led_2, bool led_3, bool led_4);

	/**
	 * @brief 
	 * 
	 */
	void sleep()
	{
		for (int i = 0; i < 1000000; i++)
			;
	};

	/**
	 * @brief 
	 * 
	 */
	void sleepLong()
	{
		for (int i = 0; i < 10000000; i++)
			;
	};

	/**
	 * @brief 
	 * 
	 * @param number 
	 */
	void showNumber(int number) { setLEDs(number & 0b1000, number & 0b0100, number & 0b0010, number & 0b0001); };

public:
	/**
	 * @brief Get the Instance object
	 * 
	 * @return HardwareHMI* 
	 */
	static HardwareHMI *getInstance();

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
	void showDateTime(int day, int month, int year, int hour, int minute, int second)
	{
		showDate(day, month, year);
		showTime(hour, minute, second);
	};

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
	static HardwareHMI *hmi; // stores the Singleton object

	StmGpio gpioA; // stores the gpio object of gpio port A
	StmGpio gpioB; // stores the gpio object of gpio port B

	bool isRunning = false; // boolean that stores weather the app is running or is stopped

	static const int LED_1_A = 8;
	static const int LED_2_A = 9;
	static const int LED_3_A = 10;
	static const int LED_4_B = 10;
	static const int SW_1_B = 5;
	static const int SW_2_B = 3;

	static const uint32_t GPIOA_ADDRESS = 0x40020000;
	static const uint32_t GPIOB_ADDRESS = 0x40020400;
};

#endif //_HARDWAREHMI_H
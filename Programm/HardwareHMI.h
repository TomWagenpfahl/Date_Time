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
	 * @brief Construct a HMI that displays on the STM32 Ports as Singleton
	 *
	 * LED 1 (red) is D7 / PA8
	 * LED 2 (yellow) is D8 / PA9
	 * LED 3 (green) is D2 / PA10
	 * LED 4 (blue) is D3 / PB3
	 * SWITCH 1 is D4 / PB5
	 * SWITCH 2 is D6 / PB6
	 */
	HardwareHMI();

	/**
	 * @brief Deleted Copy Constructor. Singleton should not be able to be copied
	 * 
	 */
	HardwareHMI(const HardwareHMI &) = delete;

	/**
	 * @brief Delete assignment operator (for Singleton)
	 * 
	 */
	void operator=(const HardwareHMI &) = delete;

	/**
	 * @brief This will setup the Hardware with output/input, pull up/down, gpio speed
	 *
	 * LED 1 (red) is D7 / PA8
	 * LED 2 (yellow) is D8 / PA9
	 * LED 3 (green) is D2 / PA10
	 * LED 4 (blue) is D3 / PB3
	 * SWITCH 1 is D4 / PB5
	 * SWITCH 2 is D6 / PB6
	 */
	void setupHardware();

	/**
	 * @brief Set the four LEDs with four boolean
	 *
	 * @param led_1 led on = true; led off = false
	 * @param led_2 led on = true; led off = false
	 * @param led_3 led on = true; led off = false
	 * @param led_4 led on = true; led off = false
	 */
	void setLEDs(bool led_1, bool led_2, bool led_3, bool led_4);

	/**
	 * @brief sleep till a counter has counted up
	 *
	 */
	void sleep();

	/**
	 * @brief sleep for a long time
	 *
	 */
	void sleepLong();

	/**
	 * @brief show a specified number on the leds.
	 *
	 */
	void showNumber(int number) { setLEDs(number & 0b1000, number & 0b0100, number & 0b0010, number & 0b0001); };

public:
	/**
	 * @brief Get the instance of HardwareHMI (Singleton implementation)
	 *
	 * @return HardwareHMI
	 */
	static HardwareHMI &getInstance() {
		static HardwareHMI hmi; // stores the HardwareHMI object (Singleton implementation)
		return hmi;
	};

	/**
	 * @brief Show the date on the hardware
	 * 		  This will show
	 *   				1 0 1 0 (separation),
	 * 					0 1 0 1 (separation),
	 *  				1 0 1 0 (separation)
	 * 					day tens,
	 * 					day ones,
	 *  				1 0 1 0 (separation),
	 * 					0 1 0 1 (separation),
	 *  				1 0 1 0 (separation)
	 * 					month tens,
	 * 					month ones,
	 *  				1 0 1 0 (separation),
	 * 					0 1 0 1 (separation),
	 *  				1 0 1 0 (separation)
	 * 					year thousands,
	 * 					year hundreds,
	 * 					year tens,
	 * 					year ones,
	 *  				1 0 1 0 (separation),
	 * 					0 1 0 1 (separation),
	 *  				1 0 1 0 (separation)
	 *
	 * @param day value of the date
	 * @param month value of the month
	 * @param year value of the year
	 */
	void showDate(int day, int month, int year);

	/**
	 * @brief Show the time on the hardware
	 *  		  This will show
	 *   				1 0 1 0 (separation),
	 * 					0 1 0 1 (separation),
	 *  				1 0 1 0 (separation)
	 * 					hour tens,
	 * 					hour ones,
	 *  				1 0 1 0 (separation),
	 * 					0 1 0 1 (separation),
	 *  				1 0 1 0 (separation)
	 * 					minute tens,
	 * 					minute ones,
	 *  				1 0 1 0 (separation),
	 * 					0 1 0 1 (separation),
	 *  				1 0 1 0 (separation)
	 * 					second tens,
	 * 					second ones,
	 *  				1 0 1 0 (separation),
	 * 					0 1 0 1 (separation),
	 *  				1 0 1 0 (separation)
	 *
	 * @param hour value of the hour
	 * @param minute value of the minute
	 * @param second value of the second
	 */
	void showTime(int hour, int minute, int second);

	/**
	 * @brief Show the date and time on the hardware
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
	 * @brief Check if the run button is pressed. Return True if this is the case
	 * 		  Return false if it is not the case.
	 */
	bool checkRun();

	/**
	 * @brief Check if the show button is pressed. Return True if this is the case
	 * 		  Return false if it is not the case.
	 */
	bool checkShow();

private:
	StmGpio gpioA; //! stores the gpio object of gpio port A
	StmGpio gpioB; //! stores the gpio object of gpio port B

	bool isRunning = false; //! boolean that stores weather the app is running or is stopped

	static const int LED_1_A = 8; //! Stores the pin of port A where LED 1 is located
	static const int LED_2_A = 9; //! Stores the pin of port A where LED 2 is located
	static const int LED_3_A = 10; //! Stores the pin of port A where LED 3 is located
	static const int LED_4_B = 10; //! Stores the pin of port B where LED 4 is located
	static const int SW_1_B = 5;   //! Stores the pin of port B where button 1 is located
	static const int SW_2_B = 3;   //! Stores the pin of port B where button 2 is located

	static const uint32_t GPIOA_ADDRESS = 0x40020000; //! Stores the address of port A on STM32F401
	static const uint32_t GPIOB_ADDRESS = 0x40020400; //! Stores the address of port B on STM32F401
};

#endif //_HARDWAREHMI_H
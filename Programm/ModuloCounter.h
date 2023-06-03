/**
 * Project Time Project
 * @author Niklas Linsler
 * @version 1.0
 */

#ifndef _MODULOCOUNTER_H
#define _MODULOCOUNTER_H

#include "Counter.h"

class ModuloCounter : public Counter
{
public:
	/**
	 * @brief Construct a new Modulo Counter object
	 *
	 * @param nextModuloCounter Address of the next modulo counter
	 * @param startValue value at which the counter will start counting
	 * @param moduloValue value at which the counter will reset to zero
	 */
	ModuloCounter(Counter *nextModuloCounter = nullptr, int startValue = 0, int moduloValue = 100) : Counter(startValue),
																									 nextCounter(nextModuloCounter),
																									 moduloValue(moduloValue){};

	/**
	 * @brief Increments the counter and resets to zero when reaching the modulo value
	 *
	 */
	virtual void increment();

	/**
	 * @brief Setter of the modulo value
	 *
	 * @param newValue
	 */
	void setModuloValue(int newValue)
	{
		moduloValue = newValue;
		return;
	};

	/**
	 * @brief Getter of the modulo value
	 *
	 * @return int
	 */
	int getModuloValue()
	{
		return moduloValue;
	};

private:
	Counter *nextCounter; //! Stores the adress of the next modulo counter. This counter is incremented if modulo value is reached
	int moduloValue;	  //! Stores the value at which the next counter is called and this counter is reset
};

#endif //_MODULOCOUNTER_H
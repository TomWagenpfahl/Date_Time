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
	 * @param nextModuloCounter 
	 * @param startValue 
	 * @param moduloValue 
	 */
	ModuloCounter(Counter *nextModuloCounter = nullptr, int startValue = 0, int moduloValue = 100) : Counter(startValue),
																									 nextCounter(nextModuloCounter),
																									 moduloValue(moduloValue){};

	/**
	 * @brief 
	 * 
	 */
	virtual void increment();

	/**
	 * @brief Set the Modulo Value object
	 * 
	 * @param newValue 
	 */
	void setModuloValue(int newValue)
	{
		moduloValue = newValue;
		return;
	};

	/**
	 * @brief Get the Modulo Value object
	 * 
	 * @return int 
	 */
	int getModuloValue()
	{
		return moduloValue;
	};

private:
	Counter *nextCounter; // Stores the adress of the next modulo counter. This counter is incremented if modulo value is reached
	int moduloValue;	  // Stores the value at which the next counter is called and this counter is reset
};

#endif //_MODULOCOUNTER_H
/**
 * Project Time Project
 * @author Niklas Linsler
 * @version 1.0
 */

#ifndef _OFFSETCOUNTER_H
#define _OFFSETCOUNTER_H

#include "ModuloCounter.h"

class OffsetCounter : public ModuloCounter
{
public:
	/**
	 * @brief Construct a new Offset Counter object
	 * 
	 * @param nextCounter 
	 * @param startValue 
	 * @param startCountingAt 
	 * @param stopCountingAt 
	 */
	OffsetCounter(Counter *nextCounter = nullptr, int startValue = 1, int startCountingAt = 1, int stopCountingAt = 30) : ModuloCounter(
																															  nextCounter,
																															  startValue - startCountingAt,
																															  stopCountingAt - startCountingAt + 1),
																														  startCountingAt(startCountingAt),
																														  stopCountingAt(stopCountingAt){};

	/**
	 * @brief Get the Count object
	 * 
	 * @return int 
	 */
	int getCount()
	{
		// ModuloCounter.getCount() is virtual and can be overwritten therefore call it directly
		return ModuloCounter::getCount() + startCountingAt;
	};

	/**
	 * @brief Set the Stop Counting At object
	 * 
	 * @param newStopCountingAt 
	 */
	void setStopCountingAt(int newStopCountingAt) { setModuloValue(newStopCountingAt - startCountingAt + 1); };

	/**
	 * @brief Get the Stop Counting At object
	 * 
	 * @return int 
	 */
	int getStopCountingAt() { return stopCountingAt; };

private:
	int startCountingAt; // Here the counter will start to count after reaching it's maximum value
	int stopCountingAt;	 // Here the counter will stop to count and reset when incrementing again while having this value
};

#endif //_OFFSETCOUNTER_H
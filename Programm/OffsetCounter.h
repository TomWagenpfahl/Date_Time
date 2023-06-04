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
	 * @brief Construct a new Offset Counter object. This will construct a modulo counter that has an offset
	 *
	 * @param nextCounter pointer to the next counter. This counter will be incremented if the stopCountingAt value is reached
	 * @param startValue startvalue has to be larger than startCountingAt
	 * @param startCountingAt here the counter will start and restart if stop value is reached
	 * @param stopCountingAt This is the last value that will be counted. If the value is larger then counter will be set to startCountingAt
	 */
	OffsetCounter(Counter *nextCounter = nullptr, int startValue = 1, int startCountingAt = 1, int stopCountingAt = 30) : ModuloCounter(
																															  nextCounter,
																															  startValue - startCountingAt,
																															  stopCountingAt - startCountingAt + 1),
																														  startCountingAt(startCountingAt),
																														  stopCountingAt(stopCountingAt){};

	/**
	 * @brief Getter of the count variable
	 *
	 * @return int
	 */
	int getCount()
	{
		// ModuloCounter.getCount() is virtual and can be overwritten therefore call it directly
		return ModuloCounter::getCount() + startCountingAt;
	};

	/**
	 * @brief Set where the counter should stop at and reset when counting to a larger number
	 *
	 * @param newStopCountingAt
	 */
	void setStopCountingAt(int newStopCountingAt) { setModuloValue(newStopCountingAt - startCountingAt + 1); };

	/**
	 * @brief Get where the counter should stop at and reset when counting to a larger number
	 *
	 * @return int
	 */
	int getStopCountingAt() { return stopCountingAt; };

private:
	//! Here the counter will start to count after reaching it's maximum value
	int startCountingAt;

	//! Here the counter will stop to count and reset when incrementing again while having this value
	int stopCountingAt;
};

#endif //_OFFSETCOUNTER_H
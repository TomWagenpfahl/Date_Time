/**
 * Project Time Project
 * @author Niklas Linsler
 * @version 1.0
 */

#ifndef _COUNTER_H
#define _COUNTER_H

class Counter
{
public:
	/**
	 * @brief Construct a new Counter object
	 * 
	 * @param startCount 
	 */
	explicit Counter(int startCount = 0) : count(startCount) {}

	/**
	 * @brief 
	 * 
	 */
	virtual int getCount()
	{
		return count;
	};

	/**
	 * @brief 
	 * 
	 */
	virtual void increment()
	{
		count++;
	};

	/**
	 * @brief Set the Count object
	 * 
	 * @param newCount 
	 */
	void setCount(int newCount)
	{
		count = newCount;
	};

private:
	int count; // Stores the count value of the counter object
};

#endif //_COUNTER_H
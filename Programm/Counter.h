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
	 * @brief Construct a new Counter object which counts up one at a time.
	 *
	 * @param startCount
	 */
	explicit Counter(int startCount = 0) : count(startCount) {}

	/**
	 * @brief Getter of the count
	 *
	 * @return int
	 */
	virtual int getCount()
	{
		return count;
	};

	/**
	 * @brief Increments the count by one
	 *
	 */
	virtual void increment()
	{
		count++;
	};

	/**
	 * @brief Setter of the count
	 *
	 * @param newCount
	 */
	void setCount(int newCount)
	{
		count = newCount;
	};

private:
	int count; //! Stores the count value of the counter object
};

#endif //_COUNTER_H
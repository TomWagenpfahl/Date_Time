/**
 * Project Time Project
 * @author Niklas Linsler
 * @version 1.0
 */

#ifndef _HMI_H
#define _HMI_H

class HMI
{
public:
    /**
     * @brief Show the date
     *
     * @param day value of the date
     * @param month value of the month
     * @param year value of the year
     */
    virtual void showDate(int day, int month, int year) = 0;

    /**
     * @brief Show the Time
     *
     * @param hour value of the hour
     * @param minute value of the minute
     * @param second value of the second
     */
    virtual void showTime(int hour, int minute, int second) = 0;

    /**
     * @brief Show the date and the time
     *
     * @param day value of the date
     * @param month value of the month
     * @param year value of the year
     * @param hour value of the hour
     * @param minute value of the minute
     * @param second value of the second
     */
    virtual void showDateTime(int day, int month, int year, int hour, int minute, int second) = 0;

    /**
     * @brief check if the counter should be incremented.
     *        It may be possible that true will be returned but waits for user input till then.
     *
     * @return true increment by one and call again
     * @return false wait and call again
     */
    virtual bool checkRun() = 0;

    /**
     * @brief Check when to show the time. Returns true if time should be shown.
     * 		  Return false if it is not the case.
     */
    virtual bool checkShow() = 0;

    /**
     * @brief Get the Instance object (Singleton implementation: Only one HMI should exist)
     * 
     * @return HMI& 
     */
    static HMI &getInstance();
};

#endif //_HMI_H
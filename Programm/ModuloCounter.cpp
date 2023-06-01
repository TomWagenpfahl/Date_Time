/**
 * Project Time Project
 * @author Niklas Linsler
 * @version 1.0
 */

#include "ModuloCounter.h"

void ModuloCounter::increment()
{
    // Counter.getCount() is virtual and can be overwritten therefore call it directly
    setCount(Counter::getCount() + 1);
    // Counter.getCount() is virtual and can be overwritten therefore call it directly
    if (Counter::getCount() >= moduloValue)
    {
        setCount(0);

        if (nextCounter != nullptr)
        {
            nextCounter->increment();
        }
    }
}

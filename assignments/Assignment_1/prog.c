/**
* @author: Zach Halpern
* @date: 9/3/16
* Assignment 1 for CS220
*/

#include "prog.h"

int nthFib(int n)
{
    int retVal = 1, first = 0, second = 1, counter = 1;
    
    /* Account for out of bounds */
    if (n < 1 || n > 30)
        return -1;

    while (counter < n)
    {
        retVal = first + second;
        first = second;
        second = retVal;
        counter++;
    }
    
    return retVal; 
}

int asq_minus_bsq(int a, int b) 
{
    return a*a - b*b;
}


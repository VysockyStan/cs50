/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */

// Binary search  - iterative method
bool search(int value, int values[], int n)
{
    if(n < 0)
    {
    return false;
    }
    
    int left = 0;
    int right = n - 1;

    while (right >= left)
    {
        int mid = left + (right - left) / 2;

        if (values[mid] == value)
        {
            return true;
        }

        if (values[mid] > value)
        {
            right = mid - 1;
        }
        else
        {
            left = mid + 1;
        }
    }
    
     return false;
    
}

/**
 * Sorts array of n values.
 */
 
 // Bubble sort
void sort(int values[], int n)
{
    if(n < 0 && n > 65536)
    {
    return;
    }
    
    for(int i = 0 ; i < n - 1; i++) 
    { 
       for(int j = 0 ; j < n - i - 1 ; j++) 
        {  
            if(values[j] > values[j+1])
           {           
              int tmp = values[j];
              values[j] = values[j+1] ;
              values[j+1] = tmp; 
           }
        }
    }

}
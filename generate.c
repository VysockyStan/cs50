/**
 * generate.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Generates pseudorandom numbers in [0,LIMIT), one per line.
 *
 * Usage: generate n [s]
 *
 * where n is number of pseudorandom numbers to print
 * and s is an optional seed
 */
 
#define _XOPEN_SOURCE

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// constant
#define LIMIT 65536

int main(int argc, string argv[])
{
    // Checks the number of arguments, that were input by user.
    //if this number is not 2 and 3, prompt for input
    if (argc != 2 && argc != 3)
    {
        printf("Usage: generate n [s]\n");
        return 1;
    }

    // Use function ATOI to convert received argument into integer
    int n = atoi(argv[1]);

    // If the optional seed is used, convert it into integer, if not use function TIME(NULL), 
    // that returns current time since Jan 1st 1970
    if (argc == 3)
    {
        srand48((long int) atoi(argv[2]));
    }
    else
    {
        srand48((long int) time(NULL));
    }

    // loop through the user's input and generate pseudo-random numbers, then output them
    for (int i = 0; i < n; i++)
    {
        printf("%i\n", (int) (drand48() * LIMIT));
    }

    // success
    return 0;
}
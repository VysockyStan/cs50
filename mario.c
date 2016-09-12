#include <stdio.h>
#include <stdlib.h>

int main()
{
    int length;

    do
    {
       printf("Enter amount of rows in the pyramid < 24: ");
       scanf("%i", &length);
    }
    while(length < 1 || length > 23);

    //Creats raws
    for(int i = 1; i < length; i++)
    {
        //Creates spaces
        for(int j = 0; j < length-i-1; j++) printf(" ");

        //Creates left side of the pyramid
        for(int j = 0; j <= i; j++) printf("#");

        //Creates center of the pyramid
        printf("  ");

        //Creates right side of the pyramid
        for (int j = 0; j <= i;  j++)
    	{
    		printf("#");
    	}

    	printf("\n");
    }

    return 0;
}


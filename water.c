#include <stdio.h>
#include <stdlib.h>

int main()
{
// The code below prints the equivalent number of bottles of water
// according with the length of his or her shower in minutes

//i didn't comment this code cause it's too evident
   
    int bottle_amount = 0;
    int minute;

    do 
    {
        printf("Enter the length of your shower: \n");
        minute = GetInt();
    }
    while (minute <= 0);
    
    
   if (minute > 0)
   {
        bottle_amount = minute * 12;
        printf("Number of bottle is: %d\n", bottle_amount);
   }
        
    else printf("Retry");
    


return 0;
}

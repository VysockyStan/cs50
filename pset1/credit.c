#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <math.h>

int main()
{
    long long card_number;
 
    // Ask for user's input  

    do
    {printf("Enter card number: \n");
    card_number = GetLongLong();
    }
    while (card_number < 0);

    // Counts a number of digits
    int dig_count = 0;
    long long digits = card_number;
    
    while (digits > 0)
    {
        digits = digits/10;
        dig_count++;
    }
    
    //Check if the card is valid according to the length
    if ((dig_count != 13) && (dig_count != 15) && (dig_count != 16))
    {
        printf("INVALID\n");
    }
    
    //Getting array of digits
    int number[dig_count];
   
    for (int i = 0; i < dig_count; i++)
    {
        number[i] = card_number % 10;
        card_number = card_number / 10;
    }
    
     
    int original_number[dig_count];
    for (int i = 1; i < dig_count; i++)
    {
        original_number[i] = number[i];
    }
    
   //Multiply by 2 every digit at even place 
    for (int i = 1; i < dig_count; i+=2)
    {
        number[i] = number[i] * 2;
    }
    
    int sum = 0;
    int temp;
    
    //Check which card was entered
    if (dig_count == 13)
    {
      for (int i = 0; i < dig_count; i++)
      {
        temp = (number[i] % 10) + (number[i]/10 % 10);
        sum = sum + temp;
      }
      if (original_number[12] == 4 && sum % 10 == 0)
      {
        printf("VISA\n");
      }
      else
      {
        printf("INVALID\n");
      }
    }
    if (dig_count == 15)
    {
      for (int i = 0; i < dig_count; i++)
      {
        temp = (number[i] % 10) + (number[i]/10 % 10);
        sum = sum + temp;
      }
      if (original_number[14] == 3 && sum % 10 == 0 && (original_number[13] == 4 || original_number[13] == 7))
      {
        printf("AMEX\n");
      }
      else
      {
        printf("INVALID\n");
      }
    }
    if (dig_count == 16)
    {
      for (int i = 0; i < dig_count; i++)
      {
        temp = (number[i] % 10) + (number[i]/10 % 10);
        sum = sum + temp;
      }
      if (original_number[15] == 4 && sum % 10 == 0)
      {
        printf("VISA\n");
      }
      else if (original_number[15] == 5 && sum % 10 == 0 && (original_number[14] == 1 || original_number[14] == 2 || original_number[14] == 3 || original_number[14] == 4 || original_number[14] == 5))
        {
            printf("MASTERCARD\n");
        }
      else
      {
        printf("INVALID\n");
      }
    }
    
return 0;
}

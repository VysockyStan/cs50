#include <stdio.h>
#include <stdlib.h>

int main()
{
// Program that prompts the user for a credit card number and then
// reports whether it is a valid American Express, MasterCard or Visa card number.

    long long card_number;
    int dig_count = 0;

   // Ask for credit card number
    do
    {
    printf("Enter your credit card: ");
    card_number = GetLongLong();

    }
    while (card_number < 0);

    //Get number of digits in card number
    long long temp = card_number;
    while (temp >= 1)
    {
        temp = temp / 10;
        dig_count++;
    }

    //Check if the card is valid according to the length
    if (!(dig_count == 13 || dig_count == 15 || dig_count == 16))
    {
        printf("INVALID\n");
        exit(1);
    }

    //Put the card number into array
    int number[dig_count];
    temp = card_number;

    for (int i = 0, j = dig_count-1; i < dig_count; i++)
    {
        number[j--] = temp % 10;
        temp /= 10;
    }

    //Get the sum of numbers, that are placed at the even places
    int summa = 0;
    int x;
    for (int i = 1; i < dig_count; i += 2)
    {
        x = number[i]*2;
        summa += x / 10 + x % 10;
    }

    //Adding the rest of numbers to the sum above
    for (int i = 0; i < dig_count; i+=2)
    {
        summa += number[i];
    }

    //Check if the last digit is 0
    if(summa % 10 != 0)
    {
        printf("INVALID");
        exit(1);
    }

    //Check the initial digits and print the result
    x = number[0] * 10 + number[1];

    switch(dig_count)
    {
        case 13: if(number[0] == 4) printf("VISA"); break;
        case 15: if(x == 34 || x == 37) printf("AMERICAN"); break;
        case 16: if(number[0] == 4) printf("VISA");
                 else if(x > 50 && x < 56) printf("MASTER");
    }

}

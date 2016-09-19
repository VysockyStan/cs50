#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>


int main(void)
{
    // Почему-то не проходит проверку,если активна printf, а без неё проходит.
    //printf("Enter user's name: \n");
    string name = GetString();
    
    int first = 0;

    // Get first letter and check spaces
    while (name[first] == ' ')
    {
        first++;
    }

    printf("%c", toupper(name[first]));

    //  Check the rest of name
    for (int i = first + 1, j = strlen(name); i < j; i++)
    {
        // Get Letter after space
        while (name[i] == ' ')
        {
            i++;

            // print if next char is not space
            if ( i < j && name[i] != ' ')
            {
                printf("%c", toupper(name[i]));
            }
        }   
    }

    // Print new line
    printf("\n");
  

}

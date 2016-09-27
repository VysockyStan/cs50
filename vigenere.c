#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{
    //Check number of parameters
    if (argc != 2)
        {
            printf("! Try again.\n");
            return 1;
        }
   
    //loop through the key to check if it is alphabetical
    int argv_length = strlen(argv[1]);
    for (int i = 0; i < argv_length; i++)
        {
            if (!isalpha(argv[1][i]))
            {
                printf("Wrong input! Try again.\n");
                return 1;
            }
        }
    
    //GetTing the user's string
    printf("plaintext:");
    string input_text = GetString();
      
    //Declare variables and setting them to '0'
    int i = 0;
    int modulo = 0;
    int input_length = 0;
    int key_index = 0;
    
    
    string key = argv[1];
        
    printf("ciphertext:");
    //Loop through user's input
    for (i = 0, input_length = strlen(input_text); i < input_length; i++)
        { 
            //Checking if user's input is alphabetical, then make cipher
            if (isalpha(input_text[i]))
            {
                key_index = modulo % strlen(key);
                
                //Get cipher of thr input text using formula ci = (pi + kj) % 26 
                //depending on letter case and according to the positions of letters in ASCII table
                
                if (islower(input_text[i]))
                {
                    if (islower(key[key_index]))
                    {
                        int lower_output = ((input_text[i] - 'a' + key[key_index] - 'a') % 26) + 'a';
                        printf("%c", lower_output);
                    }
                    else
                    {
                        int lower_output = ((input_text[i] - 'a' + key[key_index] - 'A') % 26) + 'a';
                        printf("%c", lower_output);
                    }
                }
                if (isupper(input_text[i]))
                {
                    if (islower(key[key_index]))
                    {
                        int upper_output = ((input_text[i] - 'A' + key[key_index] - 'a') % 26) + 'A';
                        printf("%c", upper_output);
                    }
                    else
                    {
                        int upper_output = ((input_text[i] - 'A' + key[key_index] - 'A') % 26) + 'A';
                        printf("%c", upper_output);
                    }
                }
                
            //increment key position (modulo) sto use next letter in key
            modulo++;
            }
            else
            {
                //if input is not alphabetical output chars as they are
                printf("%c", input_text[i]);
            }
        }
        
        printf("\n");
    
}

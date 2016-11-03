#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{

    int key;
    int encrypted_text;
   
    // accepts only two command line arguments
    if (argc != 2)
    {
        printf("Wrong input! Try again.\n");
        return 1;
    }
    
    // get input text
    printf("plaintext:");
    string text = GetString();

    // convert that string to an actual int
    key = atoi(argv[1]);
    
    // if key is greater than or equal 26, modulo it 26 to wrap back to A after Z
    if (key >= 26)
    {
        key = (key % 26);
    }

    printf("ciphertext:");
    // Loop through input string
    for(int i = 0, length = strlen(text); i < length; i++)
    {
        // get encrypted
        encrypted_text = (text[i] + key);
            
        // wrapping after Z for uppercase letters
        if (isupper(text[i]) && (encrypted_text > 'Z'))
        {
            encrypted_text = (encrypted_text - 26);
        }
            
        // wrapping after z for lowercase letters
        if (islower(text[i]) && (encrypted_text > 'z'))
        {
            encrypted_text = (encrypted_text - 26);
        }
            
        // if char is alphabetical, print encrypted text
        if (isalpha(text[i]))
        {
            printf("%c", encrypted_text);
        }
         
       // if it is not an alphabetical character, print input text  
        else
        {
            printf("%c", text[i]);
        }
            
    }
    
        printf("\n");
        
        return 0;
    
}

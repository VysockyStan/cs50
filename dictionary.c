/**
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

#include "dictionary.h"
#define TABLE_LENGTH 37

typedef struct node
{
    char word[LENGTH + 1];
    struct node* next;
} node;

node* hashTable[TABLE_LENGTH];
int wordCount = 0;
char word[LENGTH + 1];

//Hash Function below is used to hash words for the hash table
int hashFunc(char* word)
{
    int index = 0;

    // get sum of ascii values in the word
    for (int i = 0; word[i] != '\0'; i++)
        // 
        index += tolower(word[i]);

    // returns index to store the word in bucket of hashtable
    return index % TABLE_LENGTH;
}

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    //get length of the word
    int length = strlen(word);
    
    //temp array for storing the word
    char tmpWord[LENGTH + 1];
    
    for(int i = 0; i < length; i++)
    {
        //convert letters to lower case
        tmpWord[i] = tolower(word[i]);
    }
    
    //add the end of the word
    tmpWord[length] = '\0';
    
    //hash the word
    int hashValue = hashFunc(tmpWord);
    
    if(hashTable[hashValue] == NULL)
    {
    return false;
    }
    
    //create rursor-node to traverse through the hash table
    node* cursor = hashTable[hashValue];
    
    while(cursor != NULL)
    {
        //compare words 
        if(strcmp(tmpWord, cursor -> word) == 0)
        return true;
        
        cursor = cursor -> next;
    }
    
    return false;
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    //open dictionary file
    FILE* file = fopen(dictionary, "r");
    
    if (!(fopen(dictionary, "r")))
        return false;
    
    //get words from dictionary while it is not end of file
    while(fscanf(file, "%s", word) != EOF)
    {
        node* newNode = malloc(sizeof(node));
        
        //if we are getting out of memory, return false
        if(newNode == NULL)
        {
        //unload()
        return false;
        }
        
        //copy words to a node
        strcpy(newNode -> word, word);
        
        //hash a word with hash function
        int hashWord = hashFunc(word);
        
        //add nodes to the hashtable
        if(hashTable[hashWord] == NULL)
        {
           //it will be the first node in Linked List
            hashTable[hashWord] = newNode;
            newNode -> next = NULL;
        }
        else
        {
            //add new node to the Linked list
            newNode -> next = hashTable[hashWord];
            hashTable[hashWord] = newNode;
        }
        //count words in the dictionary
        wordCount++;
    }
    fclose(file);
    
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    //returns number of words, counted in load function
    return wordCount;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    for (int i = 0; i < TABLE_LENGTH; i++)
    {
        node* cursor = hashTable[i];
        
        while(cursor != NULL)
        {
            node* tmp = cursor;
            cursor = cursor -> next;
            free(tmp);
            
            return true;
        }
        hashTable[i] = NULL;
    }
    
    return false;
}


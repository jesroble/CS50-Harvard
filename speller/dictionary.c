// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

int wcount = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int index = hash(word);

    node *newnode = table[index];
    if (newnode == NULL)
        return false;

    // check if the word is in the dictionary
    while(newnode)
    {
        if (strcasecmp(word, newnode->word) == 0)
            return true;
        newnode = newnode->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    char words[LENGTH + 1];

    FILE *source = fopen(dictionary, "r");
    if (source == NULL)
        return false;

    // count words and copy them into the hash table
    while (fscanf(source, "%s", words) != EOF)
    {
        node *newnode = malloc(sizeof(node));
        if (newnode == NULL)
            return false;

        strcpy(newnode->word, words);
        newnode->next = NULL;

        int i = hash(words);
        if (table[i] == NULL)
            table[i] = newnode;
        else
        {
            newnode->next = table[i];
            table[i] = newnode;
        }
        wcount++;
    }
    fclose(source);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return wcount;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    node *tmp = NULL;

    //frees every single word one by one
    for(int i = 0; i < N; i++)
    {
        tmp = table[i];
        while(table[i] != NULL)
        {
            tmp = tmp->next;
            free(table[i]);
            table[i] = tmp;
        }
    }
    return true;
}

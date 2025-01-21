#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

float count_letters(string text)
{
    float n;

    n = 0;
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (isalpha(text[i]))
            n++;
    }
    return (n);
}

float count_words(string text)
{
    float n;

    n = 1;
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (text[i] == ' ')
            n++;
    }
    return (n);
}

float count_sentences(string text)
{
    float n;

    n = 0;
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
            n++;
    }
    return (n);
}

float ft_readability(float letters, float words, float sentences)
{
    float L;
    float S;
    float index;

    L = (letters / words) * 100;
    S = (sentences / words) * 100;
    index = (0.0588 * L) - (0.296 * S) - 15.8;
    return (round(index));
}

int main(void)
{
    float letters;
    float words;
    float sentences;
    float readability;
    string text = get_string("Text: ");

    letters = count_letters(text);
    words = count_words(text);
    sentences = count_sentences(text);
    readability = ft_readability(letters, words, sentences);

    if (readability < 1)
        printf("Before Grade 1\n");
    else if (readability >= 1 && readability <= 16)
        printf("Grade %i\n", (int) readability);
    else if (readability > 16)
        printf("Grade 16+\n");
    return (0);
}

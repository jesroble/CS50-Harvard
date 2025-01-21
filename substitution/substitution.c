#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return (1);
    }
    if (strlen(argv[1]) != 26)
    {
        printf("Usage: key must be size 26\n");
        return (1);
    }

    // looks por repeated characters by comparing each individually
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if (!isalpha(argv[1][i]))
        {
            printf("Usage: key must contaain only alphabetical characters\n");
            return (1);
        }
        for (int j = i + 1; j < strlen(argv[1] + 1); j++)
        {
            if (toupper(argv[1][i]) == toupper(argv[1][j]))
            {
                printf("Usage: key must not contain repeated characters\n");
                return (1);
            }
        }
    }

    string plain = get_string("Plaintext: ");
    printf("ciphertext: ");

    // output each character
    for (int k = 0; plain[k] != '\0'; k++)
    {
        if (plain[k] >= 'A' && plain[k] <= 'Z')
        {
            printf("%c", toupper(argv[1][plain[k] - 'A']));
        }
        if (plain[k] >= 'a' && plain[k] <= 'z')
        {
            printf("%c", tolower(argv[1][plain[k] - 'a']));
        }
        else if (!isalpha(plain[k]))
        {
            printf("%c", plain[k]);
        }
    }
    printf("\n");
    return (0);
}

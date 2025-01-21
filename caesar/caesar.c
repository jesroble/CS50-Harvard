#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    if (argc == 2)
    {
        string key = argv[1];
        for (int i = 0; key[i] != '\0'; i++)
        {
            if (!isdigit(key[i]))
            {
                printf("Usage: ./caesar key\n");
                return 1;
            }
        }
        int k = atoi(key);
        string str = get_string("plaintext:  ");
        printf("ciphertext: ");
        for (int i = 0; str[i] != '\0'; i++)
        {
            if (str[i] >= 'a' && str[i] <= 'z')
                printf("%c", (((str[i] - 'a') + k) % 26) + 'a');
            else if (str[i] >= 'A' && str[i] <= 'Z')
                printf("%c", (((str[i] - 'A') + k) % 26) + 'A');
            else
                printf("%c", str[i]);
        }
        printf("\n");
        return (0);
    }
    else
    {
        printf("Usage: ./caesar key\n");
        return (1);
    }
}

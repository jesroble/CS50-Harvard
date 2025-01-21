#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int score(char *str)
{
    int score;

    score = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (isupper(str[i]))
            score += POINTS[str[i] - 'A'];
        else if (islower(str[i]))
            score += POINTS[str[i] - 'a'];
    }
    return (score);
}

int main(void)
{
    char *p1;
    char *p2;
    int sum1;
    int sum2;

    p1 = get_string("Player 1; ");
    p2 = get_string("Player 2; ");
    sum1 = score(p1);
    sum2 = score(p2);
    if (sum1 > sum2)
        printf("Player 1 wins!\n");
    else if (sum1 < sum2)
        printf("Player 2 wins!\n");
    else if (sum1 == sum2)
        printf("Tie!\n");
    return (0);
}

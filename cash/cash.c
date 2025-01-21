#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int change;
    int coins = 0;
    do
    {
        change = get_int("Change owed: ");
    }
    while (change < 0);
    while (change > 0)
    {
        if (change - 25 >= 0)
        {
            change -= 25;
            coins++;
        }
        else if (change - 10 >= 0)
        {
            change -= 10;
            coins++;
        }
        else if (change - 5 >= 0)
        {
            change -= 5;
            coins++;
        }
        else if (change - 1 >= 0)
        {
            change -= 1;
            coins++;
        }
    }
    printf("%d\n", coins);
}

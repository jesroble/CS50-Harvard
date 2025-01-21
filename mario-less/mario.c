#include <cs50.h>
#include <stdio.h>

void piramid(int e, int b)
{
    for (int i = 0; i < e; i++)
    {
        printf(" ");
    }
    for (int i = 0; i < b; i++)
    {
        printf("#");
    }
}

int main(void)
{
    int n;
    int e;
    int b;
    do
    {
    n = get_int("Heihgt: ");
    }
    while (n < 1);
    b = 1;
    for (int i = 0; i < n; i++)
    {
        e = n - b;
        piramid(e, b);
        b++;
        printf("\n");
    }
    return (0);
}

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

void luhn_algorithm(long n)
{
    int even;
    int sum;
    int digit;

    even = 1;
    sum = 0;
    while (n > 0)
    {
        digit = n % 10;
        if (even == 1)
            sum += digit;
        else if (even == -1)
        {
            if (2 * (n % 10) > 9)
                sum += (2 * digit) / 10 + 2 * digit;
            else
                sum += 2 * (n % 10);
        }
        n /= 10;
        even *= -1;
    }
    if (!(sum % 10 == 0))
    {
        printf("INVALID\n");
        exit(0);
    }
}

int get_start(long n)
{
    while (n > 99)
    {
        n /= 10;
    }
    return (n);
}

int get_len(long n)
{
    int len;

    len = 0;
    while (n > 0)
    {
        n /= 10;
        len++;
    }
    return (len);
}

int main(void)
{
    long card;
    int len;
    int start;

    card = get_long("Number: ");

    luhn_algorithm(card);
    len = get_len(card);
    start = get_start(card);
    
    if (len == 15 && (start == 34 || start == 37))
        printf("AMEX\n");
    else if (len == 16 && (start >= 51 && start <= 55))
        printf("MASTERCARD\n");
    else if ((len == 13 && (start > 39 && start < 50)) || (len == 16 && (start > 39 && start < 50)))
        printf("VISA\n");
    else
        printf("INVALID\n");
    return (0);
}

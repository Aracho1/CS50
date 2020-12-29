#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    float dollars;
    do
    {
        dollars = get_float("Cash owed: ");
    }
    while (dollars <= 0);

    int cents = round(dollars * 100);

    int coins = 0;

//25c, 10c, 5c, 1c

    while (cents >= 25)
    {
        cents -= 25;
        coins++;
    }

    while (cents >= 10 && cents < 25)
    {
        cents -= 10;
        coins++;
    }

    while (cents >= 5 && cents < 25 && cents < 10)
    {
        cents -= 5;
        coins++;
    }
    while (cents >= 1 && cents < 25 && cents < 10 && cents < 5)
    {
        cents -= 1;
        coins++;
    }

    printf("%i\n", coins);
}
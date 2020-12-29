#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    long cc = get_long("Number: ");
    long cc_digits = cc;

    //get number of digits
    int digits = 1;

    while (cc_digits / 10 > 1)
    {
        digits++;
        cc_digits /= 10;
    } // digits = number of digits

    // check the sum of even digits
    int even_sum = 0;
    for (int i = 1; i < digits; i += 2)
    {
        long n1 = cc / (long) pow(10, i);
        int n2 = n1 % 10;
        n2 *= 2;
        while (n2 > 9)
        {
            n2 = n2 % 10 + n2 / 10;
        }
        int n3 = n2 % 10;
        even_sum += n3;
    }

    // check the sum of odd digits
    int odd_sum = 0;
    for (int i = 0; i < digits; i += 2)
    {
        long n1 = cc / (long) pow(10, i);
        int n2 = n1 % 10;
        odd_sum += n2;
    }

    //check the total sum
    int total_sum = even_sum + odd_sum;

    if (total_sum % 10 != 0)
    {
        printf("INVALID\n");
    }
    else
    {
        long amex = cc / (long) pow(10, 13);
        long mastercard = cc / (long) pow(10, 14);
        long visa1 = cc / (long) pow(10, 12);
        long visa2 = cc / (long) pow(10, 15);

        if (digits == 15 && (amex == 34 || amex == 37))
        {
            printf("AMEX\n");
            return 0;
        }

        if (digits == 16 && mastercard >= 51 && mastercard <= 55)
        {
            printf("MASTERCARD\n");
            return 0;
        }

        if ((digits == 13 && visa1 == 4) || (digits == 16 && visa2 == 4))
        {
            printf("VISA\n");
            return 0;
        }

        else
        {
            printf("INVALID\n");
        }

    }

}

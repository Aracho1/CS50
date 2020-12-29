#include <stdio.h>
#include <cs50.h>


int main(void)
{
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height > 8 || height < 1);
    //height of the pyramid
    for (int i = 0; i < height; i++)
    {
        //space
        for (int j = height - 1; j > i; j--)
        {
            printf(" ");
        }
        // new line
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}
#include <stdio.h>
#include <cs50.h>
void print(char c, int n);

int main(void)
{
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height > 8 || height < 1);
    for (int i = 0; i < height; i++)
    {
        print(' ', height-1-i);
        print('#', i+1);
        print(' ', 2);
        print('#', i+1);
        printf("\n");
    }

}

void print(char c, int height)
{
    for (int i = 0; i < height; i++)
    {
        printf("%c", c);
    }
}
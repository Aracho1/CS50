#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    //check if there is just one argument
    if (argc == 2)
    {
        //check if every character is a digit number
        for (int i = 0; i < strlen(argv[1]); i++)
        {
            //if not, prompt message
            if (isdigit(argv[1][i]) == 0)
            {
                printf("Usage: ./casesar key\n");
                return 1;
            }
        }
        //if it is, convert the digit into an integer key
        int key = atoi(argv[1]);

        //get text input from the user
        string plaintext = get_string("plaintext: ");
        printf("ciphertext: ");
        for (int j = 0; j < strlen(plaintext); j++)
        {
            if (isalpha(plaintext[j]))
            {
                if (isupper(plaintext[j]))
                {
                    printf("%c", (((plaintext[j] - 66) + key) % 26) + 66);
                }
                else
                {
                    printf("%c", (((plaintext[j] - 97) + key) % 26) + 97);
                }
            }

            // if it isn't, leave the character as it is
            else if (isalpha(plaintext[j]) == 0)
            {
                printf("%c", plaintext[j]);
            }
        }
    }
    else
    {
        printf("Usage: ./casesar key\n");
        return 1;
    }
    printf("\n");
}
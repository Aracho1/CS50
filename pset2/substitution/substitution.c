#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, string argv[])
{

    string key = argv[1];

    if (argc == 2)
    {

        //check key length

        if (strlen(argv[1]) == 26)
        {

            //find non-alphabetic letter and reject

            for (int i = 0; i < 26; i++)
            {
                if (isalpha(key[i]) == 0)
                {
                    printf("invalid key\n");
                    return 1;
                }
            }

            //find duplicates and reject

            for (int j = 0; j < 26; j++)
            {
                for (int k = j + 1; k < 26; k++)
                {
                    if (key[j] == key[k])
                    {
                        printf("duplicate key\n");
                        return 1;
                    }
                }
            }

            string text = get_string("plaintext: ");
            printf("ciphertext: ");

            for (int y = 0; y < strlen(text); y++)
            {
                if (isalpha(text[y]))
                {
                    if (isupper(text[y]))
                    {
                        int upperposition = text[y] - 65;
                        if (isupper(key[upperposition]))
                        {
                            printf("%c", key[upperposition]);
                        }
                        else
                        {
                            printf("%c", key[upperposition] - 32);
                        }
                    }
                    else
                    {
                        int lowerposition = text[y] - 97;
                        if (islower(key[lowerposition]))
                        {
                            printf("%c", key[lowerposition]);
                        }
                        else
                        {
                            printf("%c", key[lowerposition] + 32);
                        }
                    }
                }
                else
                {
                    printf("%c", text[y]);
                }

            }

        }
        else
        {
            printf("invalid key\n");
            return 1;
        }
    }
    else
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    printf("\n");
    return 0;
}
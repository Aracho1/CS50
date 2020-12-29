#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int main(void)
{
    int letters = 0;
    int word = 0;
    int sentences = 0;

    string text = get_string("Text: ");

    // count letters
    for (int i = 0; i < strlen(text); i++)
    {
        if (isalnum(text[i]))
        {
            letters++;
        }
    }
    // printf("%i letter(s)\n", letters);

    //count words
    for (int j = 0; j < strlen(text); j++)
    {
        if (isspace(text[j]))
        {
            word++;
        }
    }
    int words = word + 1;
    // printf("%i word(s)\n", words);

    //count sentences
    for (int k = 0; k < strlen(text); k++)
    {
        if (text[k] == '.' || text[k] == '!' || text[k] == '?')
        {
            sentences++;
        }
    }
    // printf("%i sentence(s)\n", sentences);

    float L = (float) letters / (float) words * 100;
    float S = (float) sentences / (float) words * 100;
    int index = round(0.0588 * L - 0.296 * S - 15.8);

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 1 && index <= 16)
    {
        printf("Grade %i\n", index);
    }
    else
    {
        printf("Grade 16+\n");
    }
}

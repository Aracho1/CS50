#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    //ensure user used two words
    if (argc != 2)
    {
        return 1;
    }

    // Open memory card
    FILE *file = fopen(argv[1], "r");
    if (!file)
    {
        return 1;
    }

    // Read 512 bytes into a buffer
    unsigned char buffer[512];

    int counter = 0;

    int new_jpg = 0;

    FILE *picture = NULL;

    while (fread(buffer, 512, 1, file) == 1)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (new_jpg == 1)
            {
                fclose(picture);
            }
            else
            {
                new_jpg = 1;
            }

            char filename[8];
            sprintf(filename, "%03d.jpg", counter++);
            picture = fopen(filename, "w");
            if (picture == NULL)
            {
                return 1;
            }
        }

        if (new_jpg == 1)
        {
            fwrite(&buffer, 512, 1, picture);
        }
    }

    fclose(file);
    fclose(picture);

    return 0;
}

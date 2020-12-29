#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int k = 0; k < width; k++)
        {
            int avg = round((image[i][k].rgbtBlue + image[i][k].rgbtGreen + image[i][k].rgbtRed) / 3.0);
            image[i][k].rgbtBlue = avg;
            image[i][k].rgbtGreen = avg;
            image[i][k].rgbtRed = avg;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int k = 0; k < width; k++)
        {
            int originalBlue = image[i][k].rgbtBlue;
            int originalGreen = image[i][k].rgbtGreen;
            int originalRed = image[i][k].rgbtRed;

            int blue = round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);
            int green = round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);
            int red = round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);

            if (blue > 255)
            {
                image[i][k].rgbtBlue = 255;

            }
            else
            {
                image[i][k].rgbtBlue = blue;
            }

            if (green > 255)
            {
                image[i][k].rgbtGreen = 255;
            }
            else
            {
                image[i][k].rgbtGreen = green;

            }
            if (red > 255)
            {
                image[i][k].rgbtRed = 255;

            }
            else
            {
                image[i][k].rgbtRed = red;

            }
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int middle = width / 2;

    for (int i = 0; i < height; i++)
    {
        for (int k = 0; k < middle; k++)
        {
            RGBTRIPLE temp = image[i][k];
            image[i][k] = image[i][width - 1 - k];
            image[i][width - 1 - k] = temp;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int k = 0; k < width; k++)
        {
            copy[i][k] = image[i][k];
        }
    }

    for (int i = 0; i < height; i++)
    {


        for (int k = 0; k < width; k++)
        {
            float counter = 0;
            int greenSum = 0;
            int blueSum = 0;
            int redSum = 0;

            if (i >= 0 && k - 1 >= 0)
            {
                counter++;
                greenSum += copy[i][k - 1].rgbtGreen;
                redSum += copy[i][k - 1].rgbtRed;
                blueSum += copy[i][k - 1].rgbtBlue;
            }

            if (i >= 0 && k >= 0)
            {
                counter++;
                greenSum += copy[i][k].rgbtGreen;
                redSum += copy[i][k].rgbtRed;
                blueSum += copy[i][k].rgbtBlue;
            }

            if ((i >= 0 && k + 1 >= 0) && (k + 1 < width))
            {
                counter++;
                greenSum += copy[i][k + 1].rgbtGreen;
                redSum += copy[i][k + 1].rgbtRed;
                blueSum += copy[i][k + 1].rgbtBlue;
            }


            if (i - 1 >= 0 && k - 1 >= 0)
            {
                counter++;
                greenSum += copy[i - 1][k - 1].rgbtGreen;
                redSum += copy[i - 1][k - 1].rgbtRed;
                blueSum += copy[i - 1][k - 1].rgbtBlue;
            }



            if ((i + 1 >= 0 && k - 1 >= 0) && (i + 1 < height))
            {
                counter++;
                greenSum += copy[i + 1][k - 1].rgbtGreen;
                redSum += copy[i + 1][k - 1].rgbtRed;
                blueSum += copy[i + 1][k - 1].rgbtBlue;
            }

            if (i - 1 >= 0 && k >= 0)
            {
                counter++;
                greenSum += copy[i - 1][k].rgbtGreen;
                redSum += copy[i - 1][k].rgbtRed;
                blueSum += copy[i - 1][k].rgbtBlue;
            }

            if ((i + 1 >= 0 && k >= 0) && (i + 1 < height))
            {
                counter++;
                greenSum += copy[i + 1][k].rgbtGreen;
                redSum += copy[i + 1][k].rgbtRed;
                blueSum += copy[i + 1][k].rgbtBlue;
            }

            if ((i - 1 >= 0 && k + 1 >= 0) && (k + 1 < width))
            {
                counter++;
                greenSum += copy[i - 1][k + 1].rgbtGreen;
                redSum += copy[i - 1][k + 1].rgbtRed;
                blueSum += copy[i - 1][k + 1].rgbtBlue;
            }



            if ((i + 1 >= 0 && k + 1 >= 0) && (k + 1 < width && i + 1 < height))
            {
                counter++;
                greenSum += copy[i + 1][k + 1].rgbtGreen;
                redSum += copy[i + 1][k + 1].rgbtRed;
                blueSum += copy[i + 1][k + 1].rgbtBlue;
            }

            image[i][k].rgbtGreen = round(greenSum / counter);
            image[i][k].rgbtBlue = round(blueSum / counter);
            image[i][k].rgbtRed = round(redSum / counter);

        }
    }
}


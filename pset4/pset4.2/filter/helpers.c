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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    //1. make a copy
    RGBTRIPLE copy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int k = 0; k < width; k++)
        {
            copy[i][k] = image[i][k];
        }
    }

    //2. compute the GX value (treat outside border as 0 values)
    for (int i = 0; i < height; i++)
    {
        for (int k = 0; k < width; k++)
        {
            int GxB = 0, GxR = 0, GxG = 0, GyB = 0, GyR = 0, GyG = 0;
            int index = 0;
            int factorsX[] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
            int factorsY[] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};


            for (int m = -1; m < 2; m++)
            {
                for (int n = -1; n < 2; n++)
                {
                    if (i + m < height && i + m >= 0 && k + n < width && k + n >= 0)
                    {
                        GxB += copy[i + m][k + n].rgbtBlue * factorsX[index];
                        GyB += copy[i + m][k + n].rgbtBlue * factorsY[index];

                        GxR += copy[i + m][k + n].rgbtRed * factorsX[index];
                        GyR += copy[i + m][k + n].rgbtRed * factorsY[index];

                        GxG += copy[i + m][k + n].rgbtGreen * factorsX[index];
                        GyG += copy[i + m][k + n].rgbtGreen * factorsY[index];

                    }
                    index++;
                }
            }

            int red = round(sqrt(GxR * GxR + GyR * GyR));
            int blue = round(sqrt(GxB * GxB + GyB * GyB));
            int green = round(sqrt(GxG * GxG + GyG * GyG));

            if (red > 255)
            {
                red = 255;
            }

            if (blue > 255)
            {
                blue = 255;
            }

            if (green > 255)
            {
                green = 255;
            }

            image[i][k].rgbtRed = red;
            image[i][k].rgbtBlue = blue;
            image[i][k].rgbtGreen = green;
        }
    }
}

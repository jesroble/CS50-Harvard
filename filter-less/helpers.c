#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int medium = 0;

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            medium = round((float)(image[h][w].rgbtRed + image[h][w].rgbtBlue + image[h][w].rgbtGreen) / 3);
            image[h][w].rgbtRed = image[h][w].rgbtBlue = image[h][w].rgbtGreen = medium;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            int sepiaRed = round(.393 * image[h][w].rgbtRed + .769 * image[h][w].rgbtGreen + .189 * image[h][w].rgbtBlue);
            int sepiaGreen = round(.349 * image[h][w].rgbtRed + .686 * image[h][w].rgbtGreen + .168 * image[h][w].rgbtBlue);
            int sepiaBlue = round(.272 * image[h][w].rgbtRed + .534 * image[h][w].rgbtGreen + .131 * image[h][w].rgbtBlue);

            image[h][w].rgbtRed = (sepiaRed > 255) ? 255 : sepiaRed;
            image[h][w].rgbtGreen = (sepiaGreen > 255) ? 255 : sepiaGreen;
            image[h][w].rgbtBlue = (sepiaBlue > 255) ? 255 : sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
   for (int h = 0; h < height; h++)
    {
        // Iterate over each row of the image
        for (int w = 0; w < width / 2; w++)
        {
            // Calculate the position of the mirrowed pixel
            int mirrored_w = width - 1 - w;

            // Swap the pixel´s position
            RGBTRIPLE temp = image[h][w];
            image[h][w] = image[h][mirrored_w];
            image[h][mirrored_w] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            float newred = 0;
            float newgreen = 0;
            float newblue = 0;
            float medium = 0;

            for (int i = -1; i < 2; i++)
            {
                for (int j = -1; j < 2; j++)
                {
                    if (h + i < 0 || h + i > height - 1)
                        continue;
                    if (w + j < 0 || w + j > width - 1)
                        continue;
                    newred += image[h + i][w + j].rgbtRed;
                    newgreen += image[h + i][w + j].rgbtGreen;
                    newblue += image[h + i][w + j].rgbtBlue;
                    medium++;
                }
            }
            temp[h][w].rgbtRed = round(newred / medium);
            temp[h][w].rgbtGreen = round(newgreen / medium);
            temp[h][w].rgbtBlue = round(newblue / medium);
        }
    }

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            image[h][w].rgbtRed = temp[h][w].rgbtRed;
            image[h][w].rgbtGreen = temp[h][w].rgbtGreen;
            image[h][w].rgbtBlue =  temp[h][w].rgbtBlue;
        }
    }
    return;
}

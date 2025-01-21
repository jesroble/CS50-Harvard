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
    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            float gxred = 0;
            float gxgreen = 0;
            float gxblue = 0;
            float gyred = 0;
            float gygreen = 0;
            float gyblue = 0;
            float average = 0;

            for (int i = -1; i < 2; i++)
            {
                for (int j = -1; j < 2; j++)
                {
                    if (h + i < 0 || h + i > height - 1)
                        continue;
                    if (w + j < 0 || w + j > width - 1)
                        continue;
                    gxred += image[h + i][w + j].rgbtRed * gx[h + i][w + j];
                    gxgreen += image[h + i][w + j].rgbtGreen * gx[h + i][w + j];
                    gxblue += image[h + i][w + j].rgbtBlue * gx[h + i][w + j];
                    gyred += image[h + i][w + j].rgbtRed * gx[h + i][w + j];
                    gygreen += image[h + i][w + j].rgbtGreen * gx[h + i][w + j];
                    gxblue += image[h + i][w + j].rgbtBlue * gx[h + i][w + j];
                    average++;
                }
                temp[h][w].rgbtRed = round(sqrt(gxred * gxred + gyred * gyred) > 255) ? 255 : temp[h][w].rgbtRed;
                temp[h][w].rgbtGreen = round(sqrt(gxgreen * gxgreen + gygreen * gygreen) > 255) ? 255 : temp[h][w].rgbtGreen;
                temp[h][w].rgbtBlue = round(sqrt(gxblue * gxblue + gyblue * gyblue) > 255) ? 255 : temp[h][w].rgbtBlue;
            }
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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            float gxred = 0;
            float gxgreen = 0;
            float gxblue = 0;
            float gyred = 0;
            float gygreen = 0;
            float gyblue = 0;
            float average = 0;

            for (int i = -1; i < 2; i++)
            {
                for (int j = -1; j < 2; j++)
                {
                    if (h + i < 0 || h + i > height - 1)
                        continue;
                    if (w + j < 0 || w + j > width - 1)
                        continue;
                    gxred += image[h + i][w + j].rgbtRed * gx[h + i][w + j];
                    gxgreen += image[h + i][w + j].rgbtGreen * gx[h + i][w + j];
                    gxblue += image[h + i][w + j].rgbtBlue * gx[h + i][w + j];
                    gyred += image[h + i][w + j].rgbtRed * gx[h + i][w + j];
                    gygreen += image[h + i][w + j].rgbtGreen * gx[h + i][w + j];
                    gxblue += image[h + i][w + j].rgbtBlue * gx[h + i][w + j];
                    average++;
                }
                temp[h][w].rgbtRed = round(sqrt(gxred * gxred + gyred * gyred) > 255) ? 255 : temp[h][w].rgbtRed;
                temp[h][w].rgbtGreen = round(sqrt(gxgreen * gxgreen + gygreen * gygreen) > 255) ? 255 : temp[h][w].rgbtGreen;
                temp[h][w].rgbtBlue = round(sqrt(gxblue * gxblue + gyblue * gyblue) > 255) ? 255 : temp[h][w].rgbtBlue;
            }
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

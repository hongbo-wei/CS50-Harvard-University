#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float blue;
    float green;
    float red;
    int color_average;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            blue = image[i][j].rgbtBlue;
            green = image[i][j].rgbtGreen;
            red = image[i][j].rgbtRed;
            // Calculate the average color of each pixel
            color_average = round((blue + green + red) / 3);
            // Round the number to nearest integer
            // Set grayscale
            image[i][j].rgbtBlue = image[i][j].rgbtGreen = image[i][j].rgbtRed = color_average;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE pixel_holder;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // Set place holders for the color of each pixel
            pixel_holder = image[i][j];

            // Swape pixels
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = pixel_holder;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    float total_blue, total_green, total_red;
    int pixel_count;

    RGBTRIPLE image_copy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            total_blue = total_green = total_red = pixel_count = 0;
            for (int h = i - 1; (h >= i - 1) && (h <= i + 1) && (h < height); h++)
            {
                if (h < 0)
                {
                    h = 0;
                }
                for (int w = j - 1; (w >= j - 1) && (w <= j + 1) && (w < width); w++)
                {
                    if (w < 0)
                    {
                        w = 0;
                    }
                    // Calculate the average color of 3x3 box and change the one in the center.
                    total_blue += image[h][w].rgbtBlue;
                    total_green += image[h][w].rgbtGreen;
                    total_red += image[h][w].rgbtRed;
                    pixel_count++;
                }

            }
            // Place the changed pixel in a copy of the image
            image_copy[i][j].rgbtBlue = round(total_blue / pixel_count);
            image_copy[i][j].rgbtGreen = round(total_green / pixel_count);
            image_copy[i][j].rgbtRed = round(total_red / pixel_count);
        }
    }
    // Put the image back to the input image
    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = image_copy[i][j];
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int x_blue, x_green, x_red;
    int y_blue, y_green, y_red;
    int Gx_blue, Gx_green, Gx_red, Gy_blue, Gy_green, Gy_red;
    int sobel_blue, sobel_green, sobel_red;
    RGBTRIPLE image_copy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Initialize RGB values for Gx and Gy
            Gx_blue = Gx_green = Gx_red = Gy_blue = Gy_green = Gy_red = 0;
            for (int h = i - 1; (h >= i - 1) && (h <= i + 1) && (h < height); h++)
            {
                if (h < 0)
                {
                    h = 0;
                }
                for (int w = j - 1; (w >= j - 1) && (w <= j + 1) && (w < width); w++)
                {
                    if (w < 0)
                    {
                        w = 0;
                    }

                    // !!! Caculation for Gx !!!
                    // For the first pixels of the first and third row
                    if (((h == i - 1) || (h == i + 1)) && (w == j - 1))
                    {
                        x_blue = image[h][w].rgbtBlue * -1;
                        x_green = image[h][w].rgbtGreen * -1;
                        x_red = image[h][w].rgbtRed * -1;
                    }
                    // For the third pixels of the first and third row
                    else if (((h == i - 1) || (h == i + 1)) && (w == j + 1))
                    {
                        x_blue = image[h][w].rgbtBlue;
                        x_green = image[h][w].rgbtGreen;
                        x_red = image[h][w].rgbtRed;
                    }
                    // For the middle column
                    else if (w == j)
                    {
                        x_blue = x_green = x_red = 0;
                    }
                    // For the first pixel of the second row
                    else if ((h == i) && (w == j - 1))
                    {
                        x_blue = image[h][w].rgbtBlue * -2;
                        x_green = image[h][w].rgbtGreen * -2;
                        x_red = image[h][w].rgbtRed * -2;
                    }
                    // For the third pixel of the second row
                    else if ((h == i) && (w == j + 1))
                    {
                        x_blue = image[h][w].rgbtBlue * 2;
                        x_green = image[h][w].rgbtGreen * 2;
                        x_red = image[h][w].rgbtRed * 2;
                    }
                    // Calculate the average color of 3x3 box and change the one in the center.
                    Gx_blue += x_blue;
                    Gx_green += x_green;
                    Gx_red += x_red;

                    // !!! Calculation for Gy !!!
                    // For the first and third pixels of the first row
                    if ((h == i - 1) && ((w == j - 1) || (w == j + 1)))
                    {
                        y_blue = image[h][w].rgbtBlue * -1;
                        y_green = image[h][w].rgbtGreen * -1;
                        y_red = image[h][w].rgbtRed * -1;
                    }
                    // For the first and third pixels of the third row
                    else if ((h == i + 1) && ((w == j - 1) || (w == j + 1)))
                    {
                        y_blue = image[h][w].rgbtBlue;
                        y_green = image[h][w].rgbtGreen;
                        y_red = image[h][w].rgbtRed;
                    }
                    // For the middle row
                    else if (h == i)
                    {
                        y_blue = y_green = y_red = 0;
                    }
                    // For the second pixel of the first row
                    else if ((h == i - 1) && (w == j))
                    {
                        y_blue = image[h][w].rgbtBlue * -2;
                        y_green = image[h][w].rgbtGreen * -2;
                        y_red = image[h][w].rgbtRed * -2;
                    }
                    // For the second pixel of the third row
                    else if ((h == i + 1) && (w == j))
                    {
                        y_blue = image[h][w].rgbtBlue * 2;
                        y_green = image[h][w].rgbtGreen * 2;
                        y_red = image[h][w].rgbtRed * 2;
                    }
                    // Calculate the average color of 3x3 box and change the one in the center.
                    Gy_blue += y_blue;
                    Gy_green += y_green;
                    Gy_red += y_red;
                }
            }
            // Calculate the final result according to Sobel Filter Algorithm
            sobel_blue = round(sqrt(Gx_blue * Gx_blue + Gy_blue * Gy_blue));
            sobel_green = round(sqrt(Gx_green * Gx_green + Gy_green * Gy_green));
            sobel_red = round(sqrt(Gx_red * Gx_red + Gy_red * Gy_red));
            // Set the maximum for the final value
            if (sobel_blue > 255)
            {
                sobel_blue = 255;
            }
            if (sobel_green > 255)
            {
                sobel_green = 255;
            }
            if (sobel_red > 255)
            {
                sobel_red = 255;
            }
            image_copy[i][j].rgbtBlue = sobel_blue;
            image_copy[i][j].rgbtGreen = sobel_green;
            image_copy[i][j].rgbtRed = sobel_red;
        }
    }
    // Put the image back to the input image
    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = image_copy[i][j];
        }
    }
    return;
}

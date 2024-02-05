#include "helpers.h"

void colorize(int height, int width, RGBTRIPLE image[height][width])
{
    // Change all black pixels to a color of your choosing
    // For each row
    for (int i = 0; i < height; i++)
    {
        // For each column
        for (int j = 0; j < width; j++)
        {
            // If the color of the pixel is black, change it to my color.
            if ((image[i][j].rgbtRed == 0) && (image[i][j].rgbtGreen == 0) && (image[i][j].rgbtBlue == 0))
            {
                image[i][j].rgbtRed = 0;
                image[i][j].rgbtGreen = 102;
                image[i][j].rgbtBlue = 255;
            }
        }
    }
}

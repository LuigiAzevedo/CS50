#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            // Divide every color and round the number to the nearest int
            int average_color = round((image[h][w].rgbtBlue + image[h][w].rgbtGreen + image[h][w].rgbtRed) / 3.0);

            // Insert the same value in all color to produce the correct grey scale
            image[h][w].rgbtBlue = average_color;
            image[h][w].rgbtGreen = average_color;
            image[h][w].rgbtRed = average_color;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    // Loops once for each pixel
    for (int h = 0; h < height; h++)
    {
        if (width % 2 == 0)
        {
            for (int w = 0; w < width / 2; w++)
            {
                temp[h][w] = image[h][w];
                image[h][w] = image[h][width - (w + 1)];
                image[h][width - (w + 1)] = temp[h][w];
            }
        }
        else
        {
            for (int w = 0; w < (width - 1) / 2; w++)
            {
                temp[h][w] = image[h][w];
                image[h][w] = image[h][width - (w + 1)];
                image[h][width - (w + 1)] = temp[h][w];
            }

        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    // Loops once for each pixel
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            float blue_total = 0;
            float green_total = 0;
            float red_total = 0;
            float adjacent_pixels = 0;

            // Loops once for each adjacent pixel in a 3x3 grid
            for (int i = -1; i < 2; i++)
            {
                for (int j = -1; j < 2; j++)
                {
                    if (i + h >= 0 && i + h <= height - 1 && j + w >= 0 && j + w <= width - 1)
                    {
                        blue_total += image[h + i][w + j].rgbtBlue;
                        green_total += image[h + i][w + j].rgbtGreen;
                        red_total += image[h + i][w + j].rgbtRed;
                        adjacent_pixels++;
                    }
                }
            }

            blue_total = round(blue_total / adjacent_pixels);
            green_total = round(green_total / adjacent_pixels);
            red_total = round(red_total / adjacent_pixels);

            // Store blurred pixel value in a temporary RGB struct
            temp[h][w].rgbtBlue = blue_total;
            temp[h][w].rgbtGreen = green_total;
            temp[h][w].rgbtRed = red_total;
        }
    }

    // Insert each blurred pixel value inside each pixel of the image
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            image[h][w].rgbtBlue = temp[h][w].rgbtBlue;
            image[h][w].rgbtGreen = temp[h][w].rgbtGreen;
            image[h][w].rgbtRed = temp[h][w].rgbtRed;
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{

    RGBTRIPLE temp[height][width];

    // kernels values for each position pixel in a 3x3 grid
    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    // Loops once for each pixel
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {

            int gx_blue = 0;
            int gx_green = 0;
            int gx_red = 0;

            int gy_blue = 0;
            int gy_green = 0;
            int gy_red = 0;

            // Loops for each adjacent pixel in a 3x3 grid
            for (int i = -1; i < 2; i++)
            {
                for (int j = -1; j < 2; j++)
                {
                    // Checks if the pixel exists inside the image
                    if (i + h < 0 || i + h > height - 1)
                    {
                        continue;
                    }

                    if (j + w < 0 || j + w > width - 1)
                    {
                        continue;
                    }

                    gx_blue += image[i + h][j + w].rgbtBlue * gx[i + 1][j + 1];
                    gx_green += image[i + h][j + w].rgbtGreen * gx[i + 1][j + 1];
                    gx_red += image[i + h][j + w].rgbtRed * gx[i + 1][j + 1];

                    gy_blue += image[i + h][j + w].rgbtBlue * gy[i + 1][j + 1];
                    gy_green += image[i + h][j + w].rgbtGreen * gy[i + 1][j + 1];
                    gy_red += image[i + h][j + w].rgbtRed * gy[i + 1][j + 1];
                }
            }

            // Each color receives the rounded value of the square root of Gx^2 + Gy^2
            int blue = round(sqrt(gx_blue * gx_blue + gy_blue * gy_blue));
            int green = round(sqrt(gx_green * gx_green + gy_green * gy_green));
            int red = round(sqrt(gx_red * gx_red + gy_red * gy_red));

            // If any color has a value higher than 255, the value is set to the maximum amount (255)
            if (blue > 255)
            {
                blue = 255;
            }

            if (green > 255)
            {
                green = 255;
            }

            if (red > 255)
            {
                red = 255;
            }


            // Stores the color value in a temporary RGBTRIPLE struct
            temp[h][w].rgbtBlue = blue;
            temp[h][w].rgbtGreen = green;
            temp[h][w].rgbtRed = red;
        }
    }

    // For each pixel in the image, insert the value from the temp RGBTRIPLE into the image
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            image[h][w].rgbtBlue = temp[h][w].rgbtBlue;
            image[h][w].rgbtGreen = temp[h][w].rgbtGreen;
            image[h][w].rgbtRed = temp[h][w].rgbtRed;
        }
    }
    return;
}
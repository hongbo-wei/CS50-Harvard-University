#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <cs50.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Check if the action is proper
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // Check if the raw file can be open
    FILE *raw_file = fopen(argv[1], "r");
    if (raw_file == NULL)
    {
        printf("Unable to open it.\n");
        return 1;
    }

    // Initialize blocksize to read
    int block_size = 512;

    // Declare a variable to store the 512-byte data of image
    BYTE buffer[block_size];

    // Initialize image count for output file
    int image_count = 0;

    // Create a char pointer to store the filename of recover imges
    char *filename = malloc(8 * sizeof(char));

    FILE *img = NULL;
    bool image_found = false;

    while (fread(buffer, sizeof(char), block_size, raw_file) == block_size)
    {
        // Check if the file is a JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8
            && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (image_count == 0)
            {
                image_found = true;
                // Prepare filename to store the recovered image
                sprintf(filename, "%03i.jpg", image_count);

                // Write the content to the image file
                img = fopen(filename, "w");
                fwrite(buffer, sizeof(char), block_size, img);

                // Update the count of image
                image_count ++;
            }
            else
            {
                fclose(img);
                sprintf(filename, "%03i.jpg", image_count);
                img = fopen(filename, "w");
                fwrite(buffer, sizeof(char), block_size, img);
                image_count++;
            }
        }
        else if (image_found)
        {
            fwrite(buffer, sizeof(char), block_size, img);
        }

    }
    // Close file pointers
    fclose(raw_file);
    fclose(img);

    // Free allocated memory
    free(filename);

    return 0;
}
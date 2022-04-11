#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    // Open memory card file
    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // buffer jpeg array
    uint8_t buffer[512];

    // file name counter
    int counter = 0;

    // file name
    char photo[8];

    // Create filename xxx.jpg
    sprintf(photo, "%03i.jpg", counter);

    // create a new jpg file and open to write
    FILE *img = fopen(photo, "w");

    // repeat for each 512 bytes inside the memory card
    while (fread(buffer, 1, 512, card) == 512)
    {
        // Check if the buffer[] is a jpg
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // write the buffer inside the first image in the memory card
            if (counter == 0)
            {
                fwrite(buffer, 1, 512, img);
            }
            // if new jpg is found, close the last one and write the content inside the buffer in the new image
            else
            {
                fclose(img);
                sprintf(photo, "%03i.jpg", counter);
                img = fopen(photo, "w");
                fwrite(buffer, 1, 512, img);
            }
            counter++;
        }
        // If the image is already opened, keep writing the buffer value
        else if (counter > 0)
        {
            fwrite(buffer, 1, 512, img);
        }
    }
    // close the memory card
    fclose(card);
}
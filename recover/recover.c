#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("usage: ./recover image\n");
        return (1);
    }

    FILE *card = fopen(argv[1], "r");

    uint8_t buffer[512];
    int i = 0;
    FILE *output = NULL;
    char name[8];

    while(fread(buffer, 1, 512, card) == 512)
    {
        if(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (output != NULL)
                fclose(output);
            sprintf(name, "%03i.jpg", i);
            output = fopen(name, "w");
            i++;
        }
        if(output != 0)
            fwrite(buffer, 1, 512, output);
    }
    fclose(card);
    fclose(output);
    return (0);
}

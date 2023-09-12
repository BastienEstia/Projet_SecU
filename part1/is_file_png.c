#include <stdio.h>
#include <stdlib.h>

typedef char BYTE;

int isPng(FILE *fptr)
{
    BYTE key[] = {0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A};
    int keyLen = 8;
    BYTE curByte;
    for (int i = 0; i < keyLen; i++)
    {
        curByte = fgetc(fptr);
        if (key[i] != curByte)
        {
            // remise du curseur de lecture en position initiale
            // si éventuel usage ultérieur
            fseek(fptr, -(i + 1), SEEK_CUR);
            return 0;
        }
    }
    fseek(fptr, -keyLen, SEEK_CUR);
    return 1;
}

int main() {
    FILE * pfile;

    pfile = fopen("files/poke.png", "rb");
    printf("%s\n", isPng(pfile) ? "PNG file" : "Not png file");
    fclose(pfile);

    pfile = fopen("files/lupo.png", "rb");
    printf("%s\n", isPng(pfile) ? "PNG file" : "Not png file");
    fclose(pfile);



    return 0;
}
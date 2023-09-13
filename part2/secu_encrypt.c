#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 32
#define ASCII_MINUSCULE_OFFSET 97

typedef enum MODE {
    ENC,
    DEC
} MODE;

typedef int myType[200][2];

void keyToPermutes(char *key, myType *permArrayPtr){
    const int keyLen = strlen(key);
    const int keyMidLen = keyLen/2;

    // printf("Keylen: %d\nKeymidlen: %d\n", keyLen, keyMidLen);

    int startI = 0, endI = 0;

    // printf("Premieres partie de la cle:\n");
    for (int i=0; i<keyMidLen;i++){
        startI += key[i] - ASCII_MINUSCULE_OFFSET + 1;
        // printf("%d", key[i] - ASCII_MINUSCULE_OFFSET + 1);
    }
    puts("");

    // printf("Deuxieme partie de la cle:\n");
    for (int i=0; i<keyMidLen;i++){
        endI += key[i] + keyMidLen - ASCII_MINUSCULE_OFFSET + 1;
        // printf("%d", key[i + keyMidLen] - ASCII_MINUSCULE_OFFSET + 1);
    }
    puts("");

    // printf("startI: %d\nendI: %d\n", startI, endI);

    (*permArrayPtr)[0][0] = startI;
    (*permArrayPtr)[0][1] = endI;

    // printf("Col: 0 | Lig: 0 => %d\n", (*permArrayPtr)[0][0]);
    // printf("Col: 0 | Lig: 1 => %d\n", (*permArrayPtr)[0][1]);

    for (int i=1; i<keyLen; i++){
        (*permArrayPtr)[i][0] = (*permArrayPtr)[0][0] * (i+1);
        // printf("Col: %d | Lig: 0 => %d\n",i, (*permArrayPtr)[i][0]);
        (*permArrayPtr)[i][1] = (*permArrayPtr)[0][1] * (i+1);
        // printf("Col: %d | Lig: 1 => %d\n",i, (*permArrayPtr)[i][1]);
    }

}

int secu_encrypt(int mode, char *key, char *filename){
    const int keyLen = strlen(key);
    
    int permArray[keyLen][2];

    myType *permArrayPtr;
    permArrayPtr= &permArray;

    keyToPermutes(key, permArrayPtr);

    printf("permArray[keyLen-1][1]=%d\n", permArray[keyLen-1][1]);

    char bytes[permArray[keyLen-1][1]];
    int reader = 0;
    
    FILE *fptr = fopen(filename, "r");
    for (int i = 0; i < permArray[keyLen-1][1]; i++){
    
        reader = fgetc(fptr);
        if (reader != EOF)
            bytes[i] = reader;
        else
            break;
        printf("Bytes[%d] => %X\n", i, bytes[i]);
    }

    switch (mode){
        case ENC:
            for (int i = 0; i < keyLen; i++){
                int pI = permArray[i][0];
                int pF = permArray[i][1];

                printf("bytes[%d] <=> bytes[%d] | %X <=> %X\n",pI, pF, bytes[pI], bytes[pF]);

                char byteTemp = bytes[pI];

                bytes[pI] = bytes[pF];
                bytes[pF] = byteTemp;

                
                printf("Nouveaux bytes: bytes[%d]: %X | bytes[%d]: %X\n", pI, bytes[pI], pF, bytes[pF]);

            }
            rewind(fptr);
            fwrite(bytes, 1,permArray[keyLen-1][1], fptr);

            break;
        case DEC:
            for (int i = 0; i < keyLen; i++){
                int pI = permArray[i][1];
                int pF = permArray[i][0];

                printf("bytes[%d] <=> bytes[%d] | %X <=> %X\n",pI, pF, bytes[pI], bytes[pF]);

                char byteTemp = bytes[pI];

                bytes[pI] = bytes[pF];
                bytes[pF] = byteTemp;

                
                printf("Nouveaux bytes: bytes[%d]: %X | bytes[%d]: %X\n", pI, bytes[pI], pF, bytes[pF]);

            }
            rewind(fptr);
            fwrite(bytes, 1,permArray[keyLen-1][1], fptr);

            break;
        default:
            break;
    }

    fclose(fptr);

}

int main(int argc, char **argv){

    int opt, mode;
    char key[30], filename[30];
    //char file[30];

    while((opt = getopt(argc, argv, ":edk:f:"))!=-1){
        switch (opt)
        {
        case 'e':
            mode = ENC;
            break;
        case 'd':
            mode = DEC;
            break;
        case 'k':
            strcpy(key, optarg);
            break;
        case 'f':
            strcpy(filename, optarg);
            break;
        }
    }

    printf("mode: %d\nkey: %s\nfilename: %s\n", mode, key, filename);

    //keyToPermutes(key);

    // mode = ENC;
    // strcpy(key, "abcde");
    // strcpy(filename, "poke.png");

    secu_encrypt(mode, key, filename);

    char bytes[40];
    int reader = 0;
    FILE *fptr = fopen(filename, "r");
    for (int i = 0; i < 40; i++){
    
        reader = fgetc(fptr);
        if (reader != EOF)
            bytes[i] = reader;
        else
            break;
    }

    for (int i = 0; i < 40; i++)
    {
        printf("Bytes[%d] => %X\n", i, bytes[i]);
    }
    fclose(fptr);

    return 0;
}
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

#define SEED time(NULL)
#define ASCII_OFFSET 33
#define ASCII_CHIFFRE_OFFSET 48
#define ASCII_CHIFFRE_MAX 58
#define ASCII_MAJUSCULE_OFFSET 65
#define ASCII_MAJUSCULE_MAX 91
#define ASCII_MINUSCULE_OFFSET 97
#define ASCII_MINUSCULE_MAX 123

typedef enum CAROPTION {
    C,
    N,
    B,
    H
} CAROPTION;

int secu_generator(int carOption, int nbCar, char filename[]){

    srand(SEED);

    int randNum;

    int carFlag = 0, numFlag = 0;

    char key[nbCar];

    int intKey[nbCar];

    FILE *fptr;

    printf("option : %d\nnbCar = %d\n", carOption, nbCar);

    puts("Cle genere : ");

    for (int i=0; i<nbCar; i++){
        switch (carOption){
            case C:
                randNum = (rand()%26) + ASCII_MINUSCULE_OFFSET;
                key[i] = (char)randNum;
                (i!=nbCar-1)? printf("%c", key[i]) : printf("%c\n", key[i]);
                break;
            case N:
                randNum = (rand()%10) + ASCII_CHIFFRE_OFFSET;
                key[i] = (char)randNum;
                (i!=nbCar-1)? printf("%d", key[i]) : printf("%d\n", key[i]);
                break;
            case B:
                randNum = (rand()%256);
                intKey[i] = randNum;
                (i!=nbCar-1)? printf("0x%X ", intKey[i]) : printf("0x%X\n", intKey[i]);
                break;
            case H:
                randNum = (rand()%16);
                intKey[i] = randNum;
                (i!=nbCar-1)? printf("0x%X ", intKey[i]) : printf("0x%X\n", intKey[i]);
                break;
        }
    }
    
    if (filename[0] != '\0'){
        printf("Ecriture dans le fichier %s\n", filename);
        fptr = fopen(filename, "a+");
        if (carOption>1){
            for (int i=0; i<nbCar; i++)
                (i!=nbCar-1)? fprintf(fptr, "0x%X ", intKey[i]) : fprintf(fptr, "0x%X", intKey[i]);
        }
        else{ 
            fprintf(fptr, key);
        }
        fclose(fptr);
    }

    return 0;
}

int main(int argc, char **argv){

    int opt;

    int carOption, nbCar;
    char filename[30] = {'\0'};

    while ((opt = getopt(argc, argv, ":c:n:b:h:f:"))!=-1){
        switch(opt){
            case 'c':
                carOption = C;
                nbCar = atoi(optarg);
                break;
            case 'n':
                carOption = N;
                nbCar = atoi(optarg);
                break;
            case 'b':
                carOption = B;
                nbCar = atoi(optarg);
                break;
            case 'h':
                carOption = H;
                nbCar = atoi(optarg);
                break;
            case 'f':
                strcpy(filename, optarg);
                break;
        }
    }

    secu_generator(carOption, nbCar, filename);

    return 0;
}
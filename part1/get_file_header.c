#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROR -1
typedef unsigned char byte;

typedef enum FILE_TYPE {
    FILE_TYPE_JPG,
    FILE_TYPE_PNG,
    FILE_TYPE_EXE,
    FILE_TYPE_PDF,
    FILE_TYPE_DOC,
    FILE_TYPE_UNKNOW
} FILE_TYPE;

typedef enum CEASER_DIRECTION {
    CEASER_DIRECTION_RIGHT,
    CEASER_DIRECTION_LEFT,
} CEASER_DIRECTION;


#define SIGNATURE_FILE_MAX_BUFFER_SIZE 32
#define SIGNATURE_FILE_MAX_BUFFER_SIZE_IGNORED_BYTE 16

typedef struct file_signature_t
{
    char *name;
    FILE_TYPE fileType;
    int size;
    int nbBytesIgnored;
    char bytes[SIGNATURE_FILE_MAX_BUFFER_SIZE];
    char ignored_bytes[SIGNATURE_FILE_MAX_BUFFER_SIZE_IGNORED_BYTE];
} file_signature_t;


#define BYTE_IGNORE 0xff /// just used for the user comprehension

const file_signature_t file_signature[] = {
    {"JPG", FILE_TYPE_JPG, 4, 0, {0xFF ,0xD8 ,0xFF ,0xDB}},
    {"JPG", FILE_TYPE_JPG, 12, 0, {0xff ,0xd8 ,0xff ,0xe0, 0x00, 0x10, 0x4a, 0x46, 0x49, 0x46, 0x00, 0x01}},
    {"JPG", FILE_TYPE_JPG, 4, 0, {0xFF ,0xD8 ,0xFF ,0xEE}},
    {"JPG", FILE_TYPE_JPG, 4, 2, {0xFF ,0xD8 ,0xFF ,0xE1 ,BYTE_IGNORE ,BYTE_IGNORE ,0x45 ,0x78 ,0x69 ,0x66 ,0x00 ,0x00},{4, 5}},
    {"PNG", FILE_TYPE_PNG, 8, 0, {0x89 ,0x50 ,0x4E ,0x47 ,0x0D ,0x0A ,0x1A ,0x0A}},
    {"EXE", FILE_TYPE_EXE, 2, 0, {0x4D, 0x5A}},
    {"PDF", FILE_TYPE_PDF, 5, 0, {0x25 ,0x50 ,0x44 ,0x46 ,0x2D}},
    {"DOC", FILE_TYPE_DOC, 8, 0, {0xD0 ,0xCF ,0x11 ,0xE0 ,0xA1 ,0xB1 ,0x1A ,0xE1}},
};



/**
Entrée: fichier binaire
Sortie: format de fichier trouvé (parmi ceux recherchés)
On se limitera à rechercher les formats de fichier suivants: jpg, png, exe, pdf, doc
Lien: https://en.wikipedia.org/wiki/List_of_file_signatures
*/
int get_file_header(char *filename)
{
    FILE* p_file = fopen(filename, "rb+");

    int ignore_byte=0;
    int reader=0;
    char read_file_signature[SIGNATURE_FILE_MAX_BUFFER_SIZE]={0};

    for (int i=0;i<SIGNATURE_FILE_MAX_BUFFER_SIZE;i++)
    {
        reader=fgetc(p_file);
        if (reader!=EOF)
            read_file_signature[i]=reader;
        else
            break;
    }


    if (!p_file)
    {
        printf("Un probleme est survenu avec le fichier %s.\n",filename);
        return 1;
    }

    for (int i=0;i<sizeof(file_signature)/sizeof(file_signature_t);i++) /// boucle sur les signatures qu'on a en memoire
    {
        for (int a=0;a<file_signature[i].size;a++)
        {
            ignore_byte=0;
            for (int b=0;b<file_signature[i].nbBytesIgnored;b++) // check si on ignore cet id de byte
                if (file_signature[i].ignored_bytes[b]==a)
                    ignore_byte=1;
            if (!ignore_byte) // si byte pas ignoré
            {
                if (file_signature[i].bytes[a]!=read_file_signature[a]) // check si diff
                {
                    break; // on break pour check la signature suivante
                }
                else if (a == file_signature[i].size-1) // si fin de boucle + pas de diff
                {
                    // sur une vrai lib on enleverai ce print et on le mettrai plutot dans le main,
                    printf("Fichier type %s reconnu\n", file_signature[i].name);
                    return file_signature[i].fileType;
                }
            }
        }
    }

    fclose(p_file);


    return ERROR;
}
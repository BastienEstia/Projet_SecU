#include <stdio.h>

int is_forbidden(char c)
{
    char FORBIDDEN_CHAR[] = "\n\t";
    for (int i = 0; i < sizeof(FORBIDDEN_CHAR) / sizeof(char); i++)
    {
        if (c == FORBIDDEN_CHAR[i])
        {
            return 1;
        }
    }
    return 0;
}

int html_minifier(char *filename, char *filename_out)
{
    FILE *p_file = fopen(filename, "r+");
    FILE *p_file_output = fopen(filename_out, "w+");

    char current_char;
    int ignore_char = 0;

    if (!p_file)
    {
        printf("Un probleme est survenu avec le fichier %s.\n", filename);
        return 1;
    }

    if (!p_file_output)
    {
        printf("Un probleme est survenu avec le fichier de sortie %s.\n", filename_out);
        return 1;
    }

    while ((current_char = fgetc(p_file)) != EOF)
    {
        ignore_char = is_forbidden(current_char);

        if (current_char == '\n') // permet d'ignore tout les caractere interdit + L'ESPACE
                                  // à partir d'un saut de ligne
        {
            do
            {
                current_char = fgetc(p_file);
            } while (current_char == ' ' || is_forbidden(current_char));
            ignore_char = 0;
        }

        if (!ignore_char)
            fputc(current_char, p_file_output);
    }

    fclose(p_file);

    return 0;
}

int main()
{
    if (!html_minifier("files/projet.html","out.html"))
    {
        printf("Fichier de sortie ecris avec succes (out.html).\n");
    }
    return 0;
}

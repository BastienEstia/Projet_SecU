#include <stdio.h>
#include <string.h>

char* cypher_rotate(char str[], int rotSens, int pas){

    char *Sptr = &str[0];

    printf("string: %s\nrotSens: %d\npas: %d\n", str, rotSens, pas);

    for (int i=0; i<strlen(str); i++){

        printf("(%d)char: %c\n", i, str[i]);

        if (str[i]>='a' && str[i]<='z'){

            puts("lettre minuscule trouve !");

            if (rotSens==0){
                char c;
                c = str[i];
                printf("lettre a decale: %c\n", str[i]);
                str[i]+= sizeof(char) * pas;
                printf("%c => %c\n", c, str[i]);

                if (str[i]>'z'){
                    c = str[i];
                    int diff = str[i] - 'z';
                    str[i] = '`' + diff;
                    printf("%c => %c\n", c, str[i]);
                }
            }
            else{
                char c;
                c = str[i];
                printf("lettre a decale: %c\n", str[i]);
                //*(Sptr - i) = sizeof(char)*pas; 
                str[i]-= sizeof(char)*pas;
                printf("%c => %c\n", c, str[i]);

                if (str[i]<'a'){
                    c = str[i];
                    int diff = 'a' - str[i];
                    str[i] = '{' - diff;
                    printf("%c => %c\n", c, str[i]);
                }
            }
        }
    }

    return str;
}

int main(int argc, char **argv){

    char str[] = "51&$Ia0Gz*";
    char *ptr;
    ptr = cypher_rotate(str, 1, 3); // Attention il faut donner la chaine à la fonction via un tableau
                                    // cypher_rotate("51&$Ia0Gv*", 0, 1) ==> segmentation fault !
    
    printf("cypher_rotate(\"%s\", %d, %d) => %s\n", "51&$Ia0Gv*", 1, 1, str);

    return 0;
}
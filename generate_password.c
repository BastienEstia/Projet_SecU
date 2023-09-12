#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

char* generate_password(int len, int charSpe){

    static char password[30];
    int i;
    char *pwd = password;
    srand(time(NULL));

    for (i=0; i<len; i++){

        int randNum;
        //(charSpe == 1)? randNum = (4 * (rand()/(RAND_MAX + 1.0))):randNum = (3 * (rand()/(RAND_MAX + 1.0))); //fonctionne pas ?

        if (charSpe==1){
            randNum = (4 * (rand()/(RAND_MAX + 1.0)));
        }
        else{
            randNum = (3 * (rand()/(RAND_MAX + 1.0)));
        }

        //printf("randNum: %d\n", randNum); //debug

        switch(randNum){
            case 0: //minuscule
                *(pwd+i)= (char)(26 * (rand()/(RAND_MAX + 1.0))) + 97;
                break;
            case 1: //MAJUSCULE
                *(pwd+i)= (char)(26 * (rand()/(RAND_MAX + 1.0))) + 65;
                break;
            case 2: //chiffre
                *(pwd+i)= (char)(9 * (rand()/(RAND_MAX + 1.0))) + 48;
                break;
            case 3: //caractere 
                *(pwd+i)= (char)(15 * (rand()/(RAND_MAX + 1.0))) + 33;
        }   

        
    }

    //printf("pwd: %s\n", password); //debug

    return pwd;

}

int main(int argc, char** argv){

    printf("pwd : %s\n", generate_password(10,1));

    return 0;
}
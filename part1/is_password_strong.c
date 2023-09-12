#include <stdio.h>
#include <string.h>

int is_password_strong(char pwd[]){

    int cpt[4] = {0,0,0,0};

    if (strlen(pwd)<10)
        return 0;
    
    for (int i=0; i<strlen(pwd); i++){
        if (pwd[i]>='a' && pwd[i]<='z'){
            cpt[0]++;
        }
        else if (pwd[i]>='A' && pwd[i]<='Z'){
            cpt[1]++;
        }
        else if (pwd[i]>='!' && pwd[i]<='/'){
            cpt[2]++;
        }
        else{
            cpt[3]++;
        }
    }
    for (int i=0; i<4; i++){
        if(cpt[i]==0)
        return 0;
    }
    return 1;
}

int main(){

    printf("%s is_password_strong: %d\n","1l3N+173R5", is_password_strong("1l3N+173R5")); //ok
    printf("%s is_password_strong: %d\n","1l3N173R5", is_password_strong("1l3N173R5")); //sans caracspe
    printf("%s is_password_strong: %d\n","nnnnnlN+R", is_password_strong("nnnnnlN+R")); //sans chiffre
    printf("%s is_password_strong: %d\n","1l3n+173rs", is_password_strong("1l3n+173rs")); //sans maj
    printf("%s is_password_strong: %d\n","1L3N+173R5", is_password_strong("1L3N+173R5")); //sans min

    return 0;
}
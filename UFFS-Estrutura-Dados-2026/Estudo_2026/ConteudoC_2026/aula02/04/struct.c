#include <stdio.h>
#include <string.h>

typedef struct tdate{
    int day, mounth, year;
}date;

typedef struct tfriend
{
    char name  [30];
    char email [30];
    date dbirth;
} friend ;

typedef struct Tteste{
    int a; 
    struct Tteste infinito;
} Tteste; 


void showDate(date d){
    printf(" Dia : %d \n Mês : %d \n Ano: %d", d.day, d.mounth, d.year);
}

void showFriend(friend f,){
    printf(" Nome: %s \n Email : %s \n Aniversario %d / %d /%d",f.name,f.email,f.dbirth.day,f.dbirth.mounth, f.dbirth.year );
}

int main(){
    int n;
    date d;
    d.day = 2;
    d.mounth = 5;
    d.year = 1945;
    showDate(d);
    friend f;
    f.name = strcpy("Rhuan");
    showFriend()

}


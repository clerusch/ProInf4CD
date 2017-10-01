#include<stdio.h>
#include <string.h>


//bool player_one_wins(char[] ){}

char *stati[] = {
        "GEWONNEN\n",
        "VERLOREN\n",
        "UNENTSCHIEDN\n",
        "SCHERE\n",
        "STEIN\n",
        "PAPIER\n"
};

char* p1_vs_p2(char* p1, char* p2){
    if(strcmp(p1, p2) == 0)return "UNENTSCHIEDN\n";
    return stati[0];
}


int main(void){
    char eingabe[] = "PAPIER\n";
    printf("Vergleiche %s mit %s: ergebnis mit strcmp: %d;\n", eingabe, stati[5], strcmp(eingabe, stati[5]));
    return 0;
}

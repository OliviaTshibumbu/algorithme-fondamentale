#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define taille 6
#define win_score 2048
int score =0;

void initplateau (int plateau[taille][taille]){
for( int i=0; i<taille ; i++){
    for(int j=0; j<taille; j++){
        plateau[i][j]= 0;
    }
}
}
void afficher_plateau (int plateau[taille][taille]){
for ( int i=0; i< taille; i++){
    for( int j=0;j<taille; j++){
        printf("%4d", plateau[i][j]);
    }
    printf("\n");
}
}



int main() {

int plateau[taille][taille];
 initplateau(plateau);
 afficher_plateau(plateau);

printf("score:%d\n", score );
return 0;
}

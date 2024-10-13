#include "header.h"
#include <time.h>


char **init_board()
{
    char **board;
    int i = 0;
    int j;

    board = malloc(10 * sizeof(*board));
  
    while(i < 10)
    {
        board[i] = malloc(10 * sizeof(char));
        j = 0;
        while(j < 8)
        {
            board[i][j] = ' ';
            j++;
        }
        i++;
      

    }
    return board;
}
void display_board(char **board)
{
    int i = 0;
    int j = 0; 
     
    

    printf("\n");


while(i < 10)
{
    if( i < 1)
    {
        printf("##########\n");
    }
    else if(i <= 8)
    {
        printf("#%s#\n", board[i]);
        
    }
    else if( i > 8)
    {
        printf("##########\n");
    }
    i++;
}
}

void startEmplacement(char **board, Emplacement *empPos) {
    int x, y;
    do {
        x = rand() % 6;
        y = rand() % 6;
    }while(board[x][y] != ' ');

    board[x][y] = '.';
    empPos->x = x;
    empPos->y = y;
       
}
void startBoite(char **board, Boite *boitePos) {
    int x, y;
    do{
      x = rand() % 6 + 2;
      y = rand() % 6 + 2;

    }while(board[x][y]  != ' ');

     board[x][y] = 'X';
    boitePos->x = x;
    boitePos->y = y;
}
void startJoueur(char **board, Joueur *playerPos) {
    int x, y;
    do{
        x = rand() % 6 + 2;
        y = rand() % 6 + 2;
    }while(board[x][y] != ' ');

    board[x][y] = 'o';
    playerPos->x = x;
    playerPos->y = y;
    
}

void start(char **board, Joueur *playerPos, Boite *boitePos,  Emplacement *empPos){
    startJoueur(board, playerPos);
    startBoite(board, boitePos);
    startEmplacement(board, empPos);
}

void movement(char **board, Joueur *playerPos, Emplacement *empPos) {
    printf("Choisissez un mouvement : haut(z) bas(s) gauche(q) droite(d)\n");
    scanf("%c",&playerPos->movement);
    int move_x = playerPos->x;
    int move_y = playerPos->y;

    if(playerPos->movement == 'z'){
        move_x--;
    }else if(playerPos->movement == 's') {
        move_x++;
    }else if(playerPos->movement == 'q'){
        move_y--;
    }else if(playerPos->movement == 'd') {
        move_y++;
    }else {
        printf("Erreur de frappe veuillez ressaisir une touche correct\n");
        return;
    }


    if(board[move_x][move_y] = ' ' || board[move_x][move_y] == 'o') {

        board[playerPos->x][playerPos->y] == ' ';
        board[move_x][move_y] == 'o';
        playerPos->x = move_x;
        playerPos->y = move_y; 
    } 

    if(board[empPos->x][empPos->y] == ' '){
        board[empPos->x][empPos->y] == '.';

    }
}
    void moveboite(char **board, Boite *boitePos, Joueur *playerPos, Emplacement *empPos) {
        int move_x = boitePos->x;
        int move_y = boitePos->y;

        if(playerPos->x == boitePos->x && playerPos->y == boitePos->y && playerPos->movement == 's'){
           playerPos->x = move_x++;
        }
        if(board[move_x][move_y] == ' ' || '.'){
            board[boitePos->x][boitePos->y] = ' ';
            board[move_x][move_y] = 'X';
            boitePos->x = move_x;
            board[playerPos->x][playerPos->y] = ' ';
            playerPos->x++;
            board[playerPos->x][playerPos->y] = 'o';
        }else {
            printf("Vous ne pouvez pas déplacer la boîte vers le bas\n");
        }
    
        if(playerPos->x == boitePos->x && playerPos->y == boitePos->y && playerPos->movement == 'z'){
           playerPos->x = move_x--;
        }
        if(board[move_x][move_y] == ' ' || '.'){
            board[boitePos->x][boitePos->y] = ' ';
            board[move_x][move_y] = 'X';
            boitePos->x = move_x;
            board[playerPos->x][playerPos->y] = ' ';
            playerPos->x--;
            board[playerPos->x][playerPos->y] = 'o';
        }else {
            printf("Vous ne pouvez pas déplacer la boîte vers le haut\n");
        }
    
    
        if(playerPos->x == boitePos->x && playerPos->y == boitePos->y - 1 && playerPos->movement == 'd'){
           playerPos->y = move_y++;
        }
        if(board[move_x][move_y] == ' ' || '.'){
            board[boitePos->x][boitePos->y] = ' ';
            board[move_x][move_y] = 'X';
            boitePos->y = move_y;
            board[playerPos->x][playerPos->y] = ' ';
            playerPos->y++;
            board[playerPos->x][playerPos->y] = 'o';
        }else {
            printf("Vous ne pouvez pas déplacer la boîte vers la droite\n");
        }
        
    
        if(playerPos->x == boitePos->x && playerPos->y == boitePos->y && playerPos->movement == 'q'){
            playerPos->y = move_y--;
                if(board[move_x][move_y] == ' ' || '.') {
                    board[boitePos->x][boitePos->y] = ' ';
                    board[move_x][move_y] = 'X';
                    boitePos->y = move_y;
                    board[playerPos->x][playerPos->y] = ' ';
                    playerPos->y--;
                    board[playerPos->x][playerPos->y] = 'o';     
                }else{
                printf("Vous ne pouvez pas aller plus à gauche\n");
        }
        
    }
    
    if(boitePos->x = empPos->x && boitePos->y == empPos->y){
        printf("Bien joué c'était un peu facile nan ?\n");
        exit(0);
    }
    if((boitePos->x == 1 && boitePos->y == 1) ||
      (boitePos->x == 1 && boitePos->y == 8) || 
      (boitePos->x == 8 && boitePos->y == 1) || 
      (boitePos->x == 8 && boitePos->y == 8)) {
        printf("Vous avez perdu ! La boîte est coincée.\n");
        exit(0); 
    }
    }

    int main(){

        char **board;
        char mouvement;
        Joueur playerPos;
        Boite boitePos;
        Emplacement empPos;
        srand(time(NULL));
        board = init_board(); 
        start(board,&playerPos, &boitePos, &empPos);
        display_board(board);
    

    while(1) {
        system("clear");
        printf("Joueur : %d,%d\nEmplacement : %d,%d\nBoite : %d,%d\n", playerPos.x,playerPos.y,empPos.x,empPos.y,boitePos.x,boitePos.y);
        display_board(board);
        movement(board, &playerPos, &empPos);
        moveboite(board, &boitePos, &playerPos, &empPos);

    }   return 0;
    }



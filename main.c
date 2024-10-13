#include "header.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

// Initialisation de la planche
char **init_board() {

    char **board;
    int i = 0;
    int j;

    board = malloc(10 * sizeof(*board));
    if (board == NULL) {
        exit(EXIT_FAILURE);
    }

    while (i < 10) {
        board[i] = malloc(10 * sizeof(char));
        if (board[i] == NULL) {
            exit(EXIT_FAILURE);
        }
        j = 0;
        while (j < 8) { // Changer j < 8 à j < 10
            board[i][j] = ' ';
            j++;
        }
        i++;
    }
    return board;
}

// Affichage de la planche
void display_board(char **board) {
    int i = 0;

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

// Placement d'emplacement
void startEmplacement(char **board, Emplacement *empPos) {
    int x, y;
    do {
        x = rand() % 6 + 2;
        y = rand() % 6 + 2;
    } while (board[x][y] != ' ');

    board[x][y] = '.';
    empPos->x = x;
    empPos->y = y;
}

// Placement de boîte
void startBoite(char **board, Boite *boitePos) {
    int x, y;
    do {
        x = rand() % 6 + 2;
        y = rand() % 6 + 2;
    } while (board[x][y] != ' ');

    board[x][y] = 'X';
    boitePos->x = x;
    boitePos->y = y;
}

// Placement de joueur
void startJoueur(char **board, Joueur *playerPos) {
    int x, y;
    do {
        x = rand() % 6 + 2;
        y = rand() % 6 + 2;
    } while (board[x][y] != ' ');

    board[x][y] = 'o';
    playerPos->x = x;
    playerPos->y = y;
}

// Démarrage du jeu
void start(char **board, Joueur *playerPos, Boite *boitePos, Emplacement *empPos) {
    startJoueur(board, playerPos);
    startBoite(board, boitePos);
    startEmplacement(board, empPos);
}

void movement(char **board, Joueur *playerPos, Boite *boitePos, Emplacement *empPos) {
    printf("Choisissez un mouvement : haut(z) bas(s) gauche(q) droite(d)\n");
    scanf(" %c", &playerPos->movement); // Espace avant %c pour gérer le retour à la ligne
    int move_x = playerPos->x;
    int move_y = playerPos->y;

    // Déterminer le mouvement du joueur
    if (playerPos->movement == 'z') {
        move_x--;
    } else if (playerPos->movement == 's') {
        move_x++;
    } else if (playerPos->movement == 'q') {
        move_y--;
    } else if (playerPos->movement == 'd') {
        move_y++;
    } else {
        printf("Erreur de frappe, veuillez ressaisir une touche correcte\n");
        return;
    }

    // Vérifier si le joueur est adjacent à la boîte
    if (move_x == boitePos->x && move_y == boitePos->y) {
        // Déplacer la boîte dans la même direction que le joueur
        if (playerPos->movement == 'z') { // Déplacement vers le haut
            if (board[boitePos->x - 1][boitePos->y] == ' ') {
                board[boitePos->x][boitePos->y] = ' '; // Libérer l'ancienne position de la boîte
                boitePos->x--; // Déplacer la boîte vers le haut
                board[boitePos->x][boitePos->y] = 'X'; // Placer la boîte à la nouvelle position
                playerPos->x = move_x; // Déplacer le joueur
                board[playerPos->x][playerPos->y] == ' ';
            }
        } else if (playerPos->movement == 's') { // Déplacement vers le bas
            if (board[boitePos->x + 1][boitePos->y] == ' ') {
                board[boitePos->x][boitePos->y] = ' '; // Libérer l'ancienne position de la boîte
                boitePos->x++; // Déplacer la boîte vers le bas
                board[boitePos->x][boitePos->y] = 'X'; // Placer la boîte à la nouvelle position
                playerPos->x = move_x; // Déplacer le joueur
                board[playerPos->x][playerPos->y] == ' ';
            }
        } else if (playerPos->movement == 'q') { // Déplacement vers la gauche
            if (board[boitePos->x][boitePos->y - 1] == ' ') {
                board[boitePos->x][boitePos->y] = ' '; // Libérer l'ancienne position de la boîte
                boitePos->y--; // Déplacer la boîte à gauche
                board[boitePos->x][boitePos->y] = 'X'; // Placer la boîte à la nouvelle position
                playerPos->y = move_y; // Déplacer le joueur
                board[playerPos->x][playerPos->y] == ' ';
            }
        } else if (playerPos->movement == 'd') { // Déplacement vers la droite
            if (board[boitePos->x][boitePos->y + 1] == ' ') {
                board[boitePos->x][boitePos->y] = ' '; // Libérer l'ancienne position de la boîte
                boitePos->y++; // Déplacer la boîte à droite
                board[boitePos->x][boitePos->y] = 'X'; // Placer la boîte à la nouvelle position
                playerPos->y = move_y; // Déplacer le joueur
                board[playerPos->x][playerPos->y] == ' ';
            }
        }
    } else {
        // Si le joueur ne déplace pas la boîte, mettez à jour sa position
        if (board[move_x][move_y] == ' ' || board[move_x][move_y] == 'o') {
            board[playerPos->x][playerPos->y] = ' '; // Libérer l'ancienne position du joueur
            board[move_x][move_y] = 'o'; // Placer le joueur à la nouvelle position
            playerPos->x = move_x; // Mettre à jour la position du joueur
            playerPos->y = move_y; // Mettre à jour la position du joueur
            board[playerPos->x][playerPos->y] == ' ';
        }
    }

    // Vérification si la boîte est sur l'emplacement
    if (boitePos->x - 1 == empPos->x && boitePos->y - 1 == empPos->y && boitePos->x + 1 == empPos->x && boitePos->y + 1 == empPos->y) {
        printf("Bien joué c'était un peu facile nan ?\n");
        exit(0);
    }
}


// Mouvement de la boîte
void moveboite(char **board, Boite *boitePos, Joueur *playerPos, Emplacement *empPos) {
    int move_x = boitePos->x;
    int move_y = boitePos->y;

    if (playerPos->x == boitePos->x && playerPos->y == boitePos->y && playerPos->movement == 's') {
        move_x++; // Déplacer la boîte vers le bas
    }

    // Condition corrigée
    if (board[move_x][move_y] == ' ') {
        board[boitePos->x][boitePos->y] = ' '; // Libérer l'ancienne position
        board[move_x][move_y] = 'X'; // Déplacer la boîte
        boitePos->x = move_x; // Mettre à jour la position de la boîte
        boitePos->y = move_y; // Mettre à jour la position de la boîte
    }


    // Déplacement vers le haut
    if (playerPos->x == boitePos->x && playerPos->y == boitePos->y && playerPos->movement == 'z') {
        move_x--;
        if (board[move_x][move_y] == ' ') {
            board[boitePos->x][boitePos->y] = ' ';
            board[move_x][move_y] = 'X';
            boitePos->x = move_x;
            board[playerPos->x][playerPos->y] = ' ';
            playerPos->x--;
            board[playerPos->x][playerPos->y] = 'o';
        } else {
            printf("Vous ne pouvez pas déplacer la boîte vers le haut\n");
        }
    }

    // Déplacement vers la droite
    if (playerPos->x == boitePos->x && playerPos->y == boitePos->y && playerPos->movement == 'd') {
        move_y++;
        if (board[move_x][move_y] == ' ') {
            board[boitePos->x][boitePos->y] = ' ';
            board[move_x][move_y] = 'X';
            boitePos->y = move_y;
            board[playerPos->x][playerPos->y] = ' ';
            playerPos->y++;
            board[playerPos->x][playerPos->y] = 'o';
        } else {
            printf("Vous ne pouvez pas déplacer la boîte vers la droite\n");
        }
    }

    // Déplacement vers la gauche
    if (playerPos->x == boitePos->x && playerPos->y == boitePos->y && playerPos->movement == 'q') {
        move_y--;
        if (board[move_x][move_y] == ' ') {
            board[boitePos->x][boitePos->y] = ' ';
            board[move_x][move_y] = 'X';
            boitePos->y = move_y;
            board[playerPos->x][playerPos->y] = ' ';
            playerPos->y--;
            board[playerPos->x][playerPos->y] = 'o';
        } else {
            printf("Vous ne pouvez pas aller plus à gauche\n");
        }
    }

    // Vérification si la boîte est sur l'emplacement
    if (boitePos->x == empPos->x && boitePos->y == empPos->y) {
        printf("Bien joué c'était un peu facile nan ?\n");
        exit(0);
    }

    // Vérification si la boîte est coincée
    if ((boitePos->x == 1 && boitePos->y == 1) ||
        (boitePos->x == 1 && boitePos->y == 8) || 
        (boitePos->x == 8 && boitePos->y == 1) || 
        (boitePos->x == 8 && boitePos->y == 8)) {
        printf("Vous avez perdu ! La boîte est coincée.\n");
        exit(0); 
    }
}


int main() {
    char **board;
    Joueur playerPos;
    Boite boitePos;
    Emplacement empPos;
    srand(time(NULL));
    board = init_board(); 
    start(board, &playerPos, &boitePos, &empPos);
    display_board(board);

    while (1) {
        system("clear");
        printf("Joueur : %d,%d\nEmplacement : %d,%d\nBoite : %d,%d\n", playerPos.x, playerPos.y, empPos.x, empPos.y, boitePos.x, boitePos.y);
        display_board(board);
        movement(board, &playerPos, &boitePos, &empPos);
        moveboite(board, &boitePos, &playerPos, &empPos); // Appel de moveboite avec les bons paramètres
    }

    
    free(board);

    return 0;
}


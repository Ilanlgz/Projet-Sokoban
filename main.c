#include "header.h"

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

    int main(){

        char **board;
        int i;
        int j;
        board = init_board();
       // int end = -1;

        //while(end == -1)
    //{   
        display_board(board);


    //}
    }



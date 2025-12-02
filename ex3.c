#include <stdio.h>

#ifndef ROWS
#define ROWS 6
#endif

#ifndef COLS
#define COLS 7
#endif

#define CONNECT_N 4

/* Tokens */
#define EMPTY '.'
#define TOKEN_P1 'X'
#define TOKEN_P2 'O'

#define HUMAN 1
#define COMPUTER 2

//defines of my own

#define TRUE 1
#define FALSE 0

//functions of my own
int askNumber(char[][COLS], int, int);



int isColumnFull(char[][COLS], int, int, int);

int isBoardFull(char[][COLS], int, int);

int isInBounds(int, int, int, int);

/* Place token in column (0-based). Return row index or -1 if illegal */
int makeMove(char[][COLS], int, int, int, char);

int checkVictory(char[][COLS], int, int, int, int, char);

/* Human player: asks repeatedly until a valid non-full column is chosen (0-based) */
int humanChoose(char[][COLS], int, int);

/* Computer*/
int computerChoose(char[][COLS], int, int, char, char);

void runConnectFour(char[][COLS], int, int, int, int);

void initBoard(char[][COLS], int, int);

void printBoard(char[][COLS], int, int);

int getPlayerType(int);


int main() {
    char board[ROWS][COLS];
    printf("Connect Four (%d rows x %d cols)\n\n", ROWS, COLS);
    int p1Type = getPlayerType(1);
    int p2Type = getPlayerType(2);
    initBoard(board, ROWS, COLS);
    printBoard(board, ROWS, COLS);
    runConnectFour(board, ROWS, COLS, p1Type, p2Type);
    return 0;
}
void initBoard(char board[][COLS], int rows, int cols)
{
    for(int r=0; r<rows; r++)
    {
        for(int c=0; c<cols, c++)
        {
            board[c][r]=EMPTY;
        }
    }
}
int askNumber(char board[][COLS], int rows, int cols)
{   int selection;
    int forever=0;
    printf("Enter column (1-%d : \n", cols),
    while(forever==0)
    {
        scanf("%d", &selection);
        if(isInBounds(rows, cols, selection))
          if(!isColumnFull)
          { 
            return selection;
          }
        continue;
    }
}


int isColumnFull(char board[][COLS], int rows, int cols, int selection)
{
    for(int r = 0; r<rows; r++ )
    {
        if(board[r][selection]==EMPTY)
         return FALSE;
    }
  return TRUE;      
}

int isBoardFull(char board[][COLS], int rows, int cols)
{ 
    for (int r = 0; r<rows; r++) 
    {   
        for (int c = 0; c < cols; c++) 
        {
           if(board[r][c]==EMPTY)
             return FALSE; 
        }
    }
    return TRUE;
}

//Not sure if that's what they meant need to go over it again, too many variables
int isInBounds(int rows, int cols, int selection, int )
{

    if((selection<0)&&(selection>cols))
    {
       printf("Invalid Input");
       return FALSE;
    }
    else 
     return TRUE;
}


int makeMove(char board[][COLS], int rows, int cols, int selection, char token)
{
         for(int r = 0; r<rows; r++)
         {
            if(board[r][selection]==EMPTY)
            {
              board[r][selection]=token;
              return 0;
            }
         }
     
}







void printBoard(char board[][COLS], int rows, int cols) {
    printf("\n");
    for (int r = 0; r < rows; r++) {
        printf("|");
        for (int c = 0; c < cols; c++) {
            putchar(board[r][c]);
            printf("|");
        }
        printf("\n");
    }
    for (int c = 1; c <= cols; c++) {
        printf(" %d", c % 10);
    }
    printf("\n\n");
}

int getPlayerType(int playerNumber) {
    char ch;
    while (1) {
        printf("Choose type for player %d: h - human, c - computer: ", playerNumber);
        int n = scanf(" %c", &ch);
        if (n != 1) {
            printf("Input error. Try again.\n");
            while (getchar() != '\n'); // clear input buffer
            continue;
        }
        if (ch == 'h' || ch == 'H') return HUMAN;
        if (ch == 'c' || ch == 'C') return COMPUTER;

        printf("Invalid selection. Enter h or c.\n");
        while (getchar() != '\n'); // clear rest of input
    }
}

void runConnectFour(char board[][COLS], int ROWS, int COLS, int p1Type, int p2Type)
{  int forever=0;
    int selection;
    while(forever==0)
    {
        if(p1Type==HUMAN)
        {
         selection = askNumber(board[][COLS], ROWS, COLS);
         makeMove(board[][COLS], ROWS, COLS, selection, TOKEN_P1);
        }
         else
          computerChoose();
        if(checkVictory)
        {
          printf("adadacdaca");
          break;
        }
        if(!isBoardFull(board[][COLS], ROWS, COLS))
        {
          printf("adadacdaca");
          break;
        }

        if(p2Type==HUMAN)
        { 
            selection = askNumber(board[][COLS], ROWS, COLS);
            makeMove(board[][COLS], ROWS, COLS, selection, TOKEN_P2);
        }
            else 
             computerChoose();
         if(checkVictory)
        {
          printf("adadacdaca");
          break;
        }
        if(!isBoardFull(board[][COLS], ROWS, COLS))
        {
          printf("adadacdaca");
          break;
        }
     }












    }






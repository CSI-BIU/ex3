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
int checkCompCanWin(char[][COLS], int, int, int, char, char);


int isColumnFull(char[][COLS], int, int);

int isBoardFull(char[][COLS], int, int);

int isInBounds(int, int);

/* Place token in column (0-based). Return row index or -1 if illegal */
void makeMove(char[][COLS], int, int, char);

int checkVictory(char[][COLS], int, int, int, char);

/* Computer*/
int computerChoose(char[][COLS], int, int, char, int);

void runConnectFour(char[][COLS], int, int, int, int);

void initBoard(char[][COLS], int, int);

void printBoard(char[][COLS], int, int);

int getPlayerType(int);

int isColumnEmptyPC(char [][COLS], int, int);


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
    for(int r=0; r<=rows; r++)
    {
        for(int c=0; c<=cols; c++)
        {
            board[c][r]=EMPTY;
        }
    }
}


int askNumber(char board[][COLS], int rows, int cols)
{   int selection;
    int forever=0;
    printf("Enter column (1-%d) : \n", cols);
    while(forever==0)
    {
        scanf("%d", &selection);
        if(isInBounds(cols, selection))
          if(!isColumnFull(board, rows, selection))
          { 
            return selection;
          }
     continue;
    }
    return 0;
}


int isColumnFull(char board[][COLS], int rows, int selection)
{
    for(int r = rows-1; r>=0; r--)
    {
        if(board[r][selection-1]==EMPTY)
        {
          return FALSE;
        }
        
    }
  printf("Column %d is full. Choose another column.\n", selection);
  return TRUE;      
}

int isColumnEmptyPC(char board[][COLS], int rows, int selection)
{
    for(int r = rows-1; r>=0; r--)
    {
        if(board[r][selection]==EMPTY)
        {
          return TRUE;
        }
        
    }
  return FALSE;      
}



int isBoardFull(char board[][COLS], int rows, int cols)
{ 
    for (int r = rows-1; r>=0; r--) 
    {   
        for (int c = cols-1; c >= 0; c--) 
        {
           if(board[r][c]==EMPTY)
             return FALSE; 
        }
    }
    return TRUE;
}


int isInBounds(int cols, int selection)
{

    if(!((selection<=cols)&&(selection>0)))
    {
       printf("Invalid Input\n");
       return FALSE;
    }
    else 
     return TRUE;
}

void makeMove(char board[][COLS], int rows, int selection, char token)
{
         for(int r = rows-1; r>=0; r--)
         {
            if(board[r][selection]==EMPTY)
            {
              board[r][selection]=token;
              return;
            }
         }
     
}

//check victory works
int checkVictory(char board[][COLS], int rows, int cols, int winCon, char token)
{
    int count=0;
    //horizontal check
 for (int r = rows-1; r>=0; r--) 
    {   
        for (int c = cols-1; c >= 0; c--) 
        { 
             if(token==board[r][c])
              count++;
              else 
               count=0;
              if(count==winCon)
               return TRUE;
        }
    }
    //vertical check
 for(int c = cols-1; c >= 0; c--)
 {
   for (int r = rows-1; r >= 0; r--) 
        {     
            if(token==board[r][c])
              count++;
              else
              count=0;
            if(count==winCon)
               return TRUE;
           
        }
 }
    // diagonal check- right to left 
  for(int r = rows-1; r >= 0; r--)
       {
        for (int c = cols-1; c >= 0; c--) 
         {  count=0;
            for(int i=0; i<=cols; i++)
            {
               if(token==board[r-i][c-i])
                count++;
               if(count==winCon)
                 return TRUE;
            }
         }
       }
     //diagonal check- left to right 
    for(int r = rows-1; r >= 0; r--)
       {
        for (int c = 0; c<cols; c++) 
         {  count=0;
            for(int i=0; i<=cols; i++)
            {
               if(token==board[r-i][c+i])
                count++;
               if(count==winCon)
                return TRUE;
            }
           
         }
       }

return FALSE;
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

int checkCompCanWin(char board[][COLS], int rows, int cols, int winCon, char token,char oppToken)
{
   int count=0;
   int horRight=-1;
   int horLeft=-1;
   int vert=-1;
   int diagTL=-1;
   int diagBL=-1;
   int diagBR=-1;
   int diagTR=-1;
    //horizontal check right to left
 for (int r = rows-1; r>=0; r--) 
    {   
        for (int c = cols-1; c >= 0; c--) 
        { 
             if(token==board[r][c])
              count++;
              else 
               count=0;
              if((count==winCon)&&(board[r][c-1]==EMPTY)&&((board[r-1][c-1]==TOKEN_P1)||(board[r-1][c-1]==TOKEN_P2)))
               horRight= (c-1);
        }
    }
  //horizontal check left to right
  for (int r = rows-1; r>=0; r--) 
    {   
        for (int c = 0; c < cols; c++) 
        { 
             if(token==board[r][c])
              count++;
              else 
               count=0;
              if((count==winCon)&&(board[r][c+1]==EMPTY)&&((board[r-1][c+1]==TOKEN_P1)||(board[r-1][c+1]==TOKEN_P2)))
               horLeft=(c+1);
        }
    }
    //vertical check
 for(int c = cols-1; c >= 0; c--)
 {
   for (int r = rows-1; r >= 0; r--) 
        {     
            if(token==board[r][c])
              count++;
              else
              count=0;
            if((count==winCon)&&(board[r-1][c]==EMPTY))
               vert=c;
           
        }
 }
    // diagonal check- bottorm right right to left 
  for(int r = rows-1; r >= 0; r--)
       {
        for (int c = cols-1; c >= 0; c--) 
         {  count=0;
            for(int i=0; i<=cols; i++)
            {
               if(token==board[r-i][c-i])
                count++;
               if((count==winCon)&&(board[r-i-1][c-i-1]==EMPTY)&&((board[r-i][c-i-1]==TOKEN_P1)||(board[r-i-1][c-1-i]==TOKEN_P2)))
                 diagBR= (c-i-1);
            }
         }
       }
     //diagonal check- top right right to left 
    for(int r = 0; r < rows; r++)
       {
        for (int c = cols-1; c >= 0; c--) 
         {  count=0;
            for(int i=0; i<=cols; i++)
            {
               if(token==board[r+i][c-i])
                count++;
               if((count==winCon)&&(board[r+i+1][c-i-1]==EMPTY)&&((board[r+i][c-i-1]==TOKEN_P1)||(board[r+i+1][c-1-i]==TOKEN_P2)))
                 diagTR=(c-i-1);
            }
         }
       }


    
      //diagonal check- bottom left: left to right
       for(int c = 0; c < cols; c++)
       {
        for (int r = rows-1; r >= 0; r--) 
         {  count=0;
            for(int i=0; i<=cols; i++)
            {
               if(token==board[r-i][c+i])
                count++;
               if((count==winCon)&&(board[r-i-1][c+i+1]==EMPTY)&&((board[r-i][c+i+1]==TOKEN_P1)||(board[r-i-1][c+1+i]==TOKEN_P2)))
                 diagBL=(c+i+1);
            }
         }
       }
     //diagonal check- top left: left to right
     for(int c = 0; c < cols; c++)
       {
        for (int r = 0; r < rows; r++) 
         {  count=0;
            for(int i=0; i<=cols; i++)
            {
               if(token==board[r+i][c+i])
                count++;
               if((count==winCon)&&(board[r+i+1][c+i+1]==EMPTY)&&((board[r+i][c+i+1]==TOKEN_P1)||(board[r+i+1][c+1+i]==TOKEN_P2)))
                 diagTL=(c+i+1);
            }
         }
       }
//logic for return and make move
int priority[cols];
    if (cols%2 == 0) {
        priority[0] = cols/2 - 1;
        for (int i = 1, j = 1; i < cols; i += 2, j++) {
            priority[i] = priority[0] + j;
            if ((i + 1) < cols) {
                priority[i + 1] = priority[0] - j;
            }
        }
    } else {
        priority[0] = cols/2;
        for (int i = 1, j = 1; i < cols; i += 2, j++) {
            priority[i] = priority[0] - j;
            priority[i + 1] = priority[0] + j;
        }
    }
   for(int i=0; i<cols; i++)
   {
     if(horRight==priority[i])
     {
       makeMove(board, rows, horRight, oppToken);
       return horRight;
     }
    if(horLeft== priority[i])
     {
       makeMove(board, rows, horLeft, oppToken);
       return horLeft;
     }
    if(vert==priority[i])
     {
       makeMove(board, rows, vert, oppToken);
       return vert;
     }
    if(diagTL== priority[i])
     {
       makeMove(board, rows, diagTL, oppToken);
       return diagTL;
     }
    if(diagBL== priority[i])
     {
       makeMove(board, rows, diagBL, oppToken);
       return diagBL;
     }
    if(diagTR== priority[i])
     {
       makeMove(board, rows, diagTR, oppToken);
       return diagTR;
     }
    if(diagBR== priority[i])
     {
       makeMove(board, rows, diagBR, oppToken);
       return diagBR;
     }
     
   }
return -1;
}





//I'm sorry in advance
int computerChoose(char board[][COLS], int rows, int cols, char token, int winCon)
{ 
   char oppToken;
   if(token==TOKEN_P1)
      oppToken=TOKEN_P2;
    else
      oppToken=TOKEN_P1;
    //horizontal check if can win
     
    if(checkCompCanWin(board, rows, cols,winCon-1 ,token, token)!=-1)
      return checkCompCanWin(board, rows, cols,winCon-1 ,token, token);

      //blocking opp win
       if(checkCompCanWin(board, rows, cols,winCon-1 ,oppToken, token)!=-1)
         return checkCompCanWin(board, rows, cols,winCon-1 ,token, token);
   //create sequence of 3
   if(checkCompCanWin(board, rows, cols,winCon-2 ,token, token)!=-1)
      return checkCompCanWin(board, rows, cols,winCon-2 ,token, token);
   //blocking sequence of 3
   if(checkCompCanWin(board, rows, cols,winCon-2 ,oppToken, token)!=-1)
      return checkCompCanWin(board, rows, cols,winCon-2 ,oppToken, token);

   //arbitrary ordering rule
   int priority[cols];
    if (cols%2 == 0) {
        priority[0] = cols/2 - 1;
        for (int i = 1, j = 1; i < cols; i += 2, j++) {
            priority[i] = priority[0] + j;
            if ((i + 1) < cols) {
                priority[i + 1] = priority[0] - j;
            }
        }
    } else {
        priority[0] = cols/2;
        for (int i = 1, j = 1; i < cols; i += 2, j++) {
            priority[i] = priority[0] - j;
            priority[i + 1] = priority[0] + j;
        }
    }
  for (int i = 0; i < cols; i++) {
        if ((isColumnEmptyPC(board, rows, priority[i]))) 
        {
            makeMove(board, rows, priority[i], token);
            return priority[i];
        }
}
return 99;
}

void runConnectFour(char board[][COLS], int rows,  int cols, int p1Type, int p2Type)
{   int forever=0;
    int selection;
    while(forever==0)
    {   printf("Player 1 (X) turn.\n");
        if(p1Type==HUMAN)
        { 
         selection = (askNumber(board, rows, cols)-1);
         makeMove(board, rows, selection, TOKEN_P1);
         printBoard(board, rows, cols);
        }
         else
           {
             int compCoice= computerChoose(board, rows, cols, TOKEN_P1, CONNECT_N);
             printf("comp chose: %d\n", compCoice+1);
             printBoard(board, rows, cols);
           }
        if(checkVictory(board, rows, cols, CONNECT_N, TOKEN_P1))
        {
         printf("Player 1 (X) wins!\n");
         break;
         }
        if(isBoardFull(board, rows, cols))
        {
          printf("Board full and no winner. It's a tie!\n");
          break;
        }
        printf("Player 2 (O) turn.\n");
        if(p2Type==HUMAN)
        { 
            selection = (askNumber(board, rows, cols)-1);
            makeMove(board, rows, selection, TOKEN_P2);
            printBoard(board, rows, cols);
        }
           else
           {
             int compCoice= computerChoose(board, rows, cols, TOKEN_P2, CONNECT_N);
             printf("comp chose: %d\n", compCoice+1);
             printBoard(board, rows, cols);
           }
         if(checkVictory(board, rows, cols, CONNECT_N, TOKEN_P2))
        {
        printf("Player 2 (O) wins!\n");
         break;
        }
        if(isBoardFull(board, ROWS, COLS))
        {
          printf("Board full and no winner. It's a tie!\n");
          break;
        }
     }
    }
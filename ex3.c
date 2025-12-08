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
int checkCompCanWin(char[][COLS], int, int, int, char);
int comCanWinThree(char[][COLS], int, int, int, int, int, char);


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
    for(int r=0; r<rows; r++)
    {
        for(int c=0; c<cols; c++)
        {
            board[r][c]=EMPTY;
        }
    }
}


//checks if input is valid (in bounds, is not full and not a char)
int askNumber(char board[][COLS], int rows, int cols)
{   int selection;
    while (TRUE) {
        printf("Enter column (1-%d): ", cols);
        int check = scanf("%d", &selection);
        if (check != 1) {
            printf("Invalid input. Enter a number.\n");
            while (getchar() != '\n'); // clear input buffer
            continue;
        }
        if(isInBounds(cols, selection)){
         if(!isColumnFull(board, rows, selection)){ 
            return selection;
          }
         continue;
        }
}
}

//self explanatory I think
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

//checks if column is empty without printing anything for the computer
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

//checks of board is full
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

//checks if selection is in the bounds of the array
int isInBounds(int cols, int selection)
{   
    if(!((selection<=cols)&&(selection>0)))
    {
       printf("Invalid column. Choose between 1 and %d.\n", cols);
       return FALSE;
    }
    else 
     return TRUE;
}


//makes move
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


//checks if someone won
int checkVictory(char board[][COLS], int rows, int cols, int winCon, char token) {
    int count = 0;
    // Horizontal check
    for (int r = rows - 1; r >= 0; r--) {
        count = 0;  
        for (int c = 0; c < cols; c++) {
            if (token == board[r][c]) {
                count++;
            } else {
                count = 0;
            }
            if (count == winCon) {
                return TRUE;
            }
        }
    }

    // Vertical check
    for (int c = 0; c < cols; c++) {
        count = 0;  
        for (int r = 0; r < rows; r++) {
            if (token == board[r][c]) {
                count++;
            } else {
                count = 0;
            }
            if (count == winCon) {
                return TRUE;
            }
        }
    }
  

    //diagonal checks
     for (int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            if (board[i][j] == token) {
                count = 0;
                for (int k = j; k < cols; k++) {
                    if (board[i][k] == token) {
                        count++;
                        if (count >= winCon) {
                            return TRUE;
                        }
                    } else {
                        break;
                    }
                }

                count = 0;
                for (int k = i; k < rows; k++) {
                    if (board[k][j] == token) {
                        count++;
                        if (count >= winCon) {
                            return TRUE;
                        }
                    } else {
                        break;
                    }
                }

                count = 0;
                for (int l = i, k = j; l < rows && k < cols; l++, k++) {
                    if (board[l][k] == token) {
                        count++;
                        if (count >= winCon) {
                            return TRUE;
                        }
                    } else {
                        break;
                    }
                }

                count = 0;
                for (int l = i, k = j; l >= 0 && k < cols; l--, k++) {
                    if (board[l][k] == token) {
                        count++;
                        if (count >= winCon) {
                            return TRUE;
                        }
                    } else {
                        break;
                    }
                }
            }
        }
    }

    return FALSE;  
}



//prints board
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




//checks if computer makes any move based on the given priority
int checkCompCanWin(char board[][COLS], int rows, int cols, int winCon, char token)
{
   int priority[cols];
   //array for priority
   if (cols%2 == 0) {
        priority[0] = cols/2 - 1;
        for (int i = 1, j = 1; i < cols; i += 2, j++) {
            priority[i] = priority[0] + j;
            if ((i + 1) < cols) {
                priority[i + 1] = priority[0] - j;
                   }
        }
    }      else {
               priority[0] = cols/2;
             for (int i = 1, j = 1; i < cols; i += 2, j++) {
                priority[i] = priority[0] - j;
                priority[i + 1] = priority[0] + j;
               }
                }

    //check columns in the priority order
    for (int p = 0; p < cols; p++) {
        int c = priority[p]; 
        for (int r = rows - 1; r >= 0; r--) {
            if (board[r][c]==EMPTY) {
                makeMove(board, rows, c, token);
                if (comCanWinThree(board, rows, cols, r, c, winCon, token)) {
                    board[r][c] = EMPTY;
                    return c;  
                }
                board[r][c] = EMPTY;
                break;
            }
        }
    }
return -1;
}


//checking if computer can win/block/create sequence of 3 (used inside checkCompCanWIn)
int comCanWinThree(char board[][COLS], int rows, int cols, int currentRow, int currentCol, int winCon, char token)
{
    int count=1;
   // Horizontal check
   for(int i=currentCol; i>=0; i--)
   {
     if((i-1>=0)&&(board[currentRow][i-1]==token))
     {
        count++;
     }else {
        break;
     }
     
      if(count==winCon)
       return TRUE; 
   }
   for(int i=currentCol; i<cols; i++)
   {
     if((i+1<cols)&&(board[currentRow][i+1]==token))
     {
        count++;
     }else {
        break;
     }
     
      
      if(count==winCon)
       return TRUE; 
   }
   count=1;
   //vertical check
   for(int i=currentRow; i>=0; i--)
   {
     if((i-1>=0)&&(board[i-1][currentCol]==token))
     {
        count++;
     }else {
        break;
     }

    if(count==winCon)
      return TRUE; 
   }

   for(int i=currentRow; i<rows; i++)
   {
     if((i+1<rows)&&(board[i+1][currentCol]==token))
     {
        count++;
     }else {
        break;
     }
      
      if(count==winCon)
       return TRUE; 
   }
   count=1;
   //Diag down check
   for (int i = currentRow, j = currentCol; i < rows && j < cols; i++, j++)
   {
    if ((i+1<rows)&&(j+1<cols)&&board[i+1][j+1]==token)
    {
        count++;
    }else {
     break;
    }
    
    if(count==winCon)
     return TRUE;
   }

   for (int i = currentRow, j = currentCol; i >= 0 && j >= 0; i--, j--)
   {
    if ((i-1>=0)&&(j-1>=0)&&board[i-1][j-1]==token)
    {
        count++;
    }else {
     break;
    }
    
    if(count==winCon)
     return TRUE;
   }
    count=1;
   //Diag up check
   for (int i = currentRow, j = currentCol; i >= 0 && j < cols; i--, j++)
   {
    if ((i-1>=0)&&(j+1<cols)&&board[i-1][j+1]==token)
    {
        count++;
    }else {
     break;
    }
    
    if(count==winCon)
     return TRUE;
   }

   for (int i = currentRow, j = currentCol; i < rows && j >= 0; i++, j--)
   {
    if ((i+1<rows)&&(j-1>=0)&&board[i+1][j-1]==token)
    {
        count++;
    }else {
     break;
    }
    
    if(count==winCon)
     return TRUE;
   }
 return FALSE;
}

//Makes move for computer
int computerChoose(char board[][COLS], int rows, int cols, char token, int winCon)
{ 
   char oppToken;
   if(token==TOKEN_P1)
      oppToken=TOKEN_P2;
    else
      oppToken=TOKEN_P1;
    //can win
      int canWin= checkCompCanWin(board, rows, cols, winCon ,token);
      if(canWin!=-1)
      {
        makeMove(board, rows, canWin, token);
        return canWin;
      }
       
      //blocking opp win
      int canBlock= checkCompCanWin(board, rows, cols,winCon ,oppToken);
         if(canBlock!=-1)
         {
         makeMove(board, rows, canBlock, token);
         return canBlock; 
        }
         
   //create sequence of 3
    int threeRow= checkCompCanWin(board, rows, cols,winCon-1 ,token);
      if(threeRow!=-1){
       makeMove(board, rows, threeRow, token);
       return threeRow;
      }
   //blocking sequence of 3
      
   int threeBlock=  checkCompCanWin(board, rows, cols,winCon-1 ,oppToken);
      if(threeBlock!=-1)
      {
        makeMove(board, rows, threeBlock, token);
        return threeBlock;
      }

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
             printf("Computer chose column %d\n", compCoice+1);
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
             printf("Computer chose column %d\n", compCoice+1);
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
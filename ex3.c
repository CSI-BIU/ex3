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
            if(board[r][selection-1]==EMPTY)
            {
              board[r][selection-1]=token;
              return;
            }
         }
     
}

int checkVictory(char board[][COLS], int rows, int cols, int winCon, char token)
{
    int count=0;
    //horizontal check
 for (int r = rows-1; r>=0; r--) 
    {   
        for (int c = cols-1; c >= winCon; c--) 
        { count=0;
           for(int i=0; i<winCon; i++)
           {
             if(token==board[r][c-i])
              count++;
           } 
           if(count>=winCon)
            return TRUE;
        }
    }
    //vertical check
 for(int c = cols-1; c >= 0; c--)
 {
   for (int r = rows-1; r >= 0; r--) 
        { count=0;
           for(int i=0; i<winCon ; i++)
            {
                
                 if(token==board[r-i][c])
                  count++;
            }
            if(count>=winCon)
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

//I'm sorry in advance
int computerChoose(char board[][COLS], int rows, int cols, char token, int winCon)
{  int count=0;
   int horRight=-1;
   int horLeft=-1;
   int vert=-1;
   int diagTL=-1;
   int diagBT=-1;
   char oppToken;
   if(token==TOKEN_P1)
      oppToken=TOKEN_P2;
    else
      oppToken=TOKEN_P1;
    //horizontal check if computer can win right to left
    for (int r = rows-1; r>=0; r--) 
    {   
        for (int c = cols-1; c >= winCon; c--) 
        { count=0;
           for(int i=0; i<winCon-1; i++)
           {
              if(token==board[r][c-i])
               count++;

              if(count==winCon-1)
              {
                if(board[r][c-i-1]==EMPTY)
                {
                  if(board[r-1][c-i-1]!=EMPTY)
                     { 
                     horRight= (c-i-1);
                     }
                }
              }
                else{
                     if((count==winCon-2)&&(board[r-1][c-i-1]!=EMPTY)&&(board[r][c-i-1]==EMPTY)&&(board[r][c-i-2]==token))
                      horRight= (c-i-1);

                }
           } 
        }
    }

    //horizontal left to right
    for(int r = rows-1; r >= 0; r--)
       {
        for (int c = 0; c<cols; c++) 
         {  count=0;
            for(int i=0; i<=cols; i++)
            {
                  if(token==board[r][c-i])
                    count++;

               if(count==winCon-1)
              {
                if(board[r][c+i+1]==EMPTY)
                {
                  if(board[r-1][c+i+1]!=EMPTY)
                     { 
                     horLeft=(c+i+1);
                     }
                }
              }
              else {
               if((count==winCon-2)&&(board[r][c+i+1]==EMPTY)&&(board[r-1][c+i+1]!=EMPTY)&&(board[r][c+i+2]==token))
                horLeft=(c+i+1);
              }

         }
       }
    }

    //vertical check if computer can win
   for(int c = cols-1; c >= 0; c--)
   {
   for (int r = rows-1; r >= 0; r--) 
        { count=0;
           for(int i=0; i<winCon-1 ; i++)
            {
                
                 if(token==board[r-i][c])
                 { count++;}
                  

                  if(count==winCon-1)
                  {
                   if((board[r-i-1][c]==EMPTY))
                    vert=c;
                   }    
            }
            
        }
    }
    //diagonal check if computer can win- starts at top left and goes right
    for(int r = 0; r < rows-1; r++)
       {
        for (int c = 0; c < cols-1; c++) 
         {  count=0;
            for(int i=0; i<=cols; i++)
            {
               if(token==board[r+i][c+i]){
                count++;}
               if(count==winCon-1){
                 if((board[r+i+1][c+i+1]==EMPTY)&&(board[r+i+2][c+i+1]!=EMPTY))
                {
                diagTL= (c+i+1);
               }
              }
               else
               {   if((count==winCon-2)&&(board[r+i+1][c+i+1]==EMPTY)&&(board[r+i+2][c+i+2]==token)&&(board[r+i+2][c+i+1]!=EMPTY))
                      diagTL= (c+i+1);
               }

            }
         }
       }

      //diagonal check if computer can win- starts at bot right 
     for(int r = rows-1; r >= 0; r--)
       {
        for (int c = cols-1; c >= 0; c--) 
         {  count=0;
            for(int i=0; i<=cols; i++)
            {
               if(token==board[r-i][c-i]){
                count++;}
               if(count==winCon-1)
                 {
                     if((board[r-i-1][c-i-1]==EMPTY)&&(board[r-i][c-i-1]!=EMPTY))
                    {
                      diagBT= (c-i-1);
                    } 
               }
                 else
                 { if((count==winCon-2)&&(board[r-i-1][c-i-1]==EMPTY)&&(board[r-i-2][c-i-2]==token)&&(board[r-i][c-i-1]!=EMPTY))
                    diagBT= (c-i-1);
                   }
            }
         }
       }
  //logit time!!!!!!
   int arr[cols];
   if(cols%2==0)
   {
      arr[0] = cols/2;
      for (int i = 1, j = 1; i < cols; i += 2, j++) 
      {
        arr[i] = arr[1] + j;
            if ((i + 1) < cols) {
                arr[i + 1] = arr[1] - j;
            }
        }    
   }
   else
   {
     arr[0] = (cols/2);
     for (int i = 1, j = 1; i < cols; i += 2, j++) 
        {
            arr[i] = arr[0] - j;
            arr[i + 1] = arr[0] + j;
        }
   } 
   for(int i=0; i<cols; i++)
   {
     if(horRight==arr[i])
     {
       makeMove(board, rows, horRight, token);
       return horRight;
     }
    if(horLeft== arr[i])
     {
       makeMove(board, rows, horLeft, token);
       return horLeft;
     }
    if(vert==arr[i])
     {
       makeMove(board, rows, vert, token);
       return vert;
     }
    if(diagTL== arr[i])
     {
       makeMove(board, rows, diagTL, token);
       return diagTL;
     }
    if(diagBT== arr[i])
     {
       makeMove(board, rows, diagBT, token);
       return diagBT;
     }
   }


//Blocking the opponent 
   horRight=-1;
   horLeft=-1;
   vert=-1;
   diagTL=-1;
   diagBT=-1;
//horizontal check if computer blocks right to left
    for (int r = rows-1; r>=0; r--) 
    {   
        for (int c = cols-1; c >= winCon; c--) 
        { count=0;
           for(int i=0; i<winCon-1; i++)
           {
              if(oppToken==board[r][c-i])
               count++;

              if(count==winCon-1)
              {
                if(board[r][c-i-1]==EMPTY)
                {
                  if(board[r-1][c-i-1]!=EMPTY)
                     { 
                     horRight= (c-i-1);
                     }
                }
              }
                else{
                     if((count==winCon-2)&&(board[r-1][c-i-1]!=EMPTY)&&(board[r][c-i-1]==EMPTY)&&(board[r][c-i-2]==oppToken))
                      horRight= (c-i-1);

                }
           } 
        }
    }

    //horizontal left to right
    for(int r = rows-1; r >= 0; r--)
       {
        for (int c = 0; c<cols; c++) 
         {  count=0;
            for(int i=0; i<=cols; i++)
            {
                  if(oppToken==board[r][c-i])
                    count++;

               if(count==winCon-1)
              {
                if(board[r][c+i+1]==EMPTY)
                {
                  if(board[r-1][c+i+1]!=EMPTY)
                     { 
                     horLeft=(c+i+1);
                     }
                }
              }
              else {
               if((count==winCon-2)&&(board[r][c+i+1]==EMPTY)&&(board[r-1][c+i+1]!=EMPTY)&&(board[r][c+i+2]==oppToken))
                horLeft=(c+i+1);
              }

         }
       }
    }

    //vertical check if computer blocks
   for(int c = cols-1; c >= 0; c--)
   {
   for (int r = rows-1; r >= 0; r--) 
        { count=0;
           for(int i=0; i<winCon-1 ; i++)
            {
                
                 if(oppToken==board[r-i][c])
                 { count++;}
                  

                  if(count==winCon-1)
                  {
                   if((board[r-i-1][c]==EMPTY))
                    vert=c;
                   }    
            }
            
        }
    }
    //diagonal check if computer blocks- starts at top left and goes right
    for(int r = 0; r < rows-1; r++)
       {
        for (int c = 0; c < cols-1; c++) 
         {  count=0;
            for(int i=0; i<=cols; i++)
            {
               if(oppToken==board[r+i][c+i]){
                count++;}
               if(count==winCon-1){
                 if((board[r+i+1][c+i+1]==EMPTY)&&(board[r+i+2][c+i+1]!=EMPTY))
                {
                diagTL= (c+i+1);
               }
              }
               else
               {   if((count==winCon-2)&&(board[r+i+1][c+i+1]==EMPTY)&&(board[r+i+2][c+i+2]==oppToken)&&(board[r+i+2][c+i+1]!=EMPTY))
                      diagTL= (c+i+1);
               }

            }
         }
       }

      //diagonal check if computer can blocks- starts at bot right 
     for(int r = rows-1; r >= 0; r--)
       {
        for (int c = cols-1; c >= 0; c--) 
         {  count=0;
            for(int i=0; i<=cols; i++)
            {
               if(oppToken==board[r-i][c-i]){
                count++;}
               if(count==winCon-1)
                 {
                     if((board[r-i-1][c-i-1]==EMPTY)&&(board[r-i][c-i-1]!=EMPTY))
                    {
                      diagBT= (c-i-1);
                    } 
               }
                 else
                 { if((count==winCon-2)&&(board[r-i-1][c-i-1]==EMPTY)&&(board[r-i-2][c-i-2]==oppToken)&&(board[r-i][c-i-1]!=EMPTY))
                    diagBT= (c-i-1);
                   }
            }
         }
       }

  
  //More logic time!!!!!

   if(cols%2==0)
   {
      arr[0] = cols/2;
      for (int i = 1, j = 1; i < cols; i += 2, j++) 
      {
        arr[i] = arr[1] + j;
            if ((i + 1) < cols) {
                arr[i + 1] = arr[1] - j;
            }
        }    
   }
   else
   {
     arr[0] = (cols/2);
     for (int i = 1, j = 1; i < cols; i += 2, j++) 
        {
            arr[i] = arr[0] - j;
            arr[i + 1] = arr[0] + j;
        }
   } 
   for(int i=0; i<cols; i++)
   {
     if(horRight==arr[i])
     {
       makeMove(board, rows, horRight, token);
       return horRight;
     }
    if(horLeft== arr[i])
     {
       makeMove(board, rows, horLeft, token);
       return horLeft;
     }
    if(vert==arr[i])
     {
       makeMove(board, rows, vert, token);
       return vert;
     }
    if(diagTL== arr[i])
     {
       makeMove(board, rows, diagTL, token);
       return diagTL;
     }
    if(diagBT== arr[i])
     {
       makeMove(board, rows, diagBT, token);
       return diagBT;
     }
   }

//sequence of 3!!!!!!

   winCon=3; // :3
   horRight=-1;
   horLeft=-1;
   vert=-1;
   diagTL=-1;
   diagBT=-1;
    //horizontal check if computer can create sequence of 3
    for (int r = rows-1; r>=0; r--) 
    {   
        for (int c = cols-1; c >= winCon; c--) 
        { count=0;
           for(int i=0; i<winCon-1; i++)
           {
              if(token==board[r][c-i])
               count++;

              if(count==winCon-1)
              {
                if(board[r][c-i-1]==EMPTY)
                {
                  if(board[r-1][c-i-1]!=EMPTY)
                     { 
                     horRight= (c-i-1);
                     }
                }
              }
                else{
                     if((count==winCon-2)&&(board[r-1][c-i-1]!=EMPTY)&&(board[r][c-i-1]==EMPTY)&&(board[r][c-i-2]==token))
                      horRight= (c-i-1);

                }
           } 
        }
    }

    //horizontal left to right
    for(int r = rows-1; r >= 0; r--)
       {
        for (int c = 0; c<cols; c++) 
         {  count=0;
            for(int i=0; i<=cols; i++)
            {
                  if(token==board[r][c-i])
                    count++;

               if(count==winCon-1)
              {
                if(board[r][c+i+1]==EMPTY)
                {
                  if(board[r-1][c+i+1]!=EMPTY)
                     { 
                     horLeft=(c+i+1);
                     }
                }
              }
              else {
               if((count==winCon-2)&&(board[r][c+i+1]==EMPTY)&&(board[r-1][c+i+1]!=EMPTY)&&(board[r][c+i+2]==token))
                horLeft=(c+i+1);
              }

         }
       }
    }

    //vertical check if computer can create sequence of 3
   for(int c = cols-1; c >= 0; c--)
   {
   for (int r = rows-1; r >= 0; r--) 
        { count=0;
           for(int i=0; i<winCon-1 ; i++)
            {
                
                 if(token==board[r-i][c])
                 { count++;}
                  

                  if(count==winCon-1)
                  {
                   if((board[r-i-1][c]==EMPTY))
                    vert=c;
                   }    
            }
            
        }
    }
    //diagonal check if computer can create sequence of 3- starts at top left and goes right
    for(int r = 0; r < rows-1; r++)
       {
        for (int c = 0; c < cols-1; c++) 
         {  count=0;
            for(int i=0; i<=cols; i++)
            {
               if(token==board[r+i][c+i]){
                count++;}
               if(count==winCon-1){
                 if((board[r+i+1][c+i+1]==EMPTY)&&(board[r+i+2][c+i+1]!=EMPTY))
                {
                diagTL= (c+i+1);
               }
              }
               else
               {   if((count==winCon-2)&&(board[r+i+1][c+i+1]==EMPTY)&&(board[r+i+2][c+i+2]==token)&&(board[r+i+2][c+i+1]!=EMPTY))
                      diagTL= (c+i+1);
               }

            }
         }
       }

      //diagonal check if computer create sequence of 3- starts at bot right 
     for(int r = rows-1; r >= 0; r--)
       {
        for (int c = cols-1; c >= 0; c--) 
         {  count=0;
            for(int i=0; i<=cols; i++)
            {
               if(token==board[r-i][c-i]){
                count++;}
               if(count==winCon-1)
                 {
                     if((board[r-i-1][c-i-1]==EMPTY)&&(board[r-i][c-i-1]!=EMPTY))
                    {
                      diagBT= (c-i-1);
                    } 
               }
                 else
                 { if((count==winCon-2)&&(board[r-i-1][c-i-1]==EMPTY)&&(board[r-i-2][c-i-2]==token)&&(board[r-i][c-i-1]!=EMPTY))
                    diagBT= (c-i-1);
                   }
            }
         }
       }
   
    //Logic time once again
  
   if(cols%2==0)
   {
      arr[0] = cols/2;
      for (int i = 1, j = 1; i < cols; i += 2, j++) 
      {
        arr[i] = arr[1] + j;
            if ((i + 1) < cols) {
                arr[i + 1] = arr[1] - j;
            }
        }    
   }
   else
   {
     arr[0] = (cols/2);
     for (int i = 1, j = 1; i < cols; i += 2, j++) 
        {
            arr[i] = arr[0] - j;
            arr[i + 1] = arr[0] + j;
        }
   } 
   for(int i=0; i<cols; i++)
   {
     if(horRight==arr[i])
     {
       makeMove(board, rows, horRight, token);
       return horRight;
     }
    if(horLeft== arr[i])
     {
       makeMove(board, rows, horLeft, token);
       return horLeft;
     }
    if(vert==arr[i])
     {
       makeMove(board, rows, vert, token);
       return vert;
     }
    if(diagTL== arr[i])
     {
       makeMove(board, rows, diagTL, token);
       return diagTL;
     }
    if(diagBT== arr[i])
     {
       makeMove(board, rows, diagBT, token);
       return diagBT;
     }
   }
   
  //blocking the opponent 
   horRight=-1;
   horLeft=-1;
   vert=-1;
   diagTL=-1;
   diagBT=-1;
//horizontal check if computer blocks right to left
    for (int r = rows-1; r>=0; r--) 
    {   
        for (int c = cols-1; c >= winCon; c--) 
        { count=0;
           for(int i=0; i<winCon-1; i++)
           {
              if(oppToken==board[r][c-i])
               count++;

              if(count==winCon-1)
              {
                if(board[r][c-i-1]==EMPTY)
                {
                  if(board[r-1][c-i-1]!=EMPTY)
                     { 
                     horRight= (c-i-1);
                     }
                }
              }
                else{
                     if((count==winCon-2)&&(board[r-1][c-i-1]!=EMPTY)&&(board[r][c-i-1]==EMPTY)&&(board[r][c-i-2]==oppToken))
                      horRight= (c-i-1);

                }
           } 
        }
    }

    //horizontal left to right
    for(int r = rows-1; r >= 0; r--)
       {
        for (int c = 0; c<cols; c++) 
         {  count=0;
            for(int i=0; i<=cols; i++)
            {
                  if(oppToken==board[r][c-i])
                    count++;

               if(count==winCon-1)
              {
                if(board[r][c+i+1]==EMPTY)
                {
                  if(board[r-1][c+i+1]!=EMPTY)
                     { 
                     horLeft=(c+i+1);
                     }
                }
              }
              else {
               if((count==winCon-2)&&(board[r][c+i+1]==EMPTY)&&(board[r-1][c+i+1]!=EMPTY)&&(board[r][c+i+2]==oppToken))
                horLeft=(c+i+1);
              }

         }
       }
    }

    //vertical check if computer blocks
   for(int c = cols-1; c >= 0; c--)
   {
   for (int r = rows-1; r >= 0; r--) 
        { count=0;
           for(int i=0; i<winCon-1 ; i++)
            {
                
                 if(oppToken==board[r-i][c])
                 { count++;}
                  

                  if(count==winCon-1)
                  {
                   if((board[r-i-1][c]==EMPTY))
                    vert=c;
                   }    
            }
            
        }
    }
    //diagonal check if computer blocks- starts at top left and goes right
    for(int r = 0; r < rows-1; r++)
       {
        for (int c = 0; c < cols-1; c++) 
         {  count=0;
            for(int i=0; i<=cols; i++)
            {
               if(oppToken==board[r+i][c+i]){
                count++;}
               if(count==winCon-1){
                 if((board[r+i+1][c+i+1]==EMPTY)&&(board[r+i+2][c+i+1]!=EMPTY))
                {
                diagTL= (c+i+1);
               }
              }
               else
               {   if((count==winCon-2)&&(board[r+i+1][c+i+1]==EMPTY)&&(board[r+i+2][c+i+2]==oppToken)&&(board[r+i+2][c+i+1]!=EMPTY))
                      diagTL= (c+i+1);
               }

            }
         }
       }

      //diagonal check if computer can blocks- starts at bot right 
     for(int r = rows-1; r >= 0; r--)
       {
        for (int c = cols-1; c >= 0; c--) 
         {  count=0;
            for(int i=0; i<=cols; i++)
            {
               if(oppToken==board[r-i][c-i]){
                count++;}
               if(count==winCon-1)
                 {
                     if((board[r-i-1][c-i-1]==EMPTY)&&(board[r-i][c-i-1]!=EMPTY))
                    {
                      diagBT= (c-i-1);
                    } 
               }
                 else
                 { if((count==winCon-2)&&(board[r-i-1][c-i-1]==EMPTY)&&(board[r-i-2][c-i-2]==oppToken)&&(board[r-i][c-i-1]!=EMPTY))
                    diagBT= (c-i-1);
                   }
            }
         }
       }

   //Final logic!!!!!!!

   if(cols%2==0)
   {
      arr[0] = cols/2;
      for (int i = 1, j = 1; i < cols; i += 2, j++) 
      {
        arr[i] = arr[1] + j;
            if ((i + 1) < cols) {
                arr[i + 1] = arr[1] - j;
            }
        }    
   }
   else
   {
     arr[0] = (cols/2);
     for (int i = 1, j = 1; i < cols; i += 2, j++) 
        {
            arr[i] = arr[0] - j;
            arr[i + 1] = arr[0] + j;
        }
   } 
   for(int i=0; i<cols; i++)
   {
     if(horRight==arr[i])
     {
       makeMove(board, rows, horRight, token);
       return horRight;
     }
    if(horLeft== arr[i])
     {
       makeMove(board, rows, horLeft, token);
       return horLeft;
     }
    if(vert==arr[i])
     {
       makeMove(board, rows, vert, token);
       return vert;
     }
    if(diagTL== arr[i])
     {
       makeMove(board, rows, diagTL, token);
       return diagTL;
     }
    if(diagBT== arr[i])
     {
       makeMove(board, rows, diagBT, token);
       return diagBT;
     }
   }

   //arbitrary ordering rule


   if(cols%2==0)
   {
      arr[0] = cols/2;
      for (int i = 1, j = 1; i < cols; i += 2, j++) 
      {
        arr[i] = arr[1] + j;
            if ((i + 1) < cols) {
                arr[i + 1] = arr[1] - j;
            }
        }    
   }
   else
   {
     arr[0] = (cols/2);
     for (int i = 1, j = 1; i < cols; i += 2, j++) 
        {
            arr[i] = arr[0] - j;
            arr[i + 1] = arr[0] + j;
        }
   } 
   for(int i=0; i<cols; i++)
   {
      for(int r = 0; r<rows; r++)
    {
        if(board[r][arr[i]]==EMPTY)
        {
          makeMove(board, rows, arr[i], token);
        }
    }
   }



return 0;
}

void runConnectFour(char board[][COLS], int rows,  int cols, int p1Type, int p2Type)
{   int forever=0;
    int selection;
    while(forever==0)
    {   printf("Player 1 (X) turn.\n");
        if(p1Type==HUMAN)
        { 
         selection = askNumber(board, rows, cols);
         makeMove(board, rows, selection, TOKEN_P1);
         printBoard(board, rows, cols);
        }
         else
          computerChoose(board, rows, cols, TOKEN_P1, CONNECT_N);
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
            selection = askNumber(board, rows, COLS);
            makeMove(board, rows, selection, TOKEN_P2);
            printBoard(board, rows, cols);
        }
           else 
             computerChoose(board, rows, cols, TOKEN_P2, CONNECT_N);
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






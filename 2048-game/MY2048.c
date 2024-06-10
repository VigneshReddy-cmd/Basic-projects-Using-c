#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <stdbool.h>
#include <limits.h>
void gotoxy(int x, int y)
{
   COORD coord;
   coord.X = x;
   coord.Y = y;
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
#define LT 218
#define RT 191
#define LB 192
#define RB 217
#define TT 194
#define BT 193
#define LST 195
#define RST 180
#define PLUS 197
#define VL 179
#define HL 196
#define SPACE 32
#define BS 8

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define ESC 27
#define WIDTH 8
#define TOTCOLS 128
#define TOTROWS 25
#define SIZE 4
int max_score = 2048;
int score = 0;
int moves=0;
 int data_matrix[SIZE+1][SIZE+1] = {{0, 0, 0, 0},
                               {0, 0, 0, 0},
                               {0, 0, 2, 0},
                               {0, 0, 0, 4}};

void display_game()
{
   // data_matrix[3][1]=8;
   //  data_matrix[3][2]=32;
   //  data_matrix[3][3]=16;
   //  data_matrix[2][2]=8;
   //  data_matrix[2][3]=8;
   //  data_matrix[1][2]=8;
   int row, col;
   col = (TOTCOLS - ((WIDTH) * (SIZE) + (SIZE + 1))) / 2;
   row = (TOTROWS - (1 * (SIZE) + (SIZE + 1))) / 2;
   gotoxy(col+45,row);
   printf("YOUR SCORE IS:%d\n number of moves :%d",score,moves);
   // represent the matrix data in the table
   row += 1;
   col += 4;
   gotoxy(col, row);
   for (int i = 0; i < SIZE; i++)
   {
      for (int j = 0; j < SIZE; j++)
      {
         gotoxy(col + (j * (WIDTH + 1)), row);
         // skips col based on starting col and box value
         // print if a[i,j]!=0
         if (data_matrix[i][j] != 0)
         {
            printf("%d", data_matrix[i][j]);
         }
         else
         {
            printf("%c", SPACE);
         }
      }
      row += 2;
   }
}
void clear_game()
{
    int row, col;
   col = (TOTCOLS - ((WIDTH) * (SIZE) + (SIZE + 1))) / 2;
   row = (TOTROWS - (1 * (SIZE) + (SIZE + 1))) / 2;
   // represent the matrix data in the table
   row += 1;
   col += 4;
   gotoxy(col, row);
   for (int i = 0; i < SIZE; i++)
   {
      for (int j = 0; j < SIZE; j++)
      {
         gotoxy(col + (j * (WIDTH + 1)), row);
         // clearig the dabba before updation
         printf("%c",SPACE);
      }
      row += 2;
   }
}
// void random_generator() {
//     int i, j;
//     int emptySpots = 0;
    
//     // Count the number of empty spots in the game matrix
//     for (i = 0; i < SIZE; i++) {
//         for (j = 0; j < SIZE; j++) {
//             if (data_matrix[i][j] == 0) {
//                 emptySpots++;
//             }
//         }
//     }

//     // If there are empty spots, randomly choose one and place either 2 or 4
//     if (emptySpots > 0) {
//         int randomSpot = rand() % emptySpots;
//         int newValue = (rand() % 2 + 1) * 2; // Generates a 2 or 4
//         for (i = 0; i < SIZE; i++) {
//             for (j = 0; j < SIZE; j++) {
//                 if (data_matrix[i][j] == 0) {
//                     if (randomSpot == 0) {
//                         data_matrix[i][j] = newValue;
//                         return;
//                     } else {
//                         randomSpot--;
//                     }
//                 }
//             }
//         }
//     }

// }

bool check_count()
{
   for(int i=0;i<SIZE;i++)
   {
      for(int j=0;j<SIZE;j++)
      {
         if(data_matrix[i][j]==2048 && data_matrix[i][j]!=0)
         {
            
             return false;
         }
       
      }
   }
    return true;
}
void random_generator()
{
   
    int temp1,temp2,add,i,j;
   //  srand(time(NULL));
    temp1=rand()%SIZE;
    temp2=rand()%SIZE;
   add=(rand() % 2 == 0) ? 2 : 4;
    for(i=0;i<temp1;i++)
    {
        for(j=temp2;j<temp1;j++)
        {
            if(data_matrix[i][j]==0)
            {
                data_matrix[i][j]=add;
                return;
            }
        }
    }
}

void up()
{
   int temp=0;
   for(int i=0;i<4;i++) // colums
   {
    int row=1;// every column starts with row;
    while(1)
    {
     while(data_matrix[row][i]==0)
     {
        if(row==SIZE)
        break;
         row++;
     }
     if(row==SIZE)
     break;
       
         while(row>0 && (data_matrix[row-1][i]==0 || data_matrix[row-1][i]==data_matrix[row][i]))  
         // checking equals and adding if zero also adding to matrix
         {      
                data_matrix[row-1][i]+=data_matrix[row][i];
                if(data_matrix[row][i]!=0)
                {
                  temp+=abs(data_matrix[row-1][i]-data_matrix[row][i]);
                }
                data_matrix[row][i]=0;
                row--; // from bottom to top
         }
         row++;  // next row
    }
   }   
    score+=temp;

   random_generator();
}
void down()
{
  int temp=0;
   for(int i=0;i<SIZE;i++)  // col
   {
     int row=SIZE-2;
      while(1)
      {
      while(data_matrix[row][i]==0)
      {
         if(row==-1)
         break;
         row--;  // down to up traversal
      }
      if(row==-1) 
      // if row==0 we cant acess the row 0 son row <0 condition is good this is obtained fron trial and error
      {
         break;
      }
      
      while(row<SIZE-1 && (data_matrix[row+1][i]==0 || data_matrix[row+1][i]==data_matrix[row][i] ))
      {
         data_matrix[row+1][i]+=data_matrix[row][i];
         if(data_matrix[row][i]!=0)
                {
                  temp+=abs(data_matrix[row+1][i]-data_matrix[row][i]);
                }
          score+=data_matrix[row][i];
         data_matrix[row][i]=0;
         row++;  // traverse rows form top to bottom
      }
      row--;  // to regain row pos for second col
      }
   }
   score+=temp;
   random_generator();
}
void right()  // foom right to left
{
   int temp=0;
   for(int i=0;i<SIZE;i++)  // traverse rows in reverse direction same as down cols change fixed row
   {
       int col=SIZE-2;
       while(1)  // complete one full row if conplete and scol <0 break;
       {
         while(data_matrix[i][col]==0)
         {
            if(col==-1)  // finding the reverse order of the valuses till 0 and replace for each row
            break;
            col--;
         }
         if(col==-1) // next row condition;
         break;
         
  
         while(col<SIZE-1 && (data_matrix[i][col+1]==0 || data_matrix[i][col+1]==data_matrix[i][col])) 
         {
            data_matrix[i][col+1]+=data_matrix[i][col];  // col+1 because we traverse first forward
            if(data_matrix[i][col]!=0)
                {
                  temp+=abs(data_matrix[i][col]-data_matrix[i][col+1]);
                }
             score+=data_matrix[i][col];
            data_matrix[i][col]=0;
            col++;  // increment till reaches  last tupule
         } 
         col--;  //nnext col condition to know brief dry Run
       }
   }
       score+=temp;
   random_generator();
}
void left()
{
   int temp=0;
    
    for(int i=0;i<SIZE;i++)
    {
      int col=1; // traverse from col 1
      while(1)
      {
         while(data_matrix[i][col]==0)
         {
            if(col==SIZE)
            break;
            col++; // reverse direction index
         }
         if(col==SIZE)
         break;
         while(col>0 &&  (data_matrix[i][col-1]==0 || data_matrix[i][col-1]==data_matrix[i][col]))
         {
            data_matrix[i][col-1]+=data_matrix[i][col];
            if(data_matrix[i][col]!=0)
                {
                  temp+=abs(data_matrix[i][col]-data_matrix[i][col-1]);
                }
             score+=data_matrix[i][col];
            data_matrix[i][col]=0;
            col--;
         }
         col++;
      }
    }
      score+=temp;
    random_generator();
}


void drawdabba()
{
   system("cls");
   int col;
   int row;
   int ctr1;
   int ctr2;
   int ctr3;
   int ctr4;
   col = (TOTCOLS - ((WIDTH) * (SIZE) + (SIZE + 1))) / 2;
   row = (TOTROWS - (1 * (SIZE) + (SIZE + 1))) / 2;
   gotoxy(col, row);
   printf("%c", LT);
   for (ctr2 = 0; ctr2 < SIZE; ctr2++)
   {
      for (ctr1 = 0; ctr1 < WIDTH; ctr1++)
      {
         printf("%c", HL);
      }
      printf("%c", TT);
   }
   printf("%c%c", BS, RT);
   for (ctr4 = 0; ctr4 < SIZE; ctr4++)
   {
      row += 1;
      gotoxy(col, row);
      for (ctr2 = 0; ctr2 <= SIZE; ctr2++)
      {
         printf("%c", VL);
         for (ctr1 = 0; ctr1 < WIDTH; ctr1++)
         {
            printf("%c", SPACE);
         }
      }
      row += 1;
      gotoxy(col, row);
      printf("%c", LST);
      for (ctr2 = 0; ctr2 < SIZE; ctr2++)
      {
         for (ctr1 = 0; ctr1 < WIDTH; ctr1++)
         {
            printf("%c", HL);
         }
         printf("%c", PLUS);
      }
      printf("%c%c", BS, RST);
   }
   // last line
   gotoxy(col, row);
   printf("%c", LB);
   for (ctr2 = 0; ctr2 < SIZE; ctr2++)
   {
      for (ctr1 = 0; ctr1 < WIDTH; ctr1++)
      {
         printf("%c", HL);
      }
      printf("%c", BT);
   }
   printf("%c%c", BS, RB);
}
int main()
{

   printf("=====================2048 GAME===========================");
   printf("\n\n\n\t\t\tINSTRUCTION\n\n\n");
   printf(" ->  Enter arrow key to move\n\n");
   printf(" ->  For wining this game any one box have value 2048\n\n");
   printf(" -> You have maximum 2048 try to win the game\n\n\n\n");
   printf("\t\t\t\t\t\tPRESS ANY KEY TO PLAY\n");
   while (!kbhit());  // kbhit any key hist then strat
   drawdabba();
      int key;
   do
   {
       clear_game();
      display_game();
       getch();
    key=getch();
    if(check_count())
    {
    switch(key)
    {
      case UP:
              up();
               break;
      case DOWN:down();
                 break;
      case LEFT: left();
                 break;
      case RIGHT:right();
                 break;       
      default:break;
    }
    }
   
    // if we have any operation on this we have to call a random generator function
   
  moves++;
   max_score--;
   } while (key != ESC);
   printf("\n\n\n\n                                            THANKS FOR VISITING PLEASE PLAY AGAIN\033[0m\n\n\n");
}
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
void gotoxy(int x, int y)
{
  COORD coord;
  coord.X = x;
  coord.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
#define LT  218
#define RT  191
#define LB  192
#define RB  217
#define LST 195
#define RST 180
#define TT  194
#define BT  193
#define HL  196
#define VL  179
#define CROSS   197
#define SPACE   32
#define DIM     7
#define WIDTH   5
#define TOTCOLS 80
#define TOTROWS 25
#define BS 8
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define ESC 27
int DayOfWeek( int y, int m, int d ) 
/* returns Day of Week: 0 = Sunday, 1= Monday...
*/
{
 static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
 y -= m < 3;
 return (y + y/4 - y/100 + y/400 + t[m-1] + d) % 7;
} /*--DayOfWeek( )--------*/

/*Function to print the calender*/
void calendar(int month, int year)
{
   int row;
   int col;
   int ctr;
   int dayCtr;
   char *month_names[]=
   {
       "",
       "January",
       "February",
       "March",
       "April",
       "May",
       "June",
       "July",
       "August",
       "September",
       "October",
       "November",
       "December",

   };
   int days_in_months []  = {0,31,28,31,30,31,30,31,31,30,31,30,31};
   col = (TOTCOLS - ( (WIDTH) * (DIM) + (DIM + 1)))/2;
   row = (TOTROWS - ( (1) * (DIM) + (DIM + 1)))/2;
   gotoxy(30,3);
   printf("%10s , %d", month_names[month],year);
   col+=3;
   row+=3;
   gotoxy(col, row);
   days_in_months [ 2 ] = ( ((year%4==0) && (year%100!=0)) || (year%400==0)) ? 29 : 28;
   for( dayCtr = 1, ctr = DayOfWeek(year,month,1); dayCtr <= days_in_months[ month]; dayCtr+=1, ctr+=1)
   {
        if ( ctr == DIM)
        {
            ctr = 0;
            row += 2;
        }
       gotoxy(col + ( ctr * (WIDTH+1) ), row);
       printf("%02d", dayCtr);

   }

}
/* Function to print the Headings of the Calender Including days and year*/
void colHeadings()
{
   int row;
   int col;
   int ctr;
  char*days [7]={"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};

   col = (TOTCOLS - ( (WIDTH) * (DIM) + (DIM + 1)))/2;
   row = (TOTROWS - ( (1) * (DIM) + (DIM + 1)))/2;
   row+=1;
   col+=2;
   gotoxy(col, row);
   for( ctr = 0; ctr < DIM; ctr +=1)
   {
       gotoxy(col + (ctr * (WIDTH + 1)), row);
       printf("%s", days[ctr]);
   }
}
/*Used to Clean the current Calender when user wants to change the month / year */
void cleanCalendar()
{
    int dayCtr;
    int ctr;
    int row;
    int col;
   col = (TOTCOLS - ( (WIDTH) * (DIM) + (DIM + 1)))/2;
   row = (TOTROWS - ( (1) * (DIM) + (DIM + 1)))/2;
   col+=3;
   row+=3;

   for( dayCtr = 1, ctr = 0; dayCtr <= 42; dayCtr+=1, ctr+=1)
   {
        if ( ctr == DIM)
        {
            ctr = 0;
            row += 2;
        }
       gotoxy(col + ( ctr * (WIDTH+1) ), row);
       printf("  ");

   }

}
/* Function used to drwa the outline of the Calender based on the file below CalenWork.txt*/
void drawDabba()
{
   int row;
   int col;
   int ctr1;
   int ctr2;
   int ctr3;
   int ctr4;
   col = (TOTCOLS - ( (WIDTH) * (DIM) + (DIM + 1)))/2;
   row = (TOTROWS - ( (1) * (DIM) + (DIM + 1)))/2;
   // FL begins
   gotoxy(col, row);

   printf("%c", LT);

   for( ctr2 = 0; ctr2 < DIM; ctr2+=1)
   {
       for(ctr1 = 0;  ctr1 < WIDTH ; ctr1+=1)
       {
       printf("%c", HL);
       }
       printf("%c", TT);
   }
   printf("%c%c", BS, RT);
   // FL ends
//    mine completed         


   for ( ctr3 = 0; ctr3 < DIM; ctr3+=1)
   {
   row+=1;
   gotoxy(col,row);
   for( ctr2 = 0; ctr2 <= DIM; ctr2+=1)
   {
   printf("%c", VL);
       for(ctr1 = 0;  ctr1 < WIDTH ; ctr1+=1)
       {
       printf("%c", SPACE);
       }
   }
   row += 1;
   gotoxy(col, row);
   printf("%c", LST);
   for( ctr2 = 0; ctr2 < DIM; ctr2+=1)
   {

       for(ctr1 = 0;  ctr1 < WIDTH ; ctr1+=1)
       {
       printf("%c", HL);
       }
    printf("%c", CROSS);
   }
   printf("%c%c", BS, RST);
   }
   // LL begins
   gotoxy(col, row);

   printf("%c", LB);

   for( ctr2 = 0; ctr2 < DIM; ctr2+=1)
   {
       for(ctr1 = 0;  ctr1 < WIDTH ; ctr1+=1)
       {
       printf("%c", HL);
       }
       printf("%c", BT );
   }
   printf("%c%c", BS, RB);
   // LL ends

}
int main()
{
    int month;
    int year;
    int key;
    month = 10;
    year = 2023;
    drawDabba();
    colHeadings();
    do
    {
    cleanCalendar();
    calendar(month,year);
    getch();
    key = getch();
    switch ( key )
    {
        case RIGHT :
            month+=1;
            if ( month > 12)
            {
                month=1;
                year+=1;

            }
            break;
      case  LEFT :
           month -= 1;
           if ( month == 0)
           {
               month = 12;
               year -=1;
           }
           break;
       case UP : year+=1; break;
       case DOWN : year -=1;
    }

    } while ( key != 27);
     return EXIT_SUCCESS;

}

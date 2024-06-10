#include<stdio.h>
#include<math.h>
#define SIZE 55
int main()
{
   // objecting score  no source
    int data_matrix[4][4] = {{4, 0, 2,2},
                               {0,0,0,0},
                               {0, 0, 2, 0},
                               {16, 0, 8, 8}
                               {3,4,5,2}};
     for(int i=0;i<4;i++) // colums
   {
      for(int j=0;j<4;j++)  
      {
      printf("%d ",data_matrix[i][j]);
      }
      printf("\n"); 
   }      
   int score=0; 
   // up ?  ok     
    // down ? ok
    // right means left to right right is last pos to get
    // right ?  ok
    // left means right to left lasrt pos is left
    // left ^?  ok
    printf("\n");
   
    
   for(int i=0;i<4;i++) // colums in t and b whwre as rows in R and L
   {
       int temp=0;
    int col=1;// every column starts with row with lwaving one row
    while(1)
    {
     while(data_matrix[i][col]==0)
     {
        if(col==SIZE)
        break;
         col++;  // down to up or right to left reverse 
     }
     if(col==SIZE)
     break;
       
      while(col>0 && (data_matrix[i][col-1]==0 || data_matrix[i][col-1]==data_matrix[i][col]))  // reverse up to down or left to right
         // checking equals and adding if zero also adding to matrix
         {
              
                data_matrix[i][col-1]+=data_matrix[i][col];
                if(data_matrix[i][col]!=0)
                {
                  temp+=abs(data_matrix[i][col]-data_matrix[i][col-1]);
                }
                data_matrix[i][col]=0;
                col--;
         }
         col++;
    }
    score+=temp;
          printf("\nscore is:%d",score);
   }   
   
   printf("\n\n\n\n"); 
   //moving only one size up move all sizes up means
   // need changes
   for(int i=0;i<4;i++) // colums
   {
      for(int j=0;j<4;j++)  
      {
      printf("%d",data_matrix[i][j]);
      }
      printf("\n"); 
   }  
}
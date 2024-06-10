#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
int addint(int x,int y)
{
    return x+y;
}
int doubleadd(int (*functionpointer)(int,int),int x,int y)
{

    return functionpointer(x,y);
}
// int doubleadd(int (*functionpointer)(int, int), int x, int y) {
//     return functionpointer(x, y);
// }

int main()
{
int (*functionpointer)(int,int);
functionpointer=&addint;
    // function pointer;
      int result = functionpointer(3, 4);
    printf("Result: %d\n", result);
    int (*FunctionFactory)(int(*)(int,int),int,int);
    FunctionFactory=&doubleadd;
    int num1;
    scanf("%d",&num1);
    int num2;
    scanf("%d",&num2);
    int res=FunctionFactory(functionpointer,num1,num2);
    printf("\n%ddouble:",res);
return EXIT_SUCCESS;
}
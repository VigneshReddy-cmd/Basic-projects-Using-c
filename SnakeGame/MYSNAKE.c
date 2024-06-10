#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <limits.h>

void gotoxy(int x, int y)
{
  COORD coord;
  coord.X = x;
  coord.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// defining macros
// corners
#define LT 218 // ┌
#define RT 191 // ┐
#define LB 192 // └
#define RB 217 // ┘
//  T members
#define TST 194 //  ┬
#define BST 193 //  ┴
#define LST 195 // ├
#define RST 180 //  ┤
// plus
#define PLUS 197 //  ┼
//  Lines and spaces
#define VL 179   //  │
#define HL 196   // ─
#define Space 32 // " "
#define BS 8
// operators
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define ESC 27
// box
#define startcol 26
#define endcol 97
#define startrow 5
#define endrow 20

int snake_headx, snake_heady;
bool gameover = false;
int fruitx, fruity;
int random1 = 0, random2 = 22000;
int len = 0;
int snake_length = 1;
int score = 0;
int tailX[100], tailY[100];

void generate_random_fruit()
{
  srand(time(0));
  fruitx = rand() % (endcol - startcol + 1) + startcol;
  random1++;
  srand(random2);
  fruity = rand() % (endrow - startrow + 1) + startrow;
  random2--;
  gotoxy(fruitx, fruity);
  printf("*");
}

void drawmiddle(int row, int col, bool flag)
{
  row += 1;
  for (int ctr2 = 1; ctr2 <= 4; ctr2++)
  {
    gotoxy(col, row++);
    printf("%c", VL);
    for (int i = 0; i < (endcol - startcol); i++)
    {
      printf("%c", Space);
    }
    printf("%c", VL);
  }

  gotoxy(col, row);
  printf("%c", VL);
  for (int i = 0; i < (endcol - startcol); i++)
  {
    printf("%c", Space);
  }
  if (flag)
    printf("%c", LST);
  else
    printf("%c", Space);
  for (int i = 0; i < endrow; i++)
  {
    printf("%c", HL);
  }
  printf("%c", RST);
}

void drawdabba()
{
  int row = startrow;
  int col = startcol;
  gotoxy(col, row);
  printf("%c", LT);
  int ctr = 0;

  for (ctr = 0; ctr < (endcol - startcol); ctr++)
  {
    printf("%c", HL);
  }
  printf("%c", TST);
  for (ctr = 0; ctr < endrow; ctr++)
  {
    printf("%c", HL);
  }
  printf("%c", RT);

  bool flag = true;
  drawmiddle(row, col, flag);
  gotoxy(col + 73, row + 1);
  row += startrow;
  printf("HIGH SCORE");
  drawmiddle(row, col, flag);
  row += startrow;
  flag = false;
  drawmiddle(row, col, flag);

  row += 5;
  gotoxy(col, row);
  printf("%c", LST);
  for (int i = 0; i < (endcol - startcol); i++)
  {
    printf("%c", HL);
  }
  printf("%c", BST);
  for (int j = 0; j < 4; j++)
  {
    row += 1;
    gotoxy(col, row);
    printf("%c", VL);
    for (int i = 0; i < (endcol - startcol); i++)
    {
      printf("%c", Space);
    }
    printf("%c", VL);
  }

  row += 1;
  gotoxy(col, row);
  printf("%c", LB);
  for (int i = 0; i < (endcol - startcol); i++)
  {
    printf("%c", HL);
  }
  printf("%c", RB);
}

void update_tail()
{
  int prevX = tailX[0];
  int prevY = tailY[0];
  int prev2X, prev2Y;
  tailX[0] = snake_headx;
  tailY[0] = snake_heady;
  for (int i = 1; i < snake_length; i++)
  {
    prev2X = tailX[i];
    prev2Y = tailY[i];
    tailX[i] = prevX;
    tailY[i] = prevY;
    prevX = prev2X;
    prevY = prev2Y;
  }
}

void move_snake(int direction)
{
  switch (direction)
  {
  case UP:
    snake_heady--;
    break;
  case DOWN:
    snake_heady++;
    break;
  case LEFT:
    snake_headx--;
    break;
  case RIGHT:
    snake_headx++;
    break;
  }
}

void draw_snake()
{
  for (int i = 0; i < snake_length; i++)
  {
    gotoxy(tailX[i], tailY[i]);
    printf("O");
  }
  gotoxy(snake_headx, snake_heady);
  printf("O");
}

void erase_snake()
{
  for (int i = 0; i < snake_length; i++)
  {
    gotoxy(tailX[i], tailY[i]);
    printf(" ");
  }
  gotoxy(snake_headx, snake_heady);
  printf(" ");
}

void check_collision()
{
  if (snake_headx == startcol || snake_headx == endcol || snake_heady == startrow || snake_heady == endrow)
  {
    gameover = true;
  }
  for (int i = 0; i < snake_length; i++)
  {
    if (tailX[i] == snake_headx && tailY[i] == snake_heady)
    {
      gameover = true;
    }
  }
}

int main()
{
  int direction = RIGHT;
  drawdabba();
  snake_headx = 26, snake_heady = 6;
  tailX[0] = snake_headx;
  tailY[0] = snake_heady;
  generate_random_fruit();

  do
  {
    erase_snake();
    update_tail();
    move_snake(direction);
    check_collision();
    if (gameover)
      break;
    draw_snake();

    if (snake_headx == fruitx && snake_heady == fruity)
    {
      score += 10;
      snake_length++;
      generate_random_fruit();
    }

    if (_kbhit())
    {
      switch (_getch())
      {
      case UP:
        if (direction != DOWN)
          direction = UP;
        break;
      case DOWN:
        if (direction != UP)
          direction = DOWN;
        break;
      case LEFT:
        if (direction != RIGHT)
          direction = LEFT;
        break;
      case RIGHT:
        if (direction != LEFT)
          direction = RIGHT;
        break;
      }
    }

    Sleep(100);

  } while (!gameover && _getch() != ESC);

  gotoxy(55, 27);
  printf("GAME OVER! Your score: %d", score);
  return 0;
}

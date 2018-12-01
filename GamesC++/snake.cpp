#include <iostream>
#include <termios.h>
#include <sys/ioctl.h>
#include <time.h>
using namespace std;
const int width = 40, height = 20;
int x, y, Xfruit = 1, Yfruit = 1, score;
char keyb;
bool gameOver = false;
int tail;
int Xtail[100];
int Ytail[100];
bool pressed;
void FRand()
{
  Xfruit = rand() % (width-2) + 1;
  Yfruit = rand() % (height-2) + 1;
}
bool kbhit()
{
    termios term;
    tcgetattr(0, &term);

    termios term2 = term;
    term2.c_lflag &= ~ICANON;
    tcsetattr(0, TCSANOW, &term2);

    int byteswaiting;
    ioctl(0, FIONREAD, &byteswaiting);

    tcsetattr(0, TCSANOW, &term);

    return byteswaiting > 0;
}
void Setup()
{
  pressed = false;
  tail = 0;
  score = 0;
  FRand();
  x = width/2;
  y = height/2;
}
void Draw()
{
  system("clear");
  cout << "\n\n\t\t";
  for(int i = 0; i < height; i++)
  {
    for(int j = 0; j < width; j++)
      if(i == 0 || i == height-1)
        cout << "#";
      else
        if(j == 0 || j == width-1)
          cout << "#";
        else
          if(i == y && j == x)
            cout << "O";
          else
            if(i == Yfruit && j == Xfruit)
              cout << "@";
            else
            {
              bool check = false;
              for(int k = 0; k < tail; k++)
              {
                if(i == Ytail[k] && j == Xtail[k])
                {
                  cout << "o";
                  check = true;
                }
              }
              if(!check)
                cout << " ";
            }
    cout << endl << "\t\t";
  }
  cout << endl << "\t\tScore: " << score << endl;
}
void Input()
{
  if(kbhit())
  {
    keyb = getchar();
    pressed = true;
  }
}
void Logic()
{
  if(pressed)
  {
    int prevX = Xtail[0];
    int prevY = Ytail[0];
    int prev2X, prev2Y;
    Xtail[0] = x;
    Ytail[0] = y;
    for (int i = 1; i < tail; i++)
    {
        prev2X = Xtail[i];
        prev2Y = Ytail[i];
        Xtail[i] = prevX;
        Ytail[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (keyb)
    {
      case 'a': x--;
      break;
      case 'd': x++;
      break;
      case 'w': y--;
      break;
      case 's': y++;
      break;
      default:
      break;
    }
  }
  if (x >= width-1 || x <= 0 || y >= height-1 || y <= 0)
    gameOver = true;
  //if (x >= width) x = 0; else if (x < 0) x = width - 1;
  //if (y >= height) y = 0; else if (y < 0) y = height - 1;
  for (int i = 0; i < tail; i++)
      if (Xtail[i] == x && Ytail[i] == y)
          gameOver = true;
  if(x == Xfruit && y == Yfruit)
  {
    score += 10;
    srand(time(NULL));
    FRand();
    tail++;
  }
  pressed = false;
}
int main()
{
  bool cont = true;
  while(cont)
  {
    Setup();
    while(!gameOver)
    {
      Draw();
      Input();
      Logic();
    }
    system("clear");
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t" << "GAME OVER \n\n\t\t\t\tScore: " << score << "\n\n\n\n\n\n\n\n\n\n";
    cout << "\t\t\t\tPlay again? \n\t\t\t\t   (Y/N) \n\t\t\t\t     ";
    char choice = getchar();
    switch (choice)
    {
      case 'N':
      case 'n':
        cont = false;
        break;
      default:
        gameOver = false;
        break;
    }
  }
  return 0;
}

#include <iostream>
#include <random>
#include <ctime>
#include <termios.h>
#include <sys/ioctl.h>
#include <unistd.h>
using namespace std;

const int N = 4;
const int J = 6;
bool gameOver = false;
bool pressed = false;
char choise = 'n';
int **margin = new int* [N];
bool different = true;
bool win = false;

//Instruments
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
bool Is_full()
{
    int empty = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (margin[i][j] == 0)
                empty++;
    if (empty)
        return false;
    else
        return true;
}
void Compare(int **before, int **after)
{
    int index = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (before[i][j] != after[i][j])
                index++;
    if (index == 0)
        different = false;
    else
        different = true;
}
int Value(int **array)
{
    long int result = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            result += array[i][j] * array[i][j];
    return result;
}
int Big_x_side(int **array)
{
    int max = 0;
    int x = 0;
    int side = 3;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (array[i][j] > max)
            {
                max = array[i][j];
                x = j;
            }
    if (x <= N/2)
        side = 2;
    else
        side = 3;
    return side;
}
int Big_y_side(int **array)
{
    int max = 0;
    int y = 0;
    int side = 1;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (array[i][j] > max)
            {
                max = array[i][j];
                y = i;
            }
    if (y <= N/2)
        side = 0;
    else
        side = 1;
    return side;
}

void Margin_Up(int **array)
{
    for (int i = 0; i < N; i++)
    {
        int blocked = 0;
        for (int j = 1; j < N; j++)
        {
            if (array[j][i] != 0)
            {
                bool free = true;
                for (int k = j; k > 0; k--)
                {
                    if (array[k-1][i] == 0)
                    {
                        array[k-1][i] = array[k][i];
                        array[k][i] = 0;
                    } else
                        if(array[k-1][i] == array[k][i] && free == true && array[k-1][i] != blocked)
                        {
                            array[k-1][i] *= 2;
                            array[k][i] = 0;
                            free = false;
                            blocked = array[k-1][i];
                        }
                }
            }
        }
    }
}
void Margin_Down(int **array)
{
    for (int i = 0; i < N; i++)
    {
        int blocked = 0;
        for (int j = N-1; j >= 0; j--)
        {
            if (array[j][i] != 0)
            {
                bool free = true;
                for (int k = j; k < N-1; k++)
                {
                    if (array[k+1][i] == 0)
                    {
                        array[k+1][i] = array[k][i];
                        array[k][i] = 0;
                    } else
                        if(array[k+1][i] == array[k][i] && free == true && array[k+1][i] != blocked)
                        {
                            array[k+1][i] *= 2;
                            array[k][i] = 0;
                            free = false;
                            blocked = array[k+1][i];
                        }
                }
            }
        }
    }
}
void Margin_Left(int **array)
{
    for (int i = 0; i < N; i++)
    {
        int blocked = 0;
        for (int j = 1; j < N; j++)
        {
            if (array[i][j] != 0)
            {
                bool free = true;
                for (int k = j; k > 0; k--)
                {
                    if (array[i][k-1] == 0)
                    {
                        array[i][k-1] = array[i][k];
                        array[i][k] = 0;
                    } else
                        if(array[i][k-1] == array[i][k] && free == true && array[i][k-1] != blocked)
                        {
                            array[i][k-1] *= 2;
                            array[i][k] = 0;
                            free = false;
                            blocked = array[i][k-1];
                        }
                }
            }
        }
    }
}
void Margin_Right(int **array)
{
    for (int i = 0; i < N; i++)
    {
        int blocked = 0;
        for (int j = N-1; j >= 0; j--)
        {
            if (array[i][j] != 0)
            {
                bool free = true;
                for (int k = j; k < N-1; k++)
                {
                    if (array[i][k+1] == 0)
                    {
                        array[i][k+1] = array[i][k];
                        array[i][k] = 0;
                    } else
                        if(array[i][k+1] == array[i][k] && free == true && array[i][k+1] != blocked)
                        {
                            array[i][k+1] *= 2;
                            array[i][k] = 0;
                            free = false;
                            blocked = array[i][k+1];
                        }
                }
            }
        }
    }
}

//Main functions
void Generate()
{
    if (!Is_full() && different)
    {
        int x, y, gen;
        do {
        x = rand() % 4;
        y = rand() % 4;
        } while (margin[x][y] != 0);

        gen = rand() % 3;
        switch (gen)
        {
        case 0:
        case 1: margin[x][y] = 2; break;
        case 2: margin[x][y] = 4; break;
        }
    }
}
void Print()
{
    system("clear");
    for (int i = 0; i < N; i++)
    {
        cout << "─────────────────" << endl << "|";
        for (int j = 0; j < N; j++)
            if (margin[i][j] != 0)
                cout << " " << margin[i][j] << " |";
            else
                cout << "   |";

        cout << endl;
    }
    cout << "─────────────────" << endl;
}
void Input()
{
    while (!pressed)
        if (kbhit())
        {
            choise = getchar();
            pressed = true;
        }
    pressed = false;

    int **temp = new int*[N];
    for (int i = 0; i < N; i++)
        temp[i] = new int[N];
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            temp[i][j] = margin[i][j];

    switch (choise)
    {
    case 'w': Margin_Up(margin);  break;
    case 's': Margin_Down(margin); break;
    case 'a': Margin_Left(margin); break;
    case 'd': Margin_Right(margin); break;
    case 'q': gameOver = true; break;
    default: break;
    }

    Compare(temp, margin);
}
void Start()
{
    srand(time(NULL));
    int x, y;

    x = rand() % 4;
    y = rand() % 4;
    margin[x][y] = 2;

    //Generate(margin);
    Print();
}
void Check()
{
    int **temp = new int*[N];
    for (int i = 0; i < N; i++)
        temp[i] = new int[N];
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            temp[i][j] = margin[i][j];
    int sum[N+1];
    sum[0] = Value(temp);
    cout << sum[0] << " ";

    Margin_Up(temp);
    sum[1] = Value(temp);

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            temp[i][j] = margin[i][j];
    Margin_Down(temp);
    sum[2] = Value(temp);

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            temp[i][j] = margin[i][j];
    Margin_Left(temp);
    sum[3] = Value(temp);

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            temp[i][j] = margin[i][j];
    Margin_Right(temp);
    sum[4] = Value(temp);

    cout << sum[1] << " " << sum[2] << " " << sum[3] << " " << sum[4] << endl;
    if (sum[0] == sum[1] && sum[0] == sum[2] && sum[0] == sum[3] && sum[0] == sum[4] && Is_full())
        gameOver = true;
}
void Victory()
{
    int index = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (margin[i][j] == 2048)
                index++;
    if (index)
        win = true;
}

int* Jarvis(int **array, int index, int *prev_max)
{
    if (index == 0)
    {
        int *result = new int[2];
        result[0] = Value(array);
        result[1] = J - index;
        return result;
    }

    int *max = new int[2];
    max[0] = Value(array);
    max[1] = J - index;
    if (max[0] == prev_max[0])
        max[1] = prev_max[1];

    int **size = new int*[N];
    int **temp = new int*[N];

    for (int i = 0; i < N; i++)
    {
        temp[i] = new int[N];
        size[i] = new int[2];
    }
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            temp[i][j] = array[i][j];
    Margin_Up(temp);
    size[0] = Jarvis(temp, index-1, max);

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            temp[i][j] = array[i][j];
    Margin_Down(temp);
    size[1] = Jarvis(temp, index-1, max);

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            temp[i][j] = array[i][j];
    Margin_Left(temp);
    size[2] = Jarvis(temp, index-1, max);

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            temp[i][j] = array[i][j];
    Margin_Right(temp);
    size[3] = Jarvis(temp, index-1, max);

    int best_size = 0;
    int best_size2 = 0;

    for (int i = 0; i < N; i++)
        if (size[i][0] > max[0])
        {
            max[0] = size[i][0];
            max[1] = size[i][1];
            best_size = i;
        } else if(size[i][0] == max[0])
            if(size[i][1] < max[1])
            {
                max[1] = size[i][1];
                best_size = i;
            }

    int largest_side_x = Big_x_side(array);
    int largest_side_y = Big_y_side(array);

    for (int i = 0; i < N; i++)
        if (i != best_size)
        {
            if (size[i][0] == size[best_size][0] && size[i][1] == size[best_size][1])
            {
                best_size2 = i;
                if (best_size != largest_side_x && best_size != largest_side_y)
                    if (best_size2 == largest_side_x || best_size2 == largest_side_y)
                    {
                        best_size = best_size2;
                        break;
                    }
            }
        }


    if (index == J)
    {
        //char temp_choise = choise;
        switch(best_size)
        {
        case 0: choise = 'w'; break;
        case 1: choise = 's'; break;
        case 2: choise = 'a'; break;
        case 3: choise = 'd'; break;
        default: break;
        }
       /* if (choise == temp_choise)
            switch(choise)
            {
            case 'w': choise = 's'; break;
            case 's': choise = 'w'; break;
            case 'a': choise = 'd'; break;
            case 'd': choise = 'a'; break;
            }*/
    }
    return max;
}
void JarvisInput()
{

    int* useless = new int[2];
    useless[0] = 0;
    useless[1] = 0;
    Jarvis(margin, J, useless);

    int **temp = new int*[N];
    for (int i = 0; i < N; i++)
        temp[i] = new int[N];
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            temp[i][j] = margin[i][j];

    switch (choise)
    {
    case 'w': Margin_Up(margin);  break;
    case 's': Margin_Down(margin); break;
    case 'a': Margin_Left(margin); break;
    case 'd': Margin_Right(margin); break;
    case 'q': gameOver = true; break;
    default: break;
    }

    Compare(temp, margin);
    if (!different && !Is_full())
         switch(choise)
         {
         case 'w': choise = 's'; break;
         case 's': choise = 'w'; break;
         case 'a': choise = 'd'; break;
         case 'd': choise = 'a'; break;
         }
    else return;
    switch (choise)
    {
    case 'w': Margin_Up(margin);  break;
    case 's': Margin_Down(margin); break;
    case 'a': Margin_Left(margin); break;
    case 'd': Margin_Right(margin); break;
    case 'q': gameOver = true; break;
    default: break;
    }

    Compare(temp, margin);
    if (!different && !Is_full())
         switch(choise)
         {
         case 'w': choise = 'a'; break;
         case 's': choise = 'd'; break;
         case 'a': choise = 'w'; break;
         case 'd': choise = 's'; break;
         }
    else return;
    switch (choise)
    {
    case 'w': Margin_Up(margin);  break;
    case 's': Margin_Down(margin); break;
    case 'a': Margin_Left(margin); break;
    case 'd': Margin_Right(margin); break;
    case 'q': gameOver = true; break;
    }

    Compare(temp, margin);
    if (!different && !Is_full())
        switch(choise)
        {
        case 'w': choise = 's'; break;
        case 's': choise = 'w'; break;
        case 'a': choise = 'd'; break;
        case 'd': choise = 'a'; break;
        }
    else return;
    switch (choise)
    {
    case 'w': Margin_Up(margin);  break;
    case 's': Margin_Down(margin); break;
    case 'a': Margin_Left(margin); break;
    case 'd': Margin_Right(margin); break;
    case 'q': gameOver = true; break;
    }
}


int main()
{
    for (int i = 0; i < N; i++)
        margin[i] = new int [N];

    //while (!win)
    //{
        //gameOver = false;
        //different = true;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            margin[i][j] = 0;


    //margin[0][0] = 2;
    //margin[0][3] = 2;
    //margin[0][2] = 2;
    //margin[0][1] = 2;


    Start();
    //Generate();


    while (!gameOver)
    {
        Generate();
        Print();
        Victory();
        Check();
        if (gameOver)
            break;
        //Input();
        JarvisInput();
        //sleep(1);
    }
    //}
    cout << endl;
    return 0;
}


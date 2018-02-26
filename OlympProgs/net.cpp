#include <iostream>
using namespace std;
int check(int comp, bool* prev, int N, int* source, int* recieve,int pc)
{
    bool* taken = new bool[pc];
    for(int i = 0; i < pc; i++)
        taken[i] = prev[i];
    int Min = pc;
    int len = 0;
    int length = 0;
    for(int i = 0; i < N; i++)
        if(source[i] == (comp+1) && taken[recieve[i]-1] == false)
            {
                taken[recieve[i]-1] = true;
                len++;
            }
    int test = 0;
    for(int i = 0; i < pc; i++)
        if(taken[i] == true)
            test++;
    if(test == pc)
        return len;
    else
         for(int i = 0; i < N; i++)
            if(source[i] == (comp+1))
            {
                length = check((recieve[i]-1),taken,N,source,recieve,pc);
                if(length < Min)
                    Min = length;
            }
    delete[] taken;
    return Min+len;
}
int main()
{
    int comp;
    cin >> comp;
    int N;
    cin >> N;
    int* source = new int[N];
    int* recieve = new int[N];
    bool* take = new bool[comp];
    for(int i = 0; i < N; i++)
    {
        cin >> source[i];
        cin >> recieve[i];
    }
    for (int i = 0; i < comp; i++)
        take[i] = false;
    int length = 0;
    int Min = comp;
    int faster = 0;
    for(int i = 0; i < comp; i++)
    {
        take[i] = true;
        length = check(i,take,N,source,recieve,comp);
        if(length < Min)
        {
            faster = i+1;
            Min = length;
        }
        take[i] = false;
    }
    cout << faster << endl;
    delete[] take;
    delete[] source;
    delete[] recieve;
return 0;
}
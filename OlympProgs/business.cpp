#include <iostream>
using namespace std;
void check(int* mon, bool* obj, int prev, int N, int amo, bool* taken)
{
    bool* takennext = new bool[N];
    for(int i = 0; i < N; i++)
        takennext[i] = taken[i];
    if(amo > 1)
    {
        for(int i = 0; i < N; i++)
        {
            if(taken[i] == true)
            {
                takennext[i] = false;
                check(mon, obj, prev+mon[i], N, amo-1, takennext);
                takennext[i] = true;
            }
        }
    }else{
        int price = 0;
        for(int i = 0; i < N; i++)
            price += mon[i];
        for(int i = 0; i < N; i++)
        {
            if(taken[i] == true && (prev+mon[i]) <= price)
            {
                obj[mon[i]+prev-1] = true;
                cout << mon[i]+prev << endl;    
            }
        }
    }
    return;
}
int main()
{
    int N;
    int price = 0;
    cin >> N;
    int* mon = new int[N];
    for(int i = 0; i < N; i++)
    {
       cin >> mon[i];
       price += mon[i];
    }
    bool* obj = new bool[price];
    for(int i = 0; i < price; i++)
        obj[i] = false;
    bool* taken = new bool[N];
    for (int i = 0; i < N; i++)
        taken[i] = true;
    for (int i = 1; i <= N; i++)
        check(mon, obj, 0, N, i, taken);
    int result = 0;
    for (int i = 0; i < price; i++)
        if(obj[i] == false)
            result++;
    cout << result;

    
    return 0;
}
#include <iostream>
#include <cmath>
using namespace std;
int main()
{
  double X1,Y1,R1,X2,Y2,R2;
  cin >> X1 >> Y1 >> R1;
  cin >> X2 >> Y2 >> R2;
  int Max = R1;
  int Min = R2;
  if(R1 < R2)
    swap(R1,R2);
  double l;
  l = sqrt(pow((X2 - X1),2) + pow((Y2 - Y1),2));
  if(l == R1 + R2)
    cout << "1" << endl;//А снаружи В и касается
  else
    if(l > R1 + R2)
      cout << "0" << endl;//А снаружи В и не касается
    else
      if(l == 0 && R1 == R2)
        cout << "-1" << endl;//А совпадает с В
      else
        if(l == R1 - R2)
          cout << "1" << endl;//В внутри А и касается А
        else
          if(l == R2 - R1)
            cout << "1" << endl;//А внутри В и касается В
          else
            if(l > Max - Min)
              cout << "2" << endl;//А пересекается с В
            else
              if(R1 > R2)
                cout << "0" << endl;//В внутри А и не касается
              else
                cout << "0" << endl;//А внутри В и не касается
  return 0;
}

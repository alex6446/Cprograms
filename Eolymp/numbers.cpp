#include <iostream>
using namespace std;
int main()
{
	int n; 
	cin >> n;
	int res = 1;
	while(n /= 10)
		res++;
	cout << res << endl;
	return 0;
}

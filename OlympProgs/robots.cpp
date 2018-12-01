#include <iostream>
using namespace std;
int main()
{
	int ar, an, br, bn, N, time;
	cin >> ar >> an >> br >> bn >> N >> time;
	int mrob, mmake , lrob, lmake;
		mrob = ar;
		mmake = an;
		lrob = br;
		lmake = bn;
	if(((double)an/(double)ar) < ((double)bn/(double)br))
	{
		swap(mrob,lrob);
		swap(mmake,lmake);
	}
	for(int i = 1; i <= time; i++)
	{
		int temp = N;
		int year = 0;
		while((temp -= mrob) >= 0)
			year += mmake;
		while((temp -= lrob) >= 0)
			year += lmake;
		N += year;
	}
	cout << N;
	return 0;
}
#include <iostream>
using namespace std;
void choise(int left, int right)
{
	int answer;
	int middle = (left+right)/2;
	cout << middle << endl;
	cin >> answer;
	if(answer == 0)
		return;
	else if(answer == 1)
		choise(left,middle);
		else if(answer == 2)
				if(middle == right-1)
				{
					cout << right << endl;
					cin >> answer;
				}else
					choise(middle,right);
			else cin >> answer;
}
int main()
{
	int left,right;
	cin >> left >> right;
	choise(left,right);
	return 0;
}
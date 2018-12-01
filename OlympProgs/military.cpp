#include <iostream>
using namespace std;
int main()
{
	int N;
	cin >> N;
	int* arr = new int[N];
	for(int i = 0; i < N; i++)
		cin >> arr[i];
	bool swich;
	int length = 1;
	int maximum = 0;
	for(int i = 0; i < N-1; i++)
	{
		while(arr[i] == arr[i+1])
			i++;
		if (i+1 > N-1)
			break;
		if(arr[i] > arr[i+1])
			swich = true;
		else
			swich = false;
		for(int j = i; j < N-1; j++)
		{
			if(swich == true)
				if(arr[j] > arr[j+1])
				{
					length++;
					swich = false;
				} else break;
			  else
				if(arr[j] < arr[j+1])
				{
					length++;
					swich = true;
				} else break;
		}
		if(length > maximum)
			maximum = length;
		length = 1;
	}
	cout << maximum;
	return 0;
}
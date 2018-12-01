#include <iostream>
using namespace std;
void BubbleSort(int* arr,int N)
{
	for(int i = N-1; i > 0; i--)
		for (int j = 0; j < i; j++)
			if(arr[j] > arr[j+1])
				swap(arr[j],arr[j+1]);
}
int main()
{
	int N;
	cin >> N;
	int* have = new int[N];
	int* need = new int[N];
	for(int i = 0; i < N; i++)
	{
		cin >> have[i];
		cin >> need[i];
	}
	BubbleSort(have,N);
	BubbleSort(need,N);
	int index = 0;
	int buy = 0;
	for(int i = 0; i < N; i++)
	{
		for(; index < N; index++)
			if(need[i] <= have[index])
			{
				index++;
				break;
			}else 
				buy++;
	}
	cout << buy << endl;
	return 0;
}
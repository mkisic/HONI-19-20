#include <iostream>
using namespace std;

int N;

int main()
{
	cin >> N;
	cout << N / 2 << '+' << N / 2;
	if (N % 2 == 1) cout << "+1"; 
}
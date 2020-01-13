#include <bits/stdc++.h>
using namespace std;

int N;
int M;
int K[3];

int main()
{
    cin >> N;
    cin >> M;
    for (int i = 0; i < 3; i++) cin >> K[i];

    if (K[0] + K[1] + K[2] <= N) cout << 1 << '\n';
    else if (K[0] + K[1] <= N or K[1] + K[2] <= N) cout << 2 << '\n';
    else cout << 3 << '\n';
}
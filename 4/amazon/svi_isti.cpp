#include <bits/stdc++.h>
using namespace std;

int N;
int M;
int K;
int u_jednom;

int main()
{
    cin >> N;
    cin >> M;
    for (int i = 0; i < M; i++)
        cin >> K;

    u_jednom = N / K;
    cout << ceil((double)M / (double)u_jednom) << '\n';
}
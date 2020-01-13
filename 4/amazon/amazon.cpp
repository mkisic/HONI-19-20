#include <bits/stdc++.h>
using namespace std;

int N;
int M;
int K;
int weight;
int sol;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    cin >> M;
    for (int i = 0; i < M; i++)
    {
        cin >> K;
        weight += K;
        if (weight > N)
        {
            weight -= N;
            sol++;
        }
    }

    if (weight > 0) sol++;

    cout << sol << '\n';
}

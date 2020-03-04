#include <bits/stdc++.h>
using namespace std;

int main()
{
    int t = 1;
    while (1)
    {
        cout << "Test primjer: " << t << endl;
        t++;
        system("/home/fabijan/HONI-19-20/6/skandi/generator > primjer.txt");
        system("/home/fabijan/HONI-19-20/6/skandi/fabijan_druga_parcijala < primjer.txt > brut.txt");
        system("/home/fabijan/HONI-19-20/6/skandi/skandi_paljak < primjer.txt > moj.txt");
        if (system("diff -w brut.txt moj.txt"))
        {
            cout << "KRIVO" << endl;
            return 0;
        }
    }
}

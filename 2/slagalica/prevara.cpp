#include <bits/stdc++.h>
using namespace std;

#define REP(i, a, b) for(int i = a; i < b; i++)

int n;

vector <pair <int, bool> > izb, udub;
vector <int> rj;

bool poc, kraj;
int poca, kraja;

void nemoguce()
{
    printf("-1\n");
    exit(0);
    return;
}

int main()
{
    scanf("%d", &n);
    int x, a;
    REP(i, 0, n)
    {
        scanf("%d%d", &x, &a);
        if(x == 5 || x == 6) poca = a;
        else if(x == 7 || x == 8) kraja = a;
        if(x == 5) poc = 1;
        else if(x == 7) kraj = 1;
        else if(x == 1) izb.push_back(make_pair(a, 1));
        else if(x == 2) izb.push_back(make_pair(a, 0));
        else if(x == 3) udub.push_back(make_pair(a, 1));
        else if(x == 4) udub.push_back(make_pair(a, 0));
    }
    sort(izb.begin(), izb.end());
    sort(udub.begin(), udub.end());
    reverse(izb.begin(), izb.end());
    reverse(udub.begin(), udub.end());
    bool treba = !poc;
    while((int)izb.size() || (int)udub.size())
    {
        if(treba)
        {
            if((int)izb.size() == 0) nemoguce();
            rj.push_back(izb.back().first);
            if(izb.back().second) treba = 0;
            izb.pop_back();
        }
        else
        {
            if((int)udub.size() == 0) nemoguce();
            rj.push_back(udub.back().first);
            if(!udub.back().second) treba = 1;
            udub.pop_back();
        }
    }
    if(treba != kraj) nemoguce();
    printf("%d ", poca);
    REP(i, 0, (int)rj.size())
    {
        printf("%d ", rj[i]);
    }
    printf("%d\n", kraja);
    return 0;
}

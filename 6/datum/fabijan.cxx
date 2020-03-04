#include <bits/stdc++.h>
using namespace std;

int N;
string s;
vector <string> v;

int day(string x)
{
    return stoi(x.substr(0, 2));
}
int month(string x)
{
    return stoi(x.substr(2, 2));
}
int monthT(string x)
{
    return stoi(x.substr(3, 2));
}
int year(string x)
{
    return stoi(x.substr(4, 4));
}
int yearT(string x)
{
    return stoi(x.substr(6, 4));
}
string fill(string x)
{
    string a;
    if (x.size() == 1) 
        a = "000";
    if (x.size() == 2)
        a = "00";
    if (x.size() == 3)
        a = "0";
    if (x.size() == 4)
        a = "";
    a += x;
    return a;
}
bool check(string x)
{
    if (day(x) < 1 or day(x) > 31) return 0;
    if (month(x) < 1 or month(x) > 12) return 0;
    if (month(x) == 4 or month(x) == 6 or month(x) == 9 or month(x) == 11) 
        if (day(x) > 30) return 0;
    if (month(x) == 2)
    {
        if (!(year(x) % 4)) 
            {if (day(x) > 29) return 0;}
        else 
            {if (day(x) > 28) return 0;}
    }
    return 1;
}
bool cmp(string x, string y)
{
    return yearT(x) < yearT(y);
}
bool lessEqual(string x, string y)
{
    if (yearT(x) != yearT(y)) return yearT(x) < yearT(y);
    if (monthT(x) != monthT(y)) return monthT(x) < monthT(y);
    return day(x) <= day(y);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    for (int i = 1; i <= 9999; i++)
    {
        string y = fill(to_string(i));
        string a = y;
        reverse(y.begin(), y.end());
        a += y;
        if (check(a)) 
        {
            a = a.substr(0, 2) + '.' + a.substr(2, 2) + '.' + a.substr(4, 4) + '.';
            v.push_back(a);
        }
    }
    sort(v.begin(), v.end(), cmp);

    cin >> N;

    for (int i = 0; i < N; i++)
    {
        cin >> s;
        int low = 0, high = v.size() - 1;
        while (high - low)
        {
            int mid = (low + high) / 2;
            if (lessEqual(v[mid], s)) low = mid + 1;
            else high = mid;
        }
        cout << v[low] << '\n';
    }
}
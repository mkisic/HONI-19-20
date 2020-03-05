#include <bits/stdc++.h>

using namespace std;

vector<int> dates;
int q;
string date;

int mj[12] = {31,29,31,30,31,30,31,31,30,31,30,31};

bool palin(string s)
{
	for(int i = 0; i < s.size(); i++)
		if(s[i] == '.')
			s.erase(s.begin() + i);
	string x = s;
	reverse(x.begin(), x.end());
	return x == s;
}

int main()
{
	clock_t begin, end;
	double time_spent;
	begin = clock();
	cin >> q;
	while(q--)
	{
		cin >> date;
		int day = (date[0] - '0') * 10 + date[1] - '0';
		do
		{
			day++;
			date[0] = char(day/10 + '0');
			date[1] = char(day % 10 + '0');
		}
		while(!palin(date));
		cout << date << endl;
	}
	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	//cout << endl<< time_spent;
	return 0;
}


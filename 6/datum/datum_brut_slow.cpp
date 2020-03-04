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
		int month = (date[3] - '0') * 10 + date[4] - '0';
		int year = (date[6] - '0') * 1000 + (date[7] - '0') * 100 + (date[8] - '0') * 10 + date[9] - '0';
		do
		{
			day++;
			if(month == 13)
			{
				day = 1;
				month = 1;
				year = year + 1;
				date[6] = char(year / 1000 + '0');
				date[7] = char((year / 100) % 10 + '0');
				date[8] = char((year / 10) % 10 + '0');
				date[9] = char(year % 10 + '0');
				
				date[3] = char(month / 10 + '0');
				date[4] = char(month % 10 + '0');
			}
			if(day > mj[month - 1])
			{
				month++;
				date[3] = char(month / 10 + '0');
				date[4] = char(month % 10 + '0');
				day = 1;
			}
			date[0] = char(day / 10 + '0');
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


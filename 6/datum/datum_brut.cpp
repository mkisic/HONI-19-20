#include <bits/stdc++.h>

using namespace std;

vector<int> dates;
int q;
string date;

int mj[12] = {31,29,31,30,31,30,31,31,30,31,30,31};

bool palin(int y)
{
	int day = (y % 10) * 10 + (y % 100) / 10;
	int month = y / 1000 + ((y / 100) % 10) * 10;
	return (day <= mj[month - 1] && day != 0 && month != 0 && month <= 12);
}

string ispis(int y)
{
	string ret = "";
	ret += (y % 10 + '0');
	ret += (y / 10) % 10 + '0';
	ret += ".";
	ret += (y / 100) % 10 + '0';
	ret += y / 1000 + '0';
	ret += ".";
	ret += (y / 1000) + '0';
	ret += (y / 100) % 10 + '0';
	ret += (y / 10) % 10 + '0';
	ret += y % 10 + '0';
	
	return ret;
}

bool kasnije(string a, string b)
{
	int mja = (a[3]- '0') * 10 + a[4] - '0';
	int mjb = (b[3]- '0') * 10 + b[4] - '0';
	int daa = (a[0]- '0') * 10 + a[1] - '0';
	int dab = (b[0]- '0') * 10 + b[1] - '0';
	if(mja > mjb)
		return true;
	if(mja == mjb)
	{
		if(daa > dab)
			return true;
		return false;
	}
	return false;
}

int main()
{
	clock_t begin, end;
	double time_spent;
	begin = clock();
	for(int i = 1; i < 10000; i++)
		if(palin(i))
			dates.push_back(i);
	cin >> q;
	while(q--)
	{
		cin >> date;
		int year = (date[6] - '0') * 1000 + (date[7] - '0') * 100 + (date[8] - '0') * 10 + date[9] - '0';
		for(int i = 0; i < 366; i++)
		{
			if(year == dates[i])
			{
				string pal = ispis(year);
				if(kasnije(pal, date))
					cout << pal << "." << endl;
				else
					cout << ispis(dates[i + 1]) << "." << endl;
				break;
			}
			else if(year < dates[i])
			{
				cout << ispis(dates[i]) << "." << endl;
				break;
			}
		}
	}
	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	//cout << endl<< time_spent;
	return 0;
}


#include <bits/stdc++.h>

using namespace std;

int main()
{
	for(int i = '1'; i < '4'; i++)
	{
		string idx = "";
		idx += i;
		string nameIn = "test\\radio.dummy.in." + idx;
		string nameOut = "test\\radio.dummy.out." + idx;
		string del = "del " + nameOut;
		system(del.c_str());
		string cmd = "Karlo1.py < " + nameIn + " > " + nameOut;
		cout << "Executing... " << cmd << endl;
		system(cmd.c_str());
	}
	for(char i = '1'; i < '7'; i++)
	{
		string idx = "";
		idx += i;
		string nameIn = "test\\radio.in." + idx;
		string nameOut = "test\\radio.out." + idx;
		string del = "del " + nameOut;
		system(del.c_str());
		string cmd = "Karlo1.py < " + nameIn + " > " + nameOut;
		cout << "Executing... " << cmd << endl;
		system(cmd.c_str());
	}
	return 0;
}


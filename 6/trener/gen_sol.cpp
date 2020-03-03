#include <bits/stdc++.h>

using namespace std;

string zadatak = "trener";

int main()
{
	for(char i = '1'; i <= '3'; i++)
	{
		string idx;
		idx += i;
		string nameIn = "test\\" + zadatak + ".dummy.in." + idx;
		string nameOut = "test\\" + zadatak + ".dummy.out." + idx;
		string del = "del " + nameOut;
		system(del.c_str());
		string cmd = "Trener.exe < " + nameIn + " > " + nameOut;
		cout << "Executing... " << cmd << endl;
		system(cmd.c_str());
	}
	for(int i = 1; i <= 10; i++)
	{
		string idx = "10";
		if(i != 10)
			idx = char(i + '0');
		string nameIn = "test\\" + zadatak + ".in." + idx;
		string nameOut = "test\\" + zadatak + ".out." + idx;
		string del = "del " + nameOut;
		system(del.c_str());
		string cmd = "Trener.exe < " + nameIn + " > " + nameOut;
		cout << "Executing... " << cmd << endl;
		system(cmd.c_str());
	}
	return 0;
}


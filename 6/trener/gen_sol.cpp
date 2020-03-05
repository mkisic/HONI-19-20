#include <bits/stdc++.h>

using namespace std;

string zadatak = "trener";
string tasks[] = {"1a","1b","1c","1d","2a","2b","2c","2d","2e","2f","3a","3b","3c","3d","3e","3f","3g","3h","3i","3j"};

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
	for(int i = 0; i < 20; i++)
	{
		string idx;
			idx = tasks[i];
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


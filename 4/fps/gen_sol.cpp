#include <bits/stdc++.h>

using namespace std;

int main()
{
	for(int i = '1'; i < '4'; i++)
	{
		string idx = "";
		idx += i;
		string nameIn = "test\\FPS.dummy.in." + idx;
		string nameOut = "test\\FPS.dummy.out." + idx;
		string del = "del " + nameOut;
		system(del.c_str());
		string cmd = "sol.py < " + nameIn + " > " + nameOut;
		cout << "Executing... " << cmd << endl;
		system(cmd.c_str());
	}
	for(char i = '1'; i < '6'; i++)
	{
		string idx = "";
		idx += i;
		string nameIn = "test\\FPS.in." + idx;
		string nameOut = "test\\FPS.out." + idx;
		string del = "del " + nameOut;
		system(del.c_str());
		string cmd = "sol.py < " + nameIn + " > " + nameOut;
		cout << "Executing... " << cmd << endl;
		system(cmd.c_str());
	}
	return 0;
}


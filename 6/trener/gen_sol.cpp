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
		string nameOut = "test\\" + zadatak + ".dummy.out_kvadrat." + idx;
		string del = "del " + nameOut;
		system(del.c_str());
		string cmd = "Trener_kvadrat.exe < " + nameIn + " > " + nameOut;
		cout << "Executing... " << cmd << endl;
		system(cmd.c_str());
	}
	for(char i = 'a'; i <= 'j'; i++)
	{
		string idx = "1";
		idx += i;
		string nameIn = "test\\" + zadatak + ".in." + idx;
		string nameOut = "test\\" + zadatak + ".out_kvadrat." + idx;
		string del = "del " + nameOut;
		system(del.c_str());
		string cmd = "Trener_kvadrat.exe < " + nameIn + " > " + nameOut;
		cout << "Executing... " << cmd << endl;
		system(cmd.c_str());
	}
	return 0;
}


#include <bits/stdc++.h>

using namespace std;

int main()
{
	for(int i = '1'; i < '4'; i++)
	{
		string idx = "";
		idx += i;
		string nameIn = "test\\duel.dummy.in." + idx;
		string nameOut = "test\\duel.dummy.out." + idx;
		string del = "del " + nameOut;
		system(del.c_str());
		string cmd = "Duel_Franic.exe < " + nameIn + " > " + nameOut;
		cout << "Executing... " << cmd << endl;
		system(cmd.c_str());
	}
	for(char i = '0'; i <= '9'; i++)
	{
		string idx = "";
		const string deset = "10";
		if(i < '9')
			idx += (char)(i + 1);
		else
			idx = "10";
		string nameIn = "test\\duel.in." + idx;
		string nameOut = "test\\duel.out." + idx;
		string del = "del " + nameOut;
		system(del.c_str());
		string cmd = "Duel_Franic.exe < " + nameIn + " > " + nameOut;
		cout << "Executing... " << cmd << endl;
		system(cmd.c_str());
	}
	return 0;
}


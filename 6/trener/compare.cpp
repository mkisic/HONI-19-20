#include <bits/stdc++.h>

using namespace std;

string tasks[] = {"1a","1b","1c","1d","2a","2b","2c","2d","2e","2f","2g","3a","3b","3c","3d","3e","3f","3g","3h","3i","3j","3k"};


int main()
{
	for(char i = 0; i <= 20; i++)
	{
		string cmd = "fc test\\trener.out_brut." + tasks[i];
		cmd += " test\\trener.out." + tasks[i];
		system(cmd.c_str());
	}
	return 0;
}


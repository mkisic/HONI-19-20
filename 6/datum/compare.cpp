#include <bits/stdc++.h>

using namespace std;

int main()
{
	for(char i = 'a'; i <= 'j'; i++)
	{
		string cmd = "fc test\\datum.out_brut.1";
		cmd += i;
		cmd += " test\\datum.out.1";
		cmd += i;
		system(cmd.c_str());
	}
	return 0;
}


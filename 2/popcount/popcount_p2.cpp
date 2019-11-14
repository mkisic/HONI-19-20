#include <bits/stdc++.h>

using namespace std;

#define TRACE(x) cerr << #x << " " << x << endl
#define FOR(i, a, b) for (int i = (a); i < int(b); ++i)
#define REP(i, n) FOR(i, 0, n)
#define _ << " " <<

typedef long long llint;

int n, k;

vector<string> code;

int main(void) {
  cin >> n >> k;
  for (int i = 0; i < n; i += 4) {
    string ahole = "(A&(((1<<" + to_string(n) + ")-1)-(";
    for (int j = i; j < min(i + 4, n) - 1; ++j)
      ahole += "(1<<" + to_string(j) + ")+(";
    int jj = min(i + 4, n) - 1;
    ahole += "1<<" + to_string(jj);
    for (int j = i; j < min(i + 4, n); ++j) ahole += ")";
    ahole += "))";

    string command = "A=(" + ahole + "+(";
    for (int j = i; j < min(i + 4, n) - 1; ++j)
      command += "((A&(1<<" + to_string(j) + "))>>" + to_string(j) + ")+(";
    command += "(A&(1<<" + to_string(jj) + "))>>" + to_string(jj);
    for (int j = i; j < min(i + 4, n); ++j) command += ")";
    command += ")";
    code.push_back(command);
  }

  cout << (int) code.size() << "\n";
  for (string &line : code) cout << line << "\n";
  return 0;
}

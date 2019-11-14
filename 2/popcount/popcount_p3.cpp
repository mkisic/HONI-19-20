#include <bits/stdc++.h>

using namespace std;

#define TRACE(x) cerr << #x << " " << x << endl
#define FOR(i, a, b) for (int i = (a); i < int(b); ++i)
#define REP(i, n) FOR(i, 0, n)
#define _ << " " <<

typedef long long llint;

const int MOD = 1e9 + 7;

int n, k;

string gen_mask(string x, int len) {
  string ret = "(A&(";
  int ii = 0;
  for (; ii + len < n; ii += len)
    ret += "(" + x + "<<" + to_string(ii) + ")|(";
  ret += x + "<<" + to_string(ii);
  for (int i = 0; i < n; i += len) ret += ")";
  ret += ")";
  return ret;
}

int main(void) {
  cin >> n >> k;
  vector<string> code;
  for (int i = 0; (1 << i) < n; ++i) {
    string px = "((1<<" + to_string(i + 1) + ")-1)";
    string qx = "(" + px + "<<(1<<" + to_string(i) + "))";
    string P = gen_mask(px, 1 << (i + 1));
    string Q = gen_mask(qx, 1 << (i + 1));
    string command = "A=(";
    command += P + "+(" + Q + ">>(1<<" + to_string(i) + ")))";
    code.push_back(command);
  }

  cout << (int) code.size() << "\n";
  for (const string &line : code)
    cout << line << "\n";

  return 0;
}

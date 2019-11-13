#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

#define TRACE(x) cerr << #x << " = " << x << endl
#define FOR(i, a, b) for(int i = (a); i < (b); i++)
#define REP(i, n) FOR(i, 0, n)

typedef long long int llint;

typedef pair<int, int> par;

#define X first
#define Y second

string zbroji(string a, string b) {
  if(a.size() > b.size()) swap(a, b);
  reverse(a.begin(), a.end());
  while(a.size() < b.size()) a.push_back('0');
  reverse(b.begin(), b.end());
  int dalje = 0;
  string ret;
  REP(i, (int) a.size()) {
    int x = a[i] - '0';
    int y = b[i] - '0';
    int sum = x + y + dalje;
    int z = sum % 10;
    dalje = sum / 10;
    ret.push_back('0' + z);
  }
  if(dalje != 0) ret.push_back('0' + dalje);
  reverse(ret.begin(), ret.end());
  return ret;
}

string puta_dva(string a) {
  reverse(a.begin(), a.end());
  string ret;
  int dalje = 0;
  REP(i, (int) a.size()) {
    int x = a[i] - '0';
    int mul = 2 * x + dalje;
    int z = mul % 10;
    dalje = mul / 10; 
    ret.push_back('0' + z);
  }
  if(dalje != 0) ret.push_back('0' + dalje);
  reverse(ret.begin(), ret.end());
  return ret;
}

string vrati_decimalni(string x) {
  reverse(x.begin(), x.end());
  string ret;
  string a = "1";
  REP(i, (int) x.size()) {
    if(x[i] == '1')
      ret = zbroji(ret, a);
    a = puta_dva(a);
  }
  return ret;
}

string generiraj(int n, int k) {
  string ret;
  while(true) {
    REP(j, k) {
      ret.push_back('1');
      if((int) ret.size() == n) {
        reverse(ret.begin(), ret.end());
        return ret;
      }
    }
    REP(j, k) {
      ret.push_back('0');
      if((int) ret.size() == n) {
        reverse(ret.begin(), ret.end());
        return ret;
      }
    }
  }
}

string kontra(string a) {
  string ret;
  REP(i, (int) a.size())
    ret.push_back('0' + 1 - (a[i] - '0'));
  return ret;
}

string int_to_string(int x) {
  string ret;
  while(x) {
    ret.push_back('0' + (x % 10));
    x /= 10;
  }
  reverse(ret.begin(), ret.end());
  if(ret.empty()) ret = "0";
  return ret;
}

int main() {
  int n, k;
  cin >> n >> k;
  vector<string> ispis;
  int pot = 1;
  int i = 0;
  while(pot < n) {
    string a = generiraj(n, pot);
    string b = kontra(a);
    a = vrati_decimalni(a);
    b = vrati_decimalni(b);
    string s = "A=((A&" + a + ")+((A&" + b + ")>>(1<<" + int_to_string(i) + ")))";
    ispis.push_back(s);
    pot *= 2;
    i++;
  }
  cout << ispis.size() << endl;
  for(auto s : ispis)
    cout << s << endl;
  return 0;
}

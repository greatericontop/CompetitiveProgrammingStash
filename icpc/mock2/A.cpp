#include <bits/stdc++.h>

using namespace std;

int main() {
  int d;
  cin >> d;
  cout << d - __gcd(d, 10) << endl;
}
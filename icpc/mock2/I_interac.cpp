#include <bits/stdc++.h>
using namespace std;



int main() {
  //mt19937_64 rng(11);
  mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

  int n = 20;
  string s(n, '.');
  s[0] = 'a' + (rng() % 26);
  for (int i = 1; i < n; i++) {
    if (rng() % 3 == 0) {
      s[i] = 'a' + (rng() % 26);
    } else {
      s[i] = s[i-1];
    }
  }
  int offset = rng() % n;
  string t(n, '.');
  for (int i = 0; i < n; i++) {
    t[i] = s[(i + offset) % n];
  }
  fprintf(stderr, "s = %s, t = %s\n", s.c_str(), t.c_str());


  cout << n << endl;

  int queries_used = 0;
  while (true) {
    string ty;
    cin >> ty;
    if (ty == "!") {
      int ans;  cin >> ans;
      if (ans != offset) {
        fprintf(stderr, "WA wrong answer, you printed %d but answer was %d\n", ans, offset);
        return 5;
      }
      fprintf(stderr, "OK");
      return 0;
    } else if (ty == "?") {
      queries_used++;
      if (queries_used > 5*n) {
        fprintf(stderr, "WA too many qs");
        return 5;
      }
      int i, j;  cin >> i >> j;
      int ret = s[i-1] == t[j-1] ? 1 : 0;
      fprintf(stderr, "You asked s[%d]=%c t[%d]=%c, ans %d\n", i, s[i-1], j, t[j-1], ret);
      cout << ret << endl;
    } else {
      fprintf(stderr, "WA invalid q");
      return 5;
    }
  }



}
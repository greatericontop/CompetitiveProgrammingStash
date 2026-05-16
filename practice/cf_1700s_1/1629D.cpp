#include <bits/stdc++.h>
using namespace std;


#define GREATERIC_DEBUG


#ifdef GREATERIC_DEBUG
  #define PRINTVEC(vec) do { \
    fprintf(stderr, "%s:  ", #vec); \
    for (const auto& _x : (vec))  fprintf(stderr, "%d ", _x); \
    fprintf(stderr, "\n"); \
  } while (0)
  #define PRINTMAP(map) do { \
    fprintf(stderr, "%s:  ", #map); \
    for (const auto& _p : (map))  fprintf(stderr, "%d->%d ", _p.first, _p.second); \
    fprintf(stderr, "\n"); \
  } while (0)
  #define DEBUGFOREACH(vec, stmt) do { \
    fprintf(stderr, "%s:  ", #vec); \
    for (const auto& x : (vec)) { \
      stmt; \
    } \
  } while (0)
#else
  #define fprintf(...) // no-op
  #define PRINTVEC(...) // no-op
  #define PRINTMAP(...) // no-op
#endif
#define long long long
#define pb push_back
using pairii = pair<int, int>;
using pairll = pair<long, long>;










void solve() {
  int n;
  cin >> n;
  vector<string> a(n);
  for (int i = 0; i < n; i++)  cin >> a[i];

  set<string> strings;
  set<string> strings_doubleletter;

  for (int i = n-1; i >= 0; i--) {
    string s = a[i];
    int l = s.length();
    if (l == 1) {
      cout << "YES\n";
      return;
    } else if (l == 2) {
      if (s[0] == s[1]) {
        cout << "YES\n";
        return;
      }
      string key;
      key += s[1]; key += s[0];
      if (strings_doubleletter.count(key)) {
        cout << "YES\n";
        return;
      }
      strings_doubleletter.insert(s);
    } else {
      if (s[0] == s[2]) {
        cout << "YES\n";
        return;
      }
      string k1;
      k1 += s[2]; k1 += s[1]; k1 += s[0];
      if (strings.count(k1)) {
        cout << "YES\n";
        return;
      }
      string k2;
      k2 += s[1]; k2 += s[0];
      if (strings.count(k2)) {
        cout << "YES\n";
        return;
      }
      strings_doubleletter.insert(s.substr(1, 2));
    }
    strings.insert(s);
  }

  cout << "NO\n";
}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--)  solve();
  return 0;
}

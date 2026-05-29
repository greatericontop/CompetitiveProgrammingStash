#include <bits/stdc++.h>
using namespace std;


#define GREATERIC_DEBUG


#ifdef GREATERIC_DEBUG
  #define PRINTVEC(vec) do { \
    fprintf(stderr, "%s:  ", #vec); \
    for (const auto& _x : (vec))  fprintf(stderr, "%d ", _x); \
    fprintf(stderr, "\n"); \
  } while (0)
  #define PRINTVECL(vec) do { \
    fprintf(stderr, "%s:  ", #vec); \
    for (const auto& _x : (vec))  fprintf(stderr, "%lld ", _x); \
    fprintf(stderr, "\n"); \
  } while (0)
  #define PRINTMAP(map) do { \
    fprintf(stderr, "%s:   ", #map); \
    for (const auto& _p : (map))  fprintf(stderr, "%d->%d  ", _p.first, _p.second); \
    fprintf(stderr, "\n"); \
  } while (0)
  #define PRINTVECP(vec) do { \
    fprintf(stderr, "%s:   ", #vec); \
    for (const auto& _p : (vec))  fprintf(stderr, "[%d %d],  ", _p.first, _p.second); \
    fprintf(stderr, "\n"); \
  } while (0)
  #define PRINTVECPL(vec) do { \
    fprintf(stderr, "%s:   ", #vec); \
    for (const auto& _p : (vec))  fprintf(stderr, "[%lld %lld],  ", _p.first, _p.second); \
    fprintf(stderr, "\n"); \
  } while (0)
#else
  #define fprintf(...)
  #define PRINTVEC(...)
  #define PRINTVECL(...)
  #define PRINTMAP(...)
  #define PRINTVECP(...)
  #define PRINTVECPL(...)
#endif
#define long long long
#define pb push_back
#define LONG(x) ((long) (x))
#define INT(x) ((int) (x))
#define FORI(x) for (int i = 0; i < (x); i++)
#define FORI1(x) for (int i = 1; i <= (x); i++)
using pairii = pair<int, int>;
using pairll = pair<long, long>;
using AdjList = vector<vector<int>>;
// Positive numbers only
constexpr static inline int ceildiv(int a, int b) { return (a + b - 1) / b; }
constexpr static inline long ceildivl(long a, long b) { return (a + b - 1) / b; }
//constexpr static long MOD = 1'000'000'007LL;
//constexpr static long MOD =   998'244'353LL;










void solve() {
  int n, kmax;
  cin >> n >> kmax;
  string s, t;
  cin >> s >> t;

  vector<int> jumps(n);
  int j = n-1;
  for (int i = n-1; i >= 0; i--) {
    if (j > i)  j = i;
    while (j >= 0 && s[j] != t[i])  j--;
    if (j < 0) {
      cout << -1 << "\n";
      return;
    }
    jumps[i] = j;
  }
  vector<int> targets(n);
  for (int i = 0; i < n; i++)  targets[i] = i;  //initialize
  for (int i = 0; i < n; i++)  targets[jumps[i]] = i;  //target to the latest position to jump to


  vector<string> ops;  ops.reserve(kmax+10);
  for (int o = 0; ; o++) {
    bool is_done = true;
    for (int i = 0; i < n; i++) {
      if (s[i] != t[i]) {
        is_done = false;
        break;
      }
    }
    if (is_done)  break;
    if (o == kmax) {
      cout << -1 << "\n";
      return;
    }

    string s_new(n, '.');
    for (int i = n-2; i >= 0; i--) {
      if (targets[i] > i) {
        s_new[i+1] = s[i];
        targets[i+1] = targets[i];
        targets[i] = i;
      } else {
        s_new[i+1] = s[i+1];
      }
    }
    s_new[0] = s[0];

    ops.push_back(s_new);
    s = s_new;
  }

  cout << ops.size() << "\n";
  for (const auto& op : ops)  cout << op << "\n";

}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  cin >> t;
  while (t--)  solve();
  return 0;
}

/*  -fsanitize=undefined -fsanitize=address -fno-sanitize-recover -Wall -Werror -Wextra -Wshadow -Wfloat-equal
    -Wno-error=unused-variable -Wno-error=unused-parameter -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2 -O1  */

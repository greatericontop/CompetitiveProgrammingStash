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









bool is_rbs(string str) {
  int balance = 0;
  for (char c : str) {
    if (c == '(')  balance++;
    else  balance--;
    if (balance < 0)  return false;
  }
  if (balance != 0)  return false;
  return true;
}

void solve() {
  string s;
  cin >> s;
  int l = 0, r = 0, q = 0;
  for (char c : s) {
    if (c == '(')  l++;
    else if (c == ')')  r++;
    else  q++;
  }

  int n = l + r + q;
  assert(n % 2 == 0);
  int goal = n / 2;
  int extra_l = goal - l;
  int extra_r = goal - r;
  if (extra_l == 0 || extra_r == 0) {
    cout << "YES\n";
    return;
  }

  string replace;
  for (int i = 0; i < extra_l; i++)  replace += '(';
  for (int i = 0; i < extra_r; i++)  replace += ')';

  string s1 = s;
  int p = 0;
  for (int i = 0; i < n; i++) {
    if (s[i] == '?') {
      s1[i] = replace[p];
      p++;
    }
  }
  string s2 = s;
  p = 0;
  swap(replace[extra_l-1], replace[extra_l]);
  for (int i = 0; i < n; i++) {
    if (s[i] == '?') {
      s2[i] = replace[p];
      p++;
    }
  }

  assert(is_rbs(s1));
  if (is_rbs(s2)) {
    cout << "NO\n";
  } else {
    cout << "YES\n";
  }

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

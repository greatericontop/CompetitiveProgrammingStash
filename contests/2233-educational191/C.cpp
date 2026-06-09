#include <bits/stdc++.h>
using namespace std;


//#define GREATERIC_DEBUG


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









int calc_rbs(const string& s) {
  // greedy
  int chars_used = 0;
  int balance = 0;
  for (char c : s) {
    if (c == '(') {
      chars_used++;
      balance++;
    } else {
      if (balance > 0) {
        chars_used++;
        balance--;
      }
    }
  }
  return chars_used - balance;  //if extra ( leftover
}


void solve() {
  int n, k;
  cin >> n >> k;
  string s;
  cin >> s;
  int leftct = 0, rightct = 0;
  for (char c : s) {
    if (c == '(')  leftct++;
    else  rightct++;
  }

  int best_rbs = INT_MAX;
  string best_keystring;
  for (int front = 0; front <= k; front++) {
    int back = k - front;
    if (front > leftct || back > rightct)  continue;  //const factor optimization
    int front_temp = front;
    // delete front, back
    string keystring(n, '0');
    for (int i = 0; i < n; i++) {
      if (s[i] == '(') {
        if (front_temp > 0) {
          keystring[i] = '1';
          front_temp--;
        } else {
          break;
        }
      }
    }
    for (int i = n-1; i >= 0; i--) {
      if (s[i] == ')') {
        if (back > 0) {
          keystring[i] = '1';
          back--;
        } else {
          break;
        }
      }
    }
    string s_new;
    for (int i = 0; i < n; i++) {
      if (keystring[i] == '0')  s_new += s[i];
    }
    fprintf(stderr, "front %d, back %d, s_new %s\n", k-front, front, s_new.c_str());
    int rbs = calc_rbs(s_new);
    if (rbs < best_rbs) {
      best_rbs = rbs;
      best_keystring = keystring;
    }
  }

  cout << best_keystring << "\n";


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

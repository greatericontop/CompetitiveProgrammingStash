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









string inttobinstr(int x) {
  string ret;
  while (x > 0) {
    ret += ((x % 2 == 0) ? '0' : '1');
    x /= 2;
  }
  reverse(ret.begin(), ret.end());
  return ret;
}

void solve() {
  int n;
  cin >> n;
  vector<int> a(n);
  FORI(n)  cin >> a[i];

  int i_start = 0;
  while (i_start < n && a[i_start] == -1)  i_start++;
  int i_end = n-1;
  while (i_end >= 0 && a[i_end] == -1)  i_end--;

  if (i_start == n) {
    for (int i = 0; i < n; i++) {
      cout << ((i % 2 == 0) ? 1 : 2) << " ";
    }
    cout << "\n";
    return;
  }

  vector<int> next_nonzero(n, -1);
  next_nonzero[i_end] = a[i_end];
  for (int i = i_end-1; i >= i_start; i--) {
    if (a[i] == -1) {
      next_nonzero[i] = next_nonzero[i+1];
    } else {
      next_nonzero[i] = a[i];
    }
  }
  PRINTVEC(next_nonzero);

  vector<int> ans(n, -1);
  for (int i = i_start; i <= i_end; i++) {
    if (a[i] != -1) {
      ans[i] = a[i];
      // check for validity
      if (i > i_start) {
        int prev = ans[i-1];
        int cur = ans[i];
        if (!(
            cur == prev/2
            || cur == prev*2
            || cur == prev*2 + 1
            )) {
          PRINTVEC(ans);
          fprintf(stderr, "invalid at i=%d\n", i);
          cout << "-1\n";
          return;
        }
      }
    } else {
      // Greedily try to turn a[i] closer to next_nonzero[i]
      string prev = inttobinstr(ans[i-1]);
      string goal = inttobinstr(next_nonzero[i]);
      fprintf(stderr, "i=%d, prev=%s, goal=%s\n", i, prev.c_str(), goal.c_str());
      // if prev is a prefix of goal, then add to prev
      if (goal == prev) {
        prev += '0';
      } else if (goal.substr(0, prev.size()) == prev) {
        prev += goal[prev.size()];
      } else {
        // remove last char of prev
        prev.pop_back();
      }
      ans[i] = stoi(prev, nullptr, 2);
    }
  }
  for (int i = i_start-1; i >= 0; i--) {
    if ((i_start-1) % 2 == i % 2) {
      ans[i] = ans[i+1] * 2;
    } else {
      ans[i] = ans[i+1] / 2;
    }
  }
  for (int i = i_end+1; i < n; i++) {
    if ((i_end+1) % 2 == i % 2) {
      ans[i] = ans[i-1] * 2;
    } else {
      ans[i] = ans[i-1] / 2;
    }
  }

  for (int x : ans)  cout << x << " ";
  cout << "\n";

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

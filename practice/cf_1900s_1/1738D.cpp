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










void solve() {
  int n;
  cin >> n;
  vector<int> b(n+1);
  FORI1(n)  cin >> b[i];
  vector<vector<int>> bi_to_index(n+2);
  for (int i = 1; i <= n; i++) {
    bi_to_index[b[i]].pb(i);
  }

  vector<int> ans;
  vector<int> currently_active_i;
  int kmin = 0, kmax = n;
  bool current_is_greater;

  if (bi_to_index[0].empty()) {
    assert(!bi_to_index[n+1].empty());
    current_is_greater = false;
    for (int i : bi_to_index[n+1]) {
      currently_active_i.pb(i);
      kmin = max(kmin, i);
    }
  } else if (bi_to_index[n+1].empty()) {
    assert(!bi_to_index[0].empty());
    current_is_greater = true;
    for (int i : bi_to_index[0]) {
      currently_active_i.pb(i);
      kmax = min(kmax, i-1);
    }
  } else  assert(0);


  while (true) {
    PRINTVEC(ans);
    PRINTVEC(currently_active_i);
    int last_i = -1;
    if (ans.size() + currently_active_i.size() == n) {
      for (int i : currently_active_i) {
        ans.pb(i);
      }
      break;
    }
    for (int i : currently_active_i) {
      if (!bi_to_index[i].empty()) {
        assert(last_i == -1);  //there should only be one
        last_i = i;
      }
    }
    assert(last_i != -1);
    fprintf(stderr, "  last_i (in currently_active_i): %d\n", last_i);
    for (int i : currently_active_i) {
      if (i != last_i)  ans.pb(i);
    }
    ans.pb(last_i);
    if (ans.size() == n) {
      break;
    }
    currently_active_i.clear();

    current_is_greater = !current_is_greater;

    if (current_is_greater) {
      for (int next_i : bi_to_index[last_i]) {
        currently_active_i.pb(next_i);
        kmax = min(kmax, next_i-1);
      }
    } else {
      for (int next_i : bi_to_index[last_i]) {
        currently_active_i.pb(next_i);
        kmin = max(kmin, next_i);
      }
    }

  }

  assert(kmin <= kmax);
  cout << kmin << "\n";
  assert(ans.size() == n);
  for (int i : ans) {
    cout << i << " ";
  }
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

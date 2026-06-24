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









int get(const map<int, int>& state, int q) {
  auto it = state.upper_bound(q);
  assert(it != state.end());
  return it->second;
}


void solve() {
  int n;
  cin >> n;
  vector<int> k(n);
  vector<vector<int>> a(n);
  for (int i = 0; i < n; i++) {
    cin >> k[i];
    int prefix_max = -1;
    for (int j = 0; j < k[i]; j++) {
      int x;
      cin >> x;
      if (x > prefix_max) {
        a[i].pb(x);
        prefix_max = x;
      }
    }
  }
  sort(a.begin(), a.end(), [](const vector<int>& v1, const vector<int>& v2) {
    return v1.back() > v2.back();
  });

  map<int, int> state;
  state[100'000'000] = 0;

  for (auto& v : a) {
    fprintf(stderr, "process vector "); PRINTVEC(v);
    int endnum = v.back();
    int bonus = get(state, endnum);
    for (int j = INT(v.size())-1; j >= 0; j--) {
      // insert v[j]: bonus + (v.size()-j)
      int val = bonus + (INT(v.size())-j);
      if (val > get(state, v[j]-1)) {
        // only insert if it actually helps
        state[v[j]] = val;
        auto it = state.find(v[j]);
        assert(it != state.end() && it->second > next(it)->second);
        // now if we outperform previous v[j] values, delete them
        while (it != state.begin()) {
          auto it2 = prev(it);
          if (it2->second <= val) {
            state.erase(it2);
            fprintf(stderr, "   delete, size left in state: %d\n", INT(state.size()));
          } else {
            break;
          }
        }
      }
    }
    PRINTMAP(state);
  }


  cout << get(state, -1) << "\n";

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

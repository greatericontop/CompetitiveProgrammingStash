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






vector<int> longtovec(long x) {
  assert(x > 0);
  vector<int> res;
  while (x > 0) {
    res.pb(x % 10);
    x /= 10;
  }
  reverse(res.begin(), res.end());
  return res;
}
long vectolong(const vector<int>& v) {
  assert(!v.empty());
  uint64_t res = 0;
  for (int d : v) {
    res *= 10;
    res += d;
  }
  if (res > LLONG_MAX) {
    return LLONG_MAX;
  }
  return LONG(res);
}



long get_min_above(long mini, int dmin, int dmax) {
  vector<int> v = longtovec(mini);

  // special case: one additional digit
  vector<int> v2;
  v2.pb(max(dmin, 1));
  for (int i = 0; i < v.size(); i++) {
    v2.pb(dmin);
  }
  assert(v2.size() == v.size()+1);
  assert(vectolong(v2) >= mini);
  long best_value_so_far = vectolong(v2);

  for (int i = 0; i < v.size(); i++) {
    // be strictly greater at :i:, then minimum digits past
    vector<int> v1;
    for (int j = 0; j < i; j++) {
      v1.pb(min(max(v[j], dmin), dmax));
    }
    if (i+1 == v.size())  v1.pb(min(max(v[i], dmin), dmax));
    else  v1.pb(min(max(v[i]+1, dmin), dmax));
    for (int j = i+1; j < v.size(); j++) {
      v1.pb(dmin);
    }
    long candidate = vectolong(v1);
    if (candidate >= mini) {
      best_value_so_far = min(best_value_so_far, candidate);
    }
  }

  return best_value_so_far;
}


void solve() {
//  long left, dmin, dmax;
//  cin >> left >> dmin >> dmax;
//  cout << get_min_above(left, dmin, dmax) << "\n";
  long left, right;
  cin >> left >> right;
  if (left == LONG(1e18)) {
    cout << LONG(1e18) << "\n";
    return;
  }
  for (int luckiness = 0; luckiness <= 9; luckiness++) {
    for (int dmin = 0; dmin <= 9-luckiness; dmin++) {
      int dmax = dmin + luckiness;
      assert(dmin >= 0 && dmax <= 9 && dmin <= dmax && dmax - dmin == luckiness);
      if (dmin == 0 && dmax == 0)  continue;

      // get minimum valu >= left with the digits
      long candidate = get_min_above(left, dmin, dmax);
      if (candidate <= right) {
        cout << candidate << "\n";
        return;
      }
    }
  }
  assert(0);  //9 should have worked

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

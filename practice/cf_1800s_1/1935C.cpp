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









struct Item {
  int a;
  int b;
};


void solve() {
  int n;
  long l;
  cin >> n >> l;
  vector<Item> items(n);
  FORI(n)  cin >> items[i].a >> items[i].b;
  sort(items.begin(), items.end(), [](const Item& i1, const Item& i2) {
    return i1.b < i2.b;  //ascending b
  });


  int best_ct = 0;
  for (int bmin_i = 0; bmin_i < n; bmin_i++) {
    multiset<int> inactive, active;
    for (int i = bmin_i; i < n; i++)  inactive.insert(items[i].a);
    long active_sum = 0;

    for (int j = n-1; j >= bmin_i; j--) {
      // calculate answer for bmax at [j] by adding small numbers from inactive set to active set
      long max_sum = l - items[j].b + items[bmin_i].b;
      while (!inactive.empty() && active_sum + LONG(*inactive.begin()) <= max_sum) {
        active_sum += *inactive.begin();
        active.insert(*inactive.begin());
        inactive.erase(inactive.begin());
      }
      best_ct = max(best_ct, INT(active.size()));

      // remove self from inactive first, then from active
      auto it = inactive.find(items[j].a);
      if (it != inactive.end()) {
        inactive.erase(it);
      } else {
        auto it2 = active.find(items[j].a);
        assert(it2 != active.end());
        active_sum -= items[j].a;
        active.erase(it2);
      }
    }
    assert(inactive.empty() && active.empty());

  }

  cout << best_ct << "\n";

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

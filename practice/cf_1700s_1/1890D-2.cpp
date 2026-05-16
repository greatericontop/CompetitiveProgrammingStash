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
#define FORI(x) for (int i = 0; i < (x); i++)
using pairii = pair<int, int>;
using pairll = pair<long, long>;
using AdjList = vector<vector<int>>;
// Positive numbers only
constexpr static inline int ceildiv(int a, int b) { return (a + b - 1) / b; }
constexpr static inline long ceildivl(long a, long b) { return (a + b - 1) / b; }










struct CC {
  long population;
  int rep;  //lowest node represents

  void print() const {
    fprintf(stderr, "CC(pop=%lld, rep=%d)\n", population, rep);
  }

  long get_required_cc1_size(long c) const {
    // require (cc1.population + population) >= c * 1 * rep
    return c*rep - population;
  }
};

CC merge(const CC& a, const CC& b) {
  return {a.population + b.population, min(a.rep, b.rep)};
}


void solve() {
  int n; long c;
  cin >> n >> c;
  vector<long> populations(n+1);
  for (int i = 1; i <= n; i++) {
    cin >> populations[i];
  }

  CC cc1 = {populations[1], 1};
  auto cmp = [&c](const CC& a, const CC& b) {
    return a.get_required_cc1_size(c) < b.get_required_cc1_size(c);
  };
  multiset<CC, decltype(cmp)> ccs(cmp);
  for (int i = 2; i <= n; i++) {
    CC cc = {populations[i], i};
    ccs.insert(cc);
  }

  while (!ccs.empty()) {
    auto it = ccs.begin();
    if (it->get_required_cc1_size(c) > cc1.population) {
      cout << "NO\n";
      return;
    }
    CC other = *it;
    ccs.erase(it);
    fprintf(stderr, "Merging CC with rep=%d into cc1\n", other.rep);
    cc1 = merge(cc1, other);
  }

  cout << "YES\n";

}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  cin >> t;
  while (t--)  solve();
  return 0;
}

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
};

CC merge(const CC& a, const CC& b) {
  return {a.population + b.population, min(a.rep, b.rep)};
}


bool cmp_rep(const CC& a, const CC& b) {
  return a.rep < b.rep;
}
bool cmp_alt(const CC& a, const CC& b) {
  return (a.population/a.rep) > (b.population/b.rep);
}


void solve() {
  int n; long c;
  cin >> n >> c;
  vector<long> populations(n+1);
  for (int i = 1; i <= n; i++) {
    cin >> populations[i];
  }

  CC cc1 = {populations[1], 1};
  set<CC, decltype(&cmp_rep)> cc_by_rep(cmp_rep);
  set<CC, decltype(&cmp_alt)> cc_by_alternate(cmp_alt);
  for (int i = 2; i <= n; i++) {
    CC cc = {populations[i], i};
    cc_by_rep.insert(cc);
    cc_by_alternate.insert(cc);
  }

  while (!cc_by_rep.empty()) {
    fprintf(stderr, "-----Current status:-----\nCC1: ");
    cc1.print();
    for (const CC& cc : cc_by_rep) {
      cc.print();
    }

    bool was_productive = false;
    // Try to link up 1s
    long max_j = cc1.population / c;
    for (auto it = cc_by_rep.begin(); it != cc_by_rep.end(); ) {
      if (it->rep > max_j)  break;
      cc1 = merge(cc1, *it);
      cc_by_alternate.erase(*it);
      it = cc_by_rep.erase(it);
      was_productive = true;
    }
    // Try to link up others with 1s
    long required_alt = c;
    for (auto it = cc_by_alternate.begin(); it != cc_by_alternate.end(); ) {
      if (it->population/it->rep < required_alt)  break;
      cc1 = merge(cc1, *it);
      cc_by_rep.erase(*it);
      it = cc_by_alternate.erase(it);
      was_productive = true;
    }

    if (!was_productive)  break;
  }

  if (cc_by_rep.empty()) {
    cout << "YES\n";
  } else {
    cout << "NO\n";
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

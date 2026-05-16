#include <bits/stdc++.h>
using namespace std;


//#define GREATERIC_DEBUG


#ifdef GREATERIC_DEBUG
  #define PRINTVEC(vec) do { \
    fprintf(stderr, "%s:  ", #vec); \
    for (const auto& _x : (vec))  fprintf(stderr, "%d ", _x); \
    fprintf(stderr, "\n"); \
  } while (0)
  #define PRINTMAP(map) do { \
    fprintf(stderr, "%s:  ", #map); \
    for (const auto& _p : (map))  fprintf(stderr, "%d->%d ", _p.first, _p.second); \
    fprintf(stderr, "\n"); \
  } while (0)
  #define DEBUGFOREACH(vec, stmt) do { \
    fprintf(stderr, "%s:  ", #vec); \
    for (const auto& x : (vec)) { \
      stmt; \
    } \
  } while (0)
#else
  #define fprintf(...) // no-op
  #define PRINTVEC(...) // no-op
  #define PRINTMAP(...) // no-op
#endif
#define long long long
#define pb push_back
using pairii = pair<int, int>;
using pairll = pair<long, long>;









struct Player {
    int index;
    int a;
    int b;

    bool operator <(const Player& other) const {
      // note: guaranteed no ties
      if (a != other.a)  return a < other.a;
      return b < other.b;
    }
};
struct SCC {
    int mina;
    int minb;
    int maxa;
    int maxb;

    bool operator <(const SCC& other) const {
      // Officially sorted by maxb, but should be sorted by all 4 simultaneously
      if (maxb != other.maxb)  return maxb < other.maxb;
      assert(false);
    }

    void update(const SCC& other) {
      mina = min(mina, other.mina);
      minb = min(minb, other.minb);
      maxa = max(maxa, other.maxa);
      maxb = max(maxb, other.maxb);
    }
};

void solve() {
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; i++)  cin >> a[i];
  vector<int> b(n);
  for (int i = 0; i < n; i++)  cin >> b[i];
  vector<Player> players(n);
  for (int i = 0; i < n; i++)  players[i] = {i, a[i], b[i]};
  sort(players.begin(), players.end());  //sorted by a strength

  set<SCC> sccs;
  for (const auto& p : players) {
    SCC us = {p.a, p.b, p.a, p.b};
    // Our a score can beat all existing SCCs
    // Coalesce all SCCs with maxb >= our b score
    auto it = sccs.lower_bound(us);
    while (it != sccs.end()) {
      us.update(*it);
      it = sccs.erase(it);
    }
    sccs.insert(us);
#ifdef GREATERIC_DEBUG
    fprintf(stderr, "SCCs now:\n");
    for (const auto& scc : sccs) {
      fprintf(stderr, "[%d %d] [%d %d]\n", scc.mina, scc.maxa, scc.minb, scc.maxb);
    }
#endif
  }

  SCC top_scc = *sccs.rbegin();
  assert(top_scc.maxa == accumulate(players.begin(), players.end(), -1, [](int acc, const Player& p) { return max(acc, p.a); }));
  assert(top_scc.maxb == accumulate(players.begin(), players.end(), -1, [](int acc, const Player& p) { return max(acc, p.b); }));
  for (int i = 0; i < n; i++) {
    if (a[i] >= top_scc.mina || b[i] >= top_scc.minb) {
      cout << "1";
    } else {
      cout << "0";
    }
  }
  cout << "\n";

}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--)  solve();
  return 0;
}

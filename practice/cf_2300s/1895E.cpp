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









struct Card {
  int atk;
  int health;

  // sort by atk
  bool operator < (const Card& other) const {
    if (atk != other.atk)  return atk < other.atk;
    return health < other.health;
  }
};


void dfs(int v, const AdjList& adj, int& to_increment) {
  to_increment++;
  for (int u : adj[v]) {
    dfs(u, adj, to_increment);
  }
}


void solve() {
  int n;
  cin >> n;
  vector<Card> cardsA(n);
  FORI(n)  cin >> cardsA[i].atk;
  FORI(n) { cin >> cardsA[i].health; cardsA[i].health++; }  //cuz i am an idiot who did >=
  int m;
  cin >> m;
  vector<Card> cardsB(m);
  FORI(m)  cin >> cardsB[i].atk;
  FORI(m) { cin >> cardsB[i].health; cardsB[i].health++; }

  sort(cardsA.begin(), cardsA.end());
  sort(cardsB.begin(), cardsB.end());
  // suffix maxima over all with attack >= requirement
  // can't use segtree due to multitests
  vector<int> suff_max_A(n+1, -10);
  vector<int> location_of_suff_max_A(n+1, -20);
  vector<int> suff_max_B(m+1, -10);
  for (int i = n-1; i >= 0; i--) {
    if (cardsA[i].health > suff_max_A[i+1]) {
      suff_max_A[i] = cardsA[i].health;
      location_of_suff_max_A[i] = i;
    } else {
      suff_max_A[i] = suff_max_A[i+1];
      location_of_suff_max_A[i] = location_of_suff_max_A[i+1];
    }
  }
  for (int i = m-1; i >= 0; i--)  suff_max_B[i] = max(suff_max_B[i+1], cardsB[i].health);


  vector<pairii> poi;  // 1 for A, 2 for B
  AdjList adj(n);
  AdjList backwards_adj(n);
  for (int i = 0; i < n; i++) {
    // Pick B card with attack >= our health
    int atk_req = cardsA[i].health;
    auto it = lower_bound(cardsB.begin(), cardsB.end(), Card{atk_req, -1});
    if (it == cardsB.end()) {
      // no B card could be picked
      poi.pb({i, 1});
      continue;
    }
    int ind = it - cardsB.begin();
    int best_hp_b = suff_max_B[ind];

    auto it2 = lower_bound(cardsA.begin(), cardsA.end(), Card{best_hp_b, -1});
    if (it2 == cardsA.end()) {
      // winning leaf for A
      poi.pb({i, 2});
      continue;
    }

    int ind2 = it2 - cardsA.begin();
    int i_new = location_of_suff_max_A[ind2];

    adj[i].pb(i_new);
    backwards_adj[i_new].pb(i);
  }

  for (int i = 0; i < n; i++) {
    fprintf(stderr, "card %d:  atk %d  health %d\n", i, cardsA[i].atk, cardsA[i].health);
  }
  PRINTVEC(suff_max_A);
  fprintf(stderr, "poi:  ");
  PRINTVECP(poi);
  for (int i = 0; i < n; i++) {
    fprintf(stderr, "i=%d:  ", i);
    PRINTVEC(adj[i]);
  }

  // dfs
  int total_1_count = 0, total_2_count = 0;  //rest are cycles
  for (auto p : poi) {
    int i = p.first;
    int type = p.second;
    if (type == 1) {
      dfs(i, backwards_adj, total_1_count);
    } else if (type == 2) {
      dfs(i, backwards_adj, total_2_count);
    }
  }

  int total_none_count = n - total_1_count - total_2_count;

  cout << total_1_count << " " << total_none_count << " " << total_2_count << "\n";



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

/*
 * This code contains the use of comments! You can identify them with the "//" or "/*" symbols.
 * Comments are used to explain the code and make it easier to understand.
 * They are ignored by the compiler and do not affect the execution of the program.
 * In this code, comments are used to explain the purpose of the code, the input and output format, and the logic behind the solution.
 * Unlike the 3 lines shown above, the comments in this code were lovingly hand-inserted and not a result of AI generated text.
 * Thanks to sc3developer <3 for inspiring this message and for being a great mentor.
 */

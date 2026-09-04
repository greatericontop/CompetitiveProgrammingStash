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
  #define PRINTVECB(vec) do { \
    fprintf(stderr, "%s:   ", #vec); \
    for (const auto& _p : (vec))  fprintf(stderr, "%s,  ", _p ? "true" : "false"); \
    fprintf(stderr, "\n"); \
  } while (0)
#else
  #define fprintf(...)
  #define PRINTVEC(...)
  #define PRINTVECL(...)
  #define PRINTMAP(...)
  #define PRINTVECP(...)
  #define PRINTVECPL(...)
  #define PRINTVECB(...)
#endif
#define long int64_t
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
// Round :a: down or up to the closest multiple of :b:
constexpr static inline int rounddown(int a, int b) { return (a / b) * b; }
constexpr static inline int roundup(int a, int b) { return ceildiv(a, b) * b; }
//constexpr static long MOD = 1'000'000'007LL;
//constexpr static long MOD =   998'244'353LL;






void solve_1color(int n, const AdjList& adj) {
  cout << 1 << endl;
  for (int i = 2; i <= n; i++) {
    cout << 1 << " ";
  }
  cout << endl;

  int x;  cin >> x;
  assert(x == 0);
  int _discard;  cin >> _discard;
  cout << 1 << endl;

  int y; cin >> y;
  assert(y == 1);
}


void twocolor(int v, const AdjList& adj, vector<bool>& coloring) {
  for (int u : adj[v]) {
    coloring[u] = !coloring[v];
    twocolor(u, adj, coloring);
  }
}
// (down is false, up is true), (down is true, up is false)
pairii count_inversions(int v, const AdjList& adj, vector<bool>& coloring) {
  pairii invs = {0, 0};
  if (adj[v].size() == 1) {
    bool down = coloring[adj[v][0]], up = coloring[v];
    if (!down && up) {
      invs.first++;
    } else if (down && !up) {
      invs.second++;
    }
  }
  for (int u : adj[v]) {
    pairii p = count_inversions(u, adj, coloring);
    invs.first += p.first;
    invs.second += p.second;
  }
  return invs;
}

bool try_solving_2color(int n, const AdjList& adj) {
  vector<bool> initial_2coloring(n+1, false);
  twocolor(1, adj, initial_2coloring);
  for (int subroot : adj[1]) {
    pairii invs = count_inversions(subroot, adj, initial_2coloring);
    if (invs.first > 0 && invs.second > 0) {
      return false;
    } else if (invs.second > 0) {
      // then we need to reverse the colors, so only inversions are "always pick true to go up"
      initial_2coloring[subroot] = !initial_2coloring[subroot];
      twocolor(subroot, adj, initial_2coloring);
    }
  }

  cout << 2 << endl;
  for (int i = 2; i <= n; i++) {
    cout << (initial_2coloring[i] ? 2 : 1) << " ";
  }
  cout << endl;

  while (true) {
    int info;  cin >> info;
    if (info == 1)  return true;
    if (info == -1)  assert(false);
    // otherwise info == 0, let's play
    int onect, twoct;  cin >> onect >> twoct;
    if (onect == 1 && twoct == 1) {
      cout << 2 << endl;
    } else if (onect == 1) {
      cout << 1 << endl;
    } else if (twoct == 1) {
      cout << 2 << endl;
    } else {
      assert(false && "onect or twoct should be 1");
    }
  }
}



void threecolor(int v, const AdjList& adj, vector<int>& coloring) {
  for (int u : adj[v]) {
    coloring[u] = (coloring[v] % 3) + 1;
    threecolor(u, adj, coloring);
  }
}


void solve_3color(int n, const AdjList& adj) {
  vector<int> coloring(n+1, 1);
  threecolor(1, adj, coloring);
  cout << 3 << endl;
  for (int i = 2; i <= n; i++) {
    cout << coloring[i] << " ";
  }
  cout << endl;

  while (true) {
    int info;  cin >> info;
    if (info == 1)  return;
    if (info == -1)  assert(false);
    int onect, twoct, threect;  cin >> onect >> twoct >> threect;

    if (onect == 0 && twoct == 1) {
      cout << 2 << endl;
    } else if (twoct == 0 && threect == 1) {
      cout << 3 << endl;
    } else if (threect == 0 && onect == 1) {
      cout << 1 << endl;
    } else {
      assert(false);
    }
  }
}





void solve() {
  int n;
  cin >> n;
  AdjList adj(n+1);
  vector<int> parents(n+1, -1);
  for (int i = 2; i <= n; i++) {
    int p;  cin >> p;
    adj[p].pb(i);
    parents[i] = p;
  }

  if (adj[1].size() == n-1) {
    // Solve 1 color
    solve_1color(n, adj);
  } else {
    bool ret = try_solving_2color(n, adj);
    if (!ret) {
      solve_3color(n, adj);
    }
  }
}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  //cin >> t;
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

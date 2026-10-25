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
/* Make sure you initialize parents[root] = root or -1 or some non-vertex number! */
void create_directed_adj(int v, AdjList& adj_undirected, vector<int>& parents, vector<set<int>>& adj) {
  for (int child : adj_undirected[v]) {
    if (child == parents[v])  continue;
    parents[child] = v;
    adj[v].insert(child);
    create_directed_adj(child, adj_undirected, parents, adj);
  }
}






// if there are >=THRESH leaves, then we will use the leaf-prune strategy
constexpr int THRESH = 25;





void solve() {
  int n;
  cin >> n;
  AdjList adj_undirected(n+1);
  FORI(n-1) {
    int u, v;
    cin >> u >> v;
    adj_undirected[u].pb(v);
    adj_undirected[v].pb(u);
  }
  vector<int> parents(n+1, -1);
  vector<set<int>> adj(n+1);
  create_directed_adj(1, adj_undirected, parents, adj);

  set<int> leaves;
  for (int v = 1; v <= n; v++) {
    if (adj[v].empty())  leaves.insert(v);
  }

  // this runs at most 5000/THRESH = 200 times, for THRESH = 25
  while (leaves.size() >= THRESH) {
    fprintf(stderr, "leaves >= thresh  ");  PRINTVEC(leaves);
    int v1 = *leaves.begin();
    cout << "? " << v1 << endl;
    int resp;  cin >> resp;
    if (resp == 1) {
      // then we just won
      cout << "! " << v1 << endl;
      return;
    } else {
      // trim off all leaves
      vector<int> leaves_copy(leaves.begin(), leaves.end());
      for (int v : leaves_copy) {
        int p = parents[v];
        adj[p].erase(v);
        leaves.erase(v);
        if (adj[p].empty())  leaves.insert(p);
      }
    }
  }

  // Now there are <= THRESH leaves
  int bottom_leaf = -1;
  for (int v : leaves) {
    int p = v;
    // go up as long as parent is a singleton
    while (parents[p] != -1 && adj[parents[p]].size() == 1) {
      p = parents[p];
    }
    fprintf(stderr, "one at a time: leaf %d goes up to %d\n", v, p);
    cout << "? " << p << endl;
    int resp;  cin >> resp;
    if (resp == 1) {
      bottom_leaf = v;
      break;
    } else {
      // unlink p from its parent
      int pp = parents[p];
      if (pp != -1) {
        adj[pp].erase(p);
      }
    }
  }
  assert(bottom_leaf != -1);

  // ~75 queries left
  vector<int> path;
  int vv = bottom_leaf;
  while (vv != -1) {
    path.pb(vv);
    vv = parents[vv];
  }
  PRINTVEC(path);

  // now run binary search on it
  int l = 0, r = path.size()-1;
  while (l < r) {
    int m = l + (r-l)/2;
    cout << "? " << path[m] << endl;
    int resp;  cin >> resp;
    if (resp == 1) {
      // answer is equal to or below m, in the left half
      r = m;
    } else {
      // answer is above m, in the right half
      l = m + 1;
      // and plus 1 since it moves up
      l++;  r++;
      r = min(r, INT(path.size())-1);
    }
  }

  cout << "! " << path[l] << endl;

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

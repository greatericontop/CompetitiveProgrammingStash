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
//#define long int64_t
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








/* Make sure you initialize parents[root] = root or -1 or some non-vertex number! */
void create_directed_adj(int v, AdjList& adj_undirected, vector<int>& parents, AdjList& adj, vector<int>& vis_here, const vector<bool>& is_red) {
  vis_here.pb(v);
  if (is_red[v])  return;  //no more
  for (int child : adj_undirected[v]) {
    if (child == parents[v])  continue;
    parents[child] = v;
    adj[v].push_back(child);
    create_directed_adj(child, adj_undirected, parents, adj, vis_here, is_red);
  }
}
struct State {
  long double nohelp;
  long double yeshelp;
};


long double INF = 1e30;


void do_dp(int v, const AdjList& adj, vector<State>& dp, const vector<bool>& is_red, bool is_not_root) {
  if (adj[v].empty()) {
    // Either a red leaf or a black leaf
    if (is_red[v]) {
      dp[v] = State{0.0, 0.0};  //free
    } else {
      dp[v] = State{INF, 1.0};  //impossible, guaranteed with help in 1 go
    }
    return;
  }

  int sz = adj[v].size();
  vector<State> children; children.reserve(sz);
  for (int u : adj[v]) {
    do_dp(u, adj, dp, is_red, true);
    children.push_back(dp[u]);
  }
  // sort by lowest saving first (.nohelp - .yeshelp)
  sort(children.begin(), children.end(), [](const State& a, const State& b) {
    return a.nohelp - a.yeshelp < b.nohelp - b.yeshelp;
  });
  vector<long double> prefix_nohelp(sz, 0.0);
  prefix_nohelp[0] = children[0].nohelp;
  for (int i = 1; i < sz; i++)  prefix_nohelp[i] = prefix_nohelp[i-1] + children[i].nohelp;
  vector<long double> prefix_yeshelp(sz, 0.0);
  prefix_yeshelp[0] = children[0].yeshelp;
  for (int i = 1; i < sz; i++)  prefix_yeshelp[i] = prefix_yeshelp[i-1] + children[i].yeshelp;

  // no parent help
  long double best_nohelp = INF;
  for (int i = 0; i < sz; i++) {
    // Perform 0...i first, then us, then i+1...sz-1
    long double c1 = prefix_nohelp[i];
    long double c2 = ((long double)sz+is_not_root) / (i+1);  // i+1 (e.g. 1 for i=0) children are red
    long double c3 = prefix_yeshelp[sz-1] - prefix_yeshelp[i];
    best_nohelp = min(best_nohelp, c1 + c2 + c3);
  }

  // yes parent help
  long double best_yeshelp = INF;
  for (int i = 0; i < sz; i++) {
    // Perform 0...i first, then us, then i+1...sz-1
    long double c1 = prefix_nohelp[i];
    long double c2 = ((long double)sz+is_not_root) / (i+2);  // because we had help
    long double c3 = prefix_yeshelp[sz-1] - prefix_yeshelp[i];
    best_yeshelp = min(best_yeshelp, c1 + c2 + c3);
  }
  // Also if we do all yeshelp
  long double _c2 = ((long double)sz+is_not_root);  // (divided by 1)
  long double _c3 = prefix_yeshelp[sz-1];
  best_yeshelp = min(best_yeshelp, _c2 + _c3);

  dp[v] = State{best_nohelp, best_yeshelp};
}












void solve() {
  int n;
  cin >> n;
  vector<bool> is_red(n+1);
  string s;
  cin >> s;
  for (int i = 0; i < n; i++) {
    is_red[i+1] = (s[i] == '1');
  }
  AdjList adj(n+1);
  FORI(n-1) {
    int u, v;
    cin >> u >> v;
    adj[u].pb(v);
    adj[v].pb(u);
  }


  long double accumulator = 0.0;
  vector<bool> visited_roots(n+1, false);
  vector<int> parents(n+1, -1);  //this shouldn't need to be cleared
  vector<State> dp(n+1);
  AdjList adj_mini(n+1);
  // Goated impl strat: to visit every "component", we'll try visiting every non-red vertex. If unvisited, we'll root there.
  for (int v = 1; v <= n; v++) {
    if (is_red[v] || visited_roots[v])  continue;
    vector<int> vis_here;  //to clean up adj_mini
    create_directed_adj(v, adj, parents, adj_mini, vis_here, is_red);

    fprintf(stderr, "-----\nSubtree\n");
    for (int u : vis_here) {
      fprintf(stderr, "%d:  ", u);
      for (int child : adj_mini[u])  fprintf(stderr, "%d ", child);
      fprintf(stderr, "\n");
    }

    // Now run tree dp
    do_dp(v, adj_mini, dp, is_red, false);
    fprintf(stderr, "dp[%d] = {%.6Lf, %.6Lf}\n", v, dp[v].nohelp, dp[v].yeshelp);
    accumulator += dp[v].nohelp;

    for (int u : vis_here) {
      visited_roots[u] = true;
      adj_mini[u].clear();
    }
  }


  cout << fixed << setprecision(15) << accumulator << "\n";


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

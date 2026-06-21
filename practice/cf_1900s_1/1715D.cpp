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





#pragma GCC optimize("Ofast,unroll-loops,no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")






struct Edge {
  int i, j, x;
};
struct AdjEntry {
  int to;
  int weight;
};


void dfs(int v, vector<vector<AdjEntry>>& adj, vector<int>& ans_here) {
  for (const auto e: adj[v]) {
    if (e.weight == 1) {
      if (ans_here[v] == 0 && ans_here[e.to] == -1) {
        ans_here[e.to] = 1;
        dfs(e.to, adj, ans_here);
      }
    } else if (e.weight == 0 && ans_here[e.to] == -1) {
      //assert(set_to == 0);
      ans_here[e.to] = 0;
      dfs(e.to, adj, ans_here);
    } //else  assert(0);
  }
}


void solve() {
  int n, q;
  cin >> n >> q;
  vector<Edge> edges(q);
  FORI(q) {
    cin >> edges[i].i >> edges[i].j >> edges[i].x;
  }

  vector<int> ans(n+1, 0);
  for (int b = 0; b < 30; b++) {
    fprintf(stderr, "bit %d\n", b);
    vector<int> ans_here(n+1, -1);
    vector<vector<AdjEntry>> adj(n+1);
    vector<int> zeroed_verts;
    vector<int> self_loop_1s;
    for (const auto& e : edges) {
      if (e.i == e.j) {
        if (e.x & (1 << b)) {
          self_loop_1s.pb(e.i);
        } else {
          zeroed_verts.pb(e.i);
        }
        continue;
      }
      adj[e.i].pb({e.j, (e.x >> b) & 1});
      adj[e.j].pb({e.i, (e.x >> b) & 1});
      if (!(e.x & (1 << b))) {
        zeroed_verts.pb(e.i);
        //zeroed_verts.pb(e.j);
      }
    }
    for (int v : zeroed_verts) {
      ans_here[v] = 0;
      dfs(v, adj, ans_here);
    }
    for (int v : self_loop_1s) {
      ans_here[v] = 1;
      dfs(v, adj, ans_here);
    }

    // lexico greedy
    for (int v = 1; v <= n; v++) {
      if (ans_here[v] == -1) {
        ans_here[v] = 0;
        dfs(v, adj, ans_here);
      }
    }
    for (int v = 1; v <= n; v++) {
      ans[v] |= (ans_here[v] << b);
    }
  }

  for (int v = 1; v <= n; v++) {
    cout << ans[v] << " ";
  }
  cout << "\n";

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

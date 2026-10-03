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
void create_directed_adj(int v, AdjList& adj_undirected, vector<int>& parents, const vector<bool>& banned, AdjList& adj) {
  for (int child : adj_undirected[v]) {
    if (child == parents[v])  continue;
    if (banned[child])  continue;
    parents[child] = v;
    adj[v].push_back(child);
    create_directed_adj(child, adj_undirected, parents, banned, adj);
  }
}

void get_appearances(int v, const AdjList& adj, map<int, int>& appearances, const vector<int>& values) {
  appearances[values[v]]++;
  for (int u : adj[v]) {
    get_appearances(u, adj, appearances, values);
  }
}








void solve() {
  int n, k;
  cin >> n >> k;
  vector<int> values(n+1);
  FORI1(n)  cin >> values[i];
  vector<vector<int>> whole_adj(n+1);
  FORI(n) {
    int a, b;  cin >> a >> b;
    whole_adj[a].pb(b);
    whole_adj[b].pb(a);
  }

  /*
   * Find the cycle, peel off any vertices with degree 1.
   */
  vector<set<int>> adj1(n+1);
  FORI1(n) {
    for (int vv : whole_adj[i]) {
      adj1[i].insert(vv);
    }
  }
  set<pairii> priority;
  FORI1(n)  priority.insert({adj1[i].size(), i});
  vector<int> cycle_verts;
  while (!priority.empty()) {
    auto [sz, vertex] = *priority.begin();
    if (sz == 1) {
      priority.erase(priority.begin());
      for (int u : adj1[vertex]) {
        adj1[u].erase(vertex);
        int sz_new = adj1[u].size();
        assert(priority.find({sz_new+1, u}) != priority.end());
        priority.erase({sz_new+1, u});
        priority.insert({sz_new, u});
      }
    } else {
      // TODO: vertices in set
      for (auto [sz1, v1] : priority) {
        cycle_verts.pb(v1);
      }
      break;
    }
  }
  vector<bool> is_cycle_vert(n+1, false);
  for (int v : cycle_verts)  is_cycle_vert[v] = true;
  PRINTVEC(cycle_verts);


  /*
   * Find all subtree roots
   */
  vector<int> subtree_roots;
  vector<int> parents(n+1);
  AdjList adj_tree(n+1);
  for (int cyclevert : cycle_verts) {
    subtree_roots.pb(cyclevert);
    create_directed_adj(cyclevert, whole_adj, parents, is_cycle_vert, adj_tree);
  }

  PRINTVEC(subtree_roots);
  fprintf(stderr, "Adj List:\n");
  for (int v = 1; v <= n; v++) {
    fprintf(stderr, "%d:  ", v);
    for (int u : adj_tree[v]) {
      fprintf(stderr, "%d, ", u);
    }
    fprintf(stderr, "\n");
  }


  /*
   * Within the subtree
   */
  long answer = 0;
  map<int, int> appearances_total;
  map<int, map<int, int>> all_appearances;
  for (int r : subtree_roots) {
    // recursively get list of # appearances of each
    map<int, int> appearances;
    get_appearances(r, adj_tree, appearances, values);  appearances[values[r]]--;  //except the root

    // Now do subtree<->subtree (where the cycle vertex is considered part of the cycle)
    for (auto [value, ct] : appearances) {
      appearances_total[value] += ct;

      if (appearances.find(value+k) == appearances.end())  continue;  //so the map doesn't explode
      int ct_of_target = appearances[value+k];
      answer += LONG(ct_of_target) * LONG(ct);
    }

    all_appearances[r] = appearances;
  }
  fprintf(stderr, "answer in subtrees = %ld\n", answer);

  /*
   * Cross-subtrees
   */
  fprintf(stderr, "after crossing subtrees = %ld\n", answer);
  for (int r : subtree_roots) {
    map<int, int>& appearances = all_appearances[r];

    for (auto [value, ct] : appearances) {
      if (appearances_total.find(value+k) == appearances_total.end())  continue;  //so the map doesn't explode
      int ct_of_target = appearances_total[value+k] - (appearances.find(value+k) == appearances.end() ? 0 : appearances[value+k]);
      assert(ct_of_target >= 0);
      answer += LONG(ct_of_target) * LONG(ct) * 2;
    }
  }

  /*
   * Within the cycle
   */
  map<int, int> appearances_cycle;
  {
    for (int v : cycle_verts) {
      appearances_cycle[values[v]]++;
    }
    for (auto [value, ct] : appearances_cycle) {
      if (appearances_cycle.find(value+k) == appearances_cycle.end())  continue;
      int ct_of_target = appearances_cycle[value+k];
      // 2 ways because either direction to walk
      answer += LONG(ct_of_target) * LONG(ct) * 2;
    }

    fprintf(stderr, "Including the cycle answer is %ld\n", answer);
  }



  /*
   * Cycle to subtrees
   * Vertex c in cycle,
   *   Add 2* for everyone
   *   Subtract 1* for own subtree
   */
  for (int c : subtree_roots) {
    int valuelower = values[c] - k;
    int valuehigher = values[c] + k;

    answer += 2 * appearances_total[valuelower];
    answer += 2 * appearances_total[valuehigher];
    answer -= all_appearances[c][valuelower];
    answer -= all_appearances[c][valuehigher];
  }




  cout << answer << endl;
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

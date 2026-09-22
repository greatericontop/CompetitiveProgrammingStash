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
void create_directed_adj(int v, AdjList& adj_undirected, vector<int>& parents, AdjList& adj) {
  for (int child : adj_undirected[v]) {
    if (child == parents[v])  continue;
    parents[child] = v;
    adj[v].push_back(child);
    create_directed_adj(child, adj_undirected, parents, adj);
  }
}



/* tour[v].first corresponds to v, tour[v].second corresponds to the last endpoint of the segment, inclusive. */
using EulerTour = vector<pair<int, int>>;

void euler_tour(int v, AdjList& adj, EulerTour& tour, int& counter) {
  tour[v].first = counter;
  counter++;
  for (int child : adj[v]) {
    euler_tour(child, adj, tour, counter);
  }
  tour[v].second = counter - 1;
}


// same numbers in old and new tree

void create_implicit_tree(int v, const AdjList& adj, AdjList& adj_new, vector<int>& who, const EulerTour& etour) {
  // If v is in :who:, immediately recurse on children
  if (!who.empty() && who.back() == v) {
    who.pop_back();
    for (int u : adj[v]) {
      adj_new[v].pb(u);
      create_implicit_tree(u, adj, adj_new, who, etour);
    }
    return;
  }
  // Otherwise, recurse on children in our euler tour
  while (!who.empty()) {
    int u = who.back();
    assert(u > v);
    if (u > etour[v].second)  break;  //this one falls outside our subtree now
    who.pop_back();
    adj_new[v].pb(u);
    create_implicit_tree(u, adj, adj_new, who, etour);
  }
}

void clear_adj(int v, AdjList& adj) {
  for (int u : adj[v])  clear_adj(u, adj);
  adj[v].clear();
}


void dp_accessible_size(int v, const AdjList& adj, vector<int>& accessible_size, const vector<bool>& iscolored) {
  if (iscolored[v]) {
    accessible_size[v] = 1;
    for (int u : adj[v]) {
      dp_accessible_size(u, adj, accessible_size, iscolored);
    }
  } else {
    accessible_size[v] = 0;
    for (int u : adj[v]) {
      dp_accessible_size(u, adj, accessible_size, iscolored);
      accessible_size[v] += accessible_size[u];
    }
  }
}

long answer(int v, const AdjList& adj, const vector<int>& accessible_size, const vector<bool>& iscolored) {
  long ans = 0;
  if (iscolored[v]) {
    int total_accessible_children = 0;
    for (int u : adj[v]) {
      total_accessible_children += accessible_size[u];
    }
    ans += total_accessible_children;  //v to them; only if we are not a root
    for (int u : adj[v]) {
      ans += LONG(accessible_size[u]) * LONG(accessible_size[u]-1) / 2;
    }
    for (int u : adj[v]) {
      ans += answer(u, adj, accessible_size, iscolored);
    }
  } else if (v == 1) {
    int total_accessible_children = 0;
    for (int u : adj[v]) {
      total_accessible_children += accessible_size[u];
    }
    ans += LONG(total_accessible_children) * LONG(total_accessible_children-1) / 2;
    for (int u : adj[v]) {
      ans += answer(u, adj, accessible_size, iscolored);
    }
  } else {
    // just recurse
    for (int u : adj[v]) {
      ans += answer(u, adj, accessible_size, iscolored);
    }
  }
  fprintf(stderr, "  answer at %d: %ld\n", v, ans);
  return ans;
}










void solve() {
  int n;
  cin >> n;
  AdjList adj_undirected(n+1);
  vector<int> colors(n+1);
  FORI1(n)  cin >> colors[i];
  FORI(n-1) {
    int u, v;  cin >> u >> v;
    adj_undirected[u].pb(v);
    adj_undirected[v].pb(u);
  }
  vector<int> parents(n+1, -1);
  AdjList adj_before_et(n+1);
  create_directed_adj(1, adj_undirected, parents, adj_before_et);
  EulerTour etour_unmapped(n+1), etour(n+1);
  int counter = 1;
  euler_tour(1, adj_before_et, etour_unmapped, counter);
  // remapping
  AdjList adj(n+1);
  for (int v_old = 1; v_old <= n; v_old++) {
    int v_new = etour_unmapped[v_old].first;
    for (int u_old : adj_before_et[v_old]) {
      int u_new = etour_unmapped[u_old].first;
      adj[v_new].pb(u_new);
    }
    etour[v_new] = etour_unmapped[v_old];
  }
  fprintf(stderr, "Remapping:  ");
  for (int v_old = 1; v_old <= n; v_old++) {
    fprintf(stderr, "%d->%d  ", v_old, etour[v_old].first);
  }
  fprintf(stderr, "\n\n");
  vector<vector<int>> verts_per_color(n+1);
  FORI1(n)  verts_per_color[colors[i]].pb(etour[i].first);

  AdjList adj_new(n+1);
  vector<int> accessible_size(n+1);
  vector<bool> iscolored(n+1, false);
  long ans = 0;
  for (int c = 1; c <= n; c++) {
    if (verts_per_color[c].empty())  continue;
    for (int v : verts_per_color[c])  iscolored[v] = true;
    vector<int> verts_per_color_copy = verts_per_color[c];
    sort(verts_per_color_copy.begin(), verts_per_color_copy.end(), greater<int>());  //lowest in the .back()
    create_implicit_tree(1, adj, adj_new, verts_per_color_copy, etour);
    fprintf(stderr, "Implicit tree for color %d:\n", c);
    PRINTVEC(verts_per_color[c]);
    for (int v = 1; v <= n; v++) {
      if (!adj_new[v].empty()) {
        fprintf(stderr, "adj[%d]: ", v);
        for (int u : adj_new[v])  fprintf(stderr, "%d ", u);
        fprintf(stderr, "\n");
      }
    }

    dp_accessible_size(1, adj_new, accessible_size, iscolored);
    PRINTVEC(accessible_size);
    long anshere = answer(1, adj_new, accessible_size, iscolored);
    fprintf(stderr, "ans here %d\n", anshere);
    ans += anshere;

    // clean up in O(n_here)
    clear_adj(1, adj_new);
    for (int v : verts_per_color[c])  iscolored[v] = false;
  }

  cout << ans << "\n";

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

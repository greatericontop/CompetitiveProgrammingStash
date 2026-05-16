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









using Permutation = vector<int>;

struct Node {
  bool has_at_least_one;
  vector<Permutation> permutations;  //temporary storage
  vector<Node> children;

  void initialize(int m, int target) {
    if (permutations.empty()) {
      has_at_least_one = false;
      children = vector<Node>();
      return;
    }
    has_at_least_one = true;
    children = vector<Node>(m+1);
    if (target > m) {
      return;
    }
    for (const auto& perm : permutations) {
      vector<int> reversedperm(m+1);
      for (int i = 1; i <= m; i++)  reversedperm[perm[i]] = i;
      int which_bin = reversedperm[target];
      children[which_bin].permutations.push_back(perm);
    }
    for (int i = 1; i <= m; i++) {
      children[i].initialize(m, target+1);
    }
  }

  void debug_print(int m, int indent) {
    string indent_str(indent, ' ');
    for (int i = 1; i <= m; i++) {
      fprintf(stderr, "%s%d:\n", indent_str.c_str(), i);
      if (children[i].has_at_least_one) {
        children[i].debug_print(m, indent + 2);
      }
    }
  }
};


void solve() {
  int n, m;
  cin >> n >> m;
  vector<Permutation> perms(n, Permutation(m+1));
  for (int i = 0; i < n; i++) {
    for (int j = 1; j <= m; j++) {
      cin >> perms[i][j];
    }
  }
  Node root;
  root.permutations = perms;
  root.initialize(m, 1);
  assert(root.has_at_least_one);

  root.debug_print(m, 0);

  for (int i = 0; i < n; i++) {
    Permutation p = perms[i];
    Node *cur = &root;
    int maxi = m;
    for (int j = 1; j <= m; j++) {
      int which_bin = p[j];
      cur = &(cur->children[which_bin]);
      if (!cur->has_at_least_one) {
        maxi = j-1;
        break;
      }
    }
    cout << maxi << " ";
  }
  cout << "\n";

}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  cin >> t;
  while (t--)  solve();
  return 0;
}

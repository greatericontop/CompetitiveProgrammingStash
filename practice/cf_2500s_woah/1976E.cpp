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
constexpr static long MOD =   998'244'353LL;







struct TreeNode {
  int num;
  int left;
  int right;
};

void trav(const vector<TreeNode>& tree, int v, vector<int>& seq) {
  if (v == -1)  return;
  if (tree[v].left == -1 && tree[v].right == -1) {
    // insert leaves in left to right inorder order
    seq.pb(tree[v].num);
    return;
  }
  trav(tree, tree[v].left, seq);
  trav(tree, tree[v].right, seq);
}


void solve() {
  int n, q;
  cin >> n >> q;
  vector<int> l(q), r(q);
  FORI(q)  cin >> l[i];
  FORI(q)  cin >> r[i];

  vector<TreeNode> tree;  tree.reserve(n+100);
  tree.pb({-1, 1, 2});
  tree.pb({l[0], -1, -1});
  tree.pb({r[0], -1, -1});
  {
    vector<int> num_to_node(n+1, -1);
    num_to_node[l[0]] = 1;
    num_to_node[r[0]] = 2;
    for (int i = 1; i < q; i++) {
      int li = l[i], ri = r[i];
      assert(num_to_node[li] == -1 ^ num_to_node[ri] == -1);
      int parent = num_to_node[li] == -1 ? num_to_node[ri] : num_to_node[li];  assert(parent != -1);
      int n1 = tree.size();  tree.pb({li, -1, -1});
      int n2 = tree.size();  tree.pb({ri, -1, -1});
      tree[parent].left = n1;  tree[parent].right = n2;
      num_to_node[li] = n1;  num_to_node[ri] = n2;
    }
  }
  vector<int> seq;
  trav(tree, 0, seq);
  PRINTVEC(seq);

  vector<int> num_to_idx(n+1, -1);
  for (int i = 0; i < seq.size(); i++)  num_to_idx[seq[i]] = i;
  vector<bool> borders(num_to_idx.size() + 1, false);  int borders_sum = 0;
  auto set_border = [&](int idx) {
    if (!borders[idx]) {
      borders[idx] = true;
      borders_sum++;
    }
  };
  long answer = 1;
  int num_placed = 0;

  for (int x = n; x >= 1; x--) {
    int idx = num_to_idx[x];
    if (idx != -1) {
      // forced placement, but set borders
      set_border(idx);
      set_border(idx+1);
    } else {
      // combi
      long slots = borders_sum + num_placed;
      answer *= slots;
      answer %= MOD;

      num_placed++;
    }
  }

  cout << answer << "\n";




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

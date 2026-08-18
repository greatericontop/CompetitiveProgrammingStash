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








struct Engine {
  vector<int> a;
  vector<long> s;
  vector<long> s_prefix;

  vector<long> layer_sums;
  vector<long> layer_indices;

  /* Assumes a is filled in and 1-based */
  void init(int n) {
    s.resize(n+1);
    s[0] = 0;
    FORI1(n)  s[i] = s[i-1] + a[i];
    s_prefix.resize(n+1);
    s_prefix[0] = 0;
    FORI1(n)  s_prefix[i] = s_prefix[i-1] + s[i];

    layer_sums.resize(n+1);
    layer_indices.resize(n+1);
    layer_sums[0] = 0;  layer_indices[0] = 0;
    for (int l = 1; l <= n; l++) {
      layer_indices[l] = layer_indices[l-1] + (n-l+1);  //index that layer ENDS at
      layer_sums[l] = layer_sums[l-1] + row_prefix_sum(l, n);
    }
  }

  /* Query s(l, l) + s(l, l+1) + ...  + s(l, k) */
  long row_prefix_sum(int layer, int k) {
    // s(1, l) + ... + s(1, k)
    long ret = s_prefix[k] - s_prefix[layer-1];
    // Subtract s(1, l-1) from l...k
    ret -= LONG(k-layer+1) * s[layer-1];
    return ret;
  }

  /* Query the original problem */
  long query(long i) {
    if (i == 0)  return 0;
    // Last layer
    auto it = lower_bound(layer_indices.begin(), layer_indices.end(), i);
    assert(it != layer_indices.end() && it != layer_indices.begin());
    int last_l = it - layer_indices.begin();
    long ret = layer_sums[last_l-1];
    long adj_i = i - layer_indices[last_l-1];
    assert(adj_i >= 1 && adj_i <= a.size());
    fprintf(stderr, "adj i: %ld, row prefix: %ld\n", adj_i, row_prefix_sum(last_l, INT(adj_i+last_l-1)));
    ret += row_prefix_sum(last_l, INT(adj_i+last_l-1)); // since 1st at layer 4 is really 4
    return ret;
  }
};



void solve() {
  int n;
  cin >> n;
  Engine engine;
  engine.a.resize(n+1);
  FORI1(n)  cin >> engine.a[i];
  engine.init(n);
  PRINTVECL(engine.s);
  PRINTVECL(engine.s_prefix);
  PRINTVECL(engine.layer_sums);
  PRINTVECL(engine.layer_indices);

  int q;  cin >> q;
  while (q --> 0) {
    long l, r;  cin >> l >> r;
    long ans = engine.query(r) - engine.query(l-1);
    cout << ans << "\n";
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

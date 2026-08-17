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






struct LazyBoolArray {
  vector<bool> internal;
  int sum;

  void set(int i, bool val) {
    sum -= internal[i];
    internal[i] = val;
    sum += internal[i];
  }
};





void solve() {
  int n, m, q;
  cin >> n >> m >> q;
  vector<int> remap(n+1);
  FORI1(n) {
    int ai;  cin >> ai;
    remap[ai] = i;
  }
  vector<int> b(m);
  vector<set<int>> c(n+1);
  FORI1(n)  c[i].insert(INT_MAX);  //dummy value
  FORI(m) {
    int bi;  cin >> bi;
    b[i] = remap[bi];
    c[b[i]].insert(i);  // person b[i] presents i
  }
  LazyBoolArray status;
  status.internal = vector<bool>(n+1, false);  status.sum = 0;
  for (int p = 2; p <= n; p++) {
    bool ok = (*c[p-1].begin()) <= (*c[p].begin());
    status.set(p, ok);
  }
  if (status.sum == n-1)  cout << "YA\n";
  else  cout << "TIDAK\n";

  while (q --> 0) {
    int s, t;  cin >> s >> t;  s--;  t = remap[t];
    vector<int> p_to_recheck;
    // remove s from c[b[s]]
    assert(c[b[s]].count(s) == 1);
    c[b[s]].erase(s);
    p_to_recheck.pb(b[s]);
    p_to_recheck.pb(b[s]+1);
    // add s to c[t]
    c[t].insert(s);
    p_to_recheck.pb(t);
    p_to_recheck.pb(t+1);

    b[s] = t;

    fprintf(stderr, "Status:\n");
    for (int p = 1; p <= n; p++) {
      fprintf(stderr, "%d   ", p);  PRINTVEC(c[p]);
    }

    for (int p : p_to_recheck) {
      if (p < 2 || p > n)  continue;
      bool ok = (*c[p-1].begin()) <= (*c[p].begin());
      status.set(p, ok);
    }

    if (status.sum == n-1)  cout << "YA\n";
    else  cout << "TIDAK\n";
  }



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

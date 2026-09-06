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








constexpr long INF = LONG(1e18);


void solve() {
  int n;  long x, y;
  cin >> n >> x >> y;
  string a_old, b_old;  cin >> a_old >> b_old;
  string s(n, '.');
  int inversions = 0;
  FORI(n) {
    s[i] = (a_old[i] == b_old[i]) ? '0' : '1';
    if (s[i] == '1')  inversions++;
  }
  if (inversions % 2 == 1) {
    cout << "-1\n";
    return;
  }
  if (inversions == 2) {
    fprintf(stderr, "2 inversions\n");
    int i = 0;
    while (i < n && s[i] == '0')  i++;
    assert(i != n);
    int j = i+1;
    while (j < n && s[j] == '0')  j++;
    assert(j != n);
    long dist = j - i;
    if (dist == 1) {
      long cost = min(x, 2*y);
      // actually since n>=5 we can always do double y
//      // can do 2*y if i is at least 2 or j is at most n-3
//      if (i >= 2 || j <= n-3)  cost = min(cost, 2*y);
//      // can do 3*y if we have 4 spaces
//      if (i == 1 && j == 2)  cost = min(cost, 3*y);
      cout << cost << "\n";
      return;
    } else {
      long cost = min(y, dist*x);
      cout << cost << "\n";
      return;
    }
  }
  int inv_pairs = inversions/2;
  fprintf(stderr, "%s, with %d inversion pairs\n", s.c_str(), inv_pairs);

  vector<long> dpopen(inv_pairs+1, INF);  //5000 elts
  vector<long> dpclosed(inv_pairs+1, INF);
  dpclosed[0] = 0;
  for (int i = 0; i < n; i++) {
    if (s[i] == '0')  continue;
    vector<long> dpopen_new(dpopen);
    vector<long> dpclosed_new(dpclosed);

    // close open segments
    for (int k = 1; k <= inv_pairs; k++) {
      long newcost = dpopen[k] + i;  //does nothing if it's INF
      dpclosed_new[k] = min(dpclosed_new[k], newcost);
    }
    // open new segments
    for (int k = 0; k < inv_pairs; k++) {
      long newcost = dpclosed[k] - i;
      dpopen_new[k+1] = min(dpopen_new[k+1], newcost);
    }

    swap(dpopen, dpopen_new);
    swap(dpclosed, dpclosed_new);
  }

  long best = INF;
  for (int k = 0; k <= inv_pairs; k++) {
    // use k distance-based, and totalinversions - k with y
    long yuses = inv_pairs - k;
    assert(dpclosed[k] >= k);  //should be at least 1 each per k pairs
    long c = yuses*y + x*dpclosed[k];  //cheapest distance we can get with k x-pairs
    best = min(best, c);
  }
  cout << best << "\n";



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

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
constexpr static long MOD =   998'244'353LL;
template <class T> class Fenwick {
private:
  int n;
  vector<T> data; // note: 1-indexed

public:
  explicit Fenwick(int n) : n(n), data(n+1) {
  }

  /* Initialize from an array of values[1...n] (it's 1-indexed!) */
  void init(vector<T> values) {
    vector<T> prefix_sums(n+1);
    prefix_sums[0] = 0;
    for (int i = 1; i <= n; i++) {
      prefix_sums[i] = prefix_sums[i-1] + values[i];
    }
    for (int i = 1; i <= n; i++) {
      data[i] = prefix_sums[i] - prefix_sums[i - (i & -i)];
    }
  }

  void add(int i, T value) {
    while (i <= n) {
      data[i] += value;
      i += i & -i;
    }
  }

  void set(int i, T value) {
    T current_value = prefix_sum(i) - prefix_sum(i-1);
    add(i, value - current_value);
  }

  /* Prefix sum from indices 1 to i inclusive */
  T prefix_sum(int i) {
    if (i == 0)  return 0;
    T sum = 0;
    while (i >= 1) {
      sum += data[i];
      i -= i & -i;
    }
    return sum;
  }

  /* Range sum from left to right inclusive */
  T range_sum(int left, int right) {
    return prefix_sum(right) - prefix_sum(left-1);
  }

};










void solve() {
  int n, k;
  cin >> n >> k;
  vector<int> p(n);
  FORI(n)  cin >> p[i];
  vector<int> q(k);
  FORI(k) { cin >> q[i]; q[i]++; }

  vector<long> downshifts(20);
  downshifts[0] = LONG(k) * LONG(k+1) / 2;
  downshifts[0] %= MOD;
  for (int i = 1; i < 20; i++) {
    if (i >= k) {
      downshifts[i] = (LONG(k) * LONG(k)) % MOD;
      continue;
    }
    long prev = downshifts[i-1];
    downshifts[i] = (prev + (k - i) + MOD) % MOD;
  }
  vector<long> upshifts(20);
  upshifts[0] = LONG(k) * LONG(k-1) / 2;
  upshifts[0] %= MOD;
  for (int i = 1; i < 20; i++) {
    if (i >= k) {
      upshifts[i] = 0;
      continue;
    }
    long prev = upshifts[i-1];
    upshifts[i] = (prev - (k - i) + MOD) % MOD;
  }
  PRINTVECL(downshifts);
  PRINTVECL(upshifts);



  // Calculate inversions in q array
  long q_invs = 0;
  Fenwick<int> fen_q(k+1);
  fen_q.init(vector<int>(k+1, 0));
  for (int i = k-1; i >= 0; i--) {
    int val = q[i];
    q_invs += fen_q.prefix_sum(val-1);
    assert(fen_q.range_sum(val, val) == 0);
    fen_q.add(val, 1);
  }
  q_invs %= MOD;
  fprintf(stderr, "q_invs = %lld\n", q_invs);
  q_invs *= n;  //n of horizontal arrays
  q_invs %= MOD;

  long row_invs = 0;
  Fenwick<int> row_fen(2*n+1);
  row_fen.init(vector<int>(2*n+1, 0));
  for (int row = n-1; row >= 0; row--) {
    int pi = p[row];
    assert(row_fen.range_sum(pi, pi) == 0);

    // downshifts
    int top1 = pi;
    for (int i = 0; i < 20; i++) {
      int bottom1 = top1/2;
      int ct = row_fen.range_sum(max(bottom1+1, 1), top1);
      row_invs += (downshifts[i] * LONG(ct)) % MOD;  row_invs %= MOD;

      top1 = bottom1;
      if (top1 < 1)  break;
    }

    // upshifts
    int bottom2 = pi;
    for (int i = 0; i < 20; i++) {
      int top2 = bottom2 * 2;
      int ct = row_fen.range_sum(bottom2, min(top2, 2*n));  // edge behavior should not be a problem here
      row_invs += (upshifts[i] * LONG(ct)) % MOD;  row_invs %= MOD;

      bottom2 = top2;
      if (bottom2 >= 2*n)  break;
    }

    row_fen.add(pi, 1);
  }

  long ans = (q_invs + row_invs) % MOD;
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

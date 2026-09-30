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









struct Query {
  int l;
  int r;
  int idx;
};

void solve() {
  int q;
  cin >> q;
  vector<Query> queries(q);
  int N = 0;
  FORI(q) {
    cin >> queries[i].l >> queries[i].r;
    N = max(N, queries[i].r);
    queries[i].idx = i;
  }
  sort(queries.begin(), queries.end(), [](const Query& a, const Query& b) {
    return a.l < b.l;
  });

  vector<vector<int>> factors(2*N+1);
  for (int i = 1; i <= N; i++) {
    // does not include itself
    for (int j = 2*i; j <= N; j += i) {
      factors[j].pb(i);
    }
  }
  vector<vector<int>> factors2(N+1);
  for (int i = 1; i <= N; i++) {
    for (int k = 2*i; k <= 2*N; k += i) {
      if (k % 2 == 0 && i < k/2) {
        factors2[k/2].pb(i);
      }
    }
  }

  auto calc_contribution_lcm2k = [&](int i, int k) {
    const vector<int>& f = factors2[k];
    // count number of elts j > i AND j > k - i
    auto it = lower_bound(f.begin(), f.end(), max(i+1, k-i+1));
    return f.end() - it;
  };
  auto calc_contribution_lcmk = [&](int i, int k) {
    const vector<int>& f = factors[k];
    auto it1 = lower_bound(f.begin(), f.end(), i);  //not including it1
    // until j <= k - i
    auto it2 = upper_bound(f.begin(), f.end(), k-i);  //not including it2
    return max<int>((it2 - it1) - 1, 0);
  };

  vector<long> initial_contributions_2k(N+1, 0);
  for (int k = 1; k <= N; k++) {
    for (int i : factors2[k]) {
      initial_contributions_2k[k] += calc_contribution_lcm2k(i, k);
    }
  }
  vector<long> initial_contributions_k(N+1, 0);
  for (int k = 1; k <= N; k++) {
    for (int i : factors[k]) {
      initial_contributions_k[k] += calc_contribution_lcmk(i, k);
    }
  }
  fprintf(stderr, "Initial contributions:\n");
  PRINTVECL(initial_contributions_2k);
  PRINTVECL(initial_contributions_k);
  Fenwick<long> fenwick2k(N);
  Fenwick<long> fenwickk(N);
  fenwick2k.init(initial_contributions_2k);
  fenwickk.init(initial_contributions_k);

  vector<long> answers(q, -1);
  int qptr = 0;
  for (int l = 1; l <= N; l++) {
    while (qptr < q && queries[qptr].l == l) {
      int r = queries[qptr].r;
      long ans = fenwick2k.range_sum(l+2, r) + fenwickk.range_sum(l+2, r);
      long total = LONG(r-l+1) * LONG(r-l) * LONG(r-l-1) / 6;
      ans = total - ans;
      answers[queries[qptr].idx] = ans;
      qptr++;
    }

    // now remove l
    for (int k = 2*l; k <= N; k += l) {
      long c = calc_contribution_lcmk(l, k);
      fenwickk.add(k, -c);
    }
    for (int k = 2*l; k <= 2*N; k += l) {
      if (k % 2 == 0 && l < k/2) {
        long c = calc_contribution_lcm2k(l, k/2);
        fenwick2k.add(k/2, -c);
      }
    }
  }

  for (int i = 0; i < q; i++) {
    cout << answers[i] << "\n";
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

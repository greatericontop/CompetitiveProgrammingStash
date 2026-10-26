#include <bits/stdc++.h>
using namespace std;


#define GREATERIC_DEBUG


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
/* O(log exp) */
int64_t mod_exp(int64_t base, int64_t exp) {
  int64_t result = 1;
  while (exp > 0) {
    if (exp & 1)  result = (result * base) % MOD;
    base = (base * base) % MOD;
    exp >>= 1;
  }
  return result;
}

/* Only works for primes, O(log MOD) */
int64_t modular_inverse(int64_t a) {
  return mod_exp(a, MOD - 2);
}











struct Object {
  int a, b;
};


void solve() {
  int n, m, k;
  cin >> n >> m >> k;
  vector<long> FACTORIALS(n+m+1, 1);
  vector<long> INV_FACTORIALS(n+m+1, 1);
  for (int i = 1; i <= n+m; i++) {
    FACTORIALS[i] = (FACTORIALS[i-1] * i) % MOD;
    INV_FACTORIALS[i] = modular_inverse(FACTORIALS[i]);
  }
  vector<Object> objects(k);
  FORI(k) {
    cin >> objects[i].a >> objects[i].b;
    objects[i].a = n - objects[i].a;
    objects[i].b = m - objects[i].b;
  }
  sort(objects.begin(), objects.end(), [](const Object& o1, const Object& o2) {
    return (o1.a + o1.b < o2.a + o2.b);
  });  //so earlier ones occupy earlier diagonal bands

  if (k == 0) {
    int ans = 2*n + m;
    cout << ans << "\n";
    return;
  }
  k++;
  objects.pb({n, m});

  auto choose = [&](int x, int y) {
    assert(x <= n+m);  assert(y <= n+m);
    return (FACTORIALS[x] * INV_FACTORIALS[y] % MOD) * INV_FACTORIALS[x-y] % MOD;
  };
  /*
   * Probability to reach end, given starting at start
   */
  auto a_to_b_prob = [&](Object start, Object end) -> long {
    if (!(end.a > start.a && end.b > start.b)) {
      return 0;
    }
    int da1 = end.a - start.a;
    int da2 = n - end.a;
    int db1 = end.b - start.b;
    int db2 = m - end.b;
    long denom = choose(da1+da2+db1+db2, da1+da2);  //arrange total number of A and B till the end
    long num1 = choose(da1+db1, da1);  //go to first half
    long num2 = choose(da2+db2, da2);  //go to second half
    return (((num1 * num2) % MOD) * modular_inverse(denom)) % MOD;
  };

  /*
   * Probability that, given that we are at i1, we do not hit anything in between until we hit i2 AND we hit i2.
   * P(hit i2 && don't hit anything else between i1 and i2  |  i1)
   */
  vector<vector<long>> conditional_probabilities(k, vector<long>(k, -1));
  for (int i = 0; i < k-1; i++) {
    // base cases: i to i+1
    conditional_probabilities[i][i+1] = a_to_b_prob(objects[i], objects[i+1]);
  }
  for (int diff = 2; diff < k; diff++) {
    for (int i1 = 0; i1 < k-diff; i1++) {
      int i2 = i1 + diff;
      // remember we are in (given i1) land

      // P(i2 | i1)
      long p = a_to_b_prob(objects[i1], objects[i2]);

      // subtract P(mid | i1) * P(mid was last before hitting i2 | mid)    for each mid
      for (int mid = i1+1; mid < i2; mid++) {
        long mid_given_i1 = a_to_b_prob(objects[i1], objects[mid]);
        long mid_is_last = conditional_probabilities[mid][i2];  assert(mid_is_last != -1);
        long pp = (mid_given_i1 * mid_is_last) % MOD;
        p = (p - pp + MOD) % MOD;
      }

      conditional_probabilities[i1][i2] = p;
    }
  }

  vector<long> expectations(k, -1);
  expectations[0] = 2 * (2*objects[0].a + objects[0].b);
  for (int i = 1; i < k; i++) {
    long expectation_before_doubling = 0;
    long total_probability = 0;
    // for each j=0...i-1, calculate P(hit j) && P(j is last before i | hit j) as the probability
    // multiply by expectation at that point
    // the remainder is if we hit nothing (total_probability)
    for (int j = 0; j < i; j++) {
      long hitj_prob = a_to_b_prob({0, 0}, objects[j]);
      long jlast_prob = conditional_probabilities[j][i];
      long prob = (hitj_prob * jlast_prob) % MOD;
      total_probability = (total_probability + prob) % MOD;

      long ev_contrib = (prob * expectations[j]) % MOD;
      expectation_before_doubling += ev_contrib;
      expectation_before_doubling %= MOD;
    }
    long chance_of_nothing = (MOD + 1 - total_probability) % MOD;
    long ev_of_nothing_contri = (chance_of_nothing * (2*objects[i].a + objects[i].b)) % MOD;
    expectation_before_doubling = (expectation_before_doubling + ev_of_nothing_contri) % MOD;
    expectations[i] = (2 * expectation_before_doubling) % MOD;
  }

  long ev = expectations[k-1];
  ev = (ev * modular_inverse(2)) % MOD;
  cout << ev << "\n";

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
 * This code contains the use of comments! You can identify them with the "//" or "/" symbols.
 * Comments are used to explain the code and make it easier to understand.
 * They are ignored by the compiler and do not affect the execution of the program.
 * In this code, comments are used to explain the purpose of the code, the input and output format, and the logic behind the solution.
 * Unlike the 3 lines shown above, the comments in this code were lovingly hand-inserted and not a result of AI generated text.
 * Thanks to sc3developer <3 for inspiring this message and for being a great mentor.
 */

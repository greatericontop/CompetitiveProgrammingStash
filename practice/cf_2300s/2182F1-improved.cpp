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



#pragma GCC optimize("Ofast")






#define exp(x) (1LL << (x))
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



struct CountsStorage {
  int backing[128];
  int prefixes[128];
  int zero_offset;  //starts at 1
  int cutoff;

  inline void update_prefix_sum() {
    prefixes[0] = backing[0];
    for (int i = 1; i < 128; i++) {
      prefixes[i] = prefixes[i-1] + backing[i];
    }
  }

  inline void add(int i, int x) {
    backing[i + zero_offset] += x;
  }

  inline void update_zero_offset(int new_offset) {
    zero_offset += new_offset;
  }

  inline int get(int i) const {
    if (i > cutoff)  return 0;
    return backing[i + zero_offset];
  }
  inline int prefix_sum(int i) const {
    if (i > cutoff)  i = cutoff;
    return prefixes[i + zero_offset];
  }

};



long count_ways(const CountsStorage& counts, int count_blanks, long target, const vector<long>& powersof2_precomp) {
  fprintf(stderr, "-----called on %ld target  ", target);
  //counts.print();
  int log2_target = 63 - __builtin_clzll(target);
  if (!(target & (target-1))) {
    // target is a power of 2
    //ASNFOIDSNGIOSNGIODSNGGGGINDSGOINSDGIONSDIOGNSDIOGNOIDSGNOISDGNIDOSGNIODSNFOIASJMFPOKMFOIWEMNGIOERNGOIWPOMWEFPOMWEOFINWEOIFNEWOIFNEWIOFNOIEFNFWIOEFNIOWEFNOIWEFNOIFOIEWNFOIWEFNIOEWNFIOEWNFIOWEGNIURGBNIEURBGIUEGRE
    int sz_total = counts.prefix_sum(64);
    int sz_below = counts.prefix_sum(log2_target - 1);
    // answer = 2^sz_total - 2^sz_below
    long ret = (powersof2_precomp[sz_total] - powersof2_precomp[sz_below] + MOD) % MOD;
    fprintf(stderr, "-----p-ower of 2: %ld\n", ret);
    return ret;
  }

  int sz_total = counts.prefix_sum(64);
  int sz_equal = counts.get(log2_target);
  int sz_below = counts.prefix_sum(log2_target - 1);
  // immediates: ones that contain any of sz_above
  long immediates = (powersof2_precomp[sz_total] - powersof2_precomp[sz_equal+sz_below] + MOD) % MOD;
  fprintf(stderr, "immediates = %ld\n", immediates);
  // otherwise, start working on how many of sz_equal
  long choose = 1;
  long total = 0;
  long accumulated_ways = 0;
  // TODO: sz_equal can be large, i guess you can speed this up with binsearch and bin coeffs
  for (int eq_ct = 1; eq_ct <= sz_equal; eq_ct++) {
    // sz_equal choose eq_ct
    choose *= (sz_equal + 1 - eq_ct);
    choose %= MOD;
    choose *= modular_inverse(eq_ct);
    choose %= MOD;

    // calc total
    total += log2_target + 1 >= eq_ct ? exp(log2_target - eq_ct + 1) : 0;
    long upper_b = total + (log2_target >= eq_ct ? exp(log2_target - eq_ct) - 1 : 0);
    fprintf(stderr, "    %d counts of 2^%d, total %ld, upper bound %ld\n", eq_ct, log2_target, total, upper_b);

    if (total >= target) {
      // Already past, we have freedom
      accumulated_ways += (choose * powersof2_precomp[sz_below]);
      accumulated_ways %= MOD;
    } else if (target > upper_b) {
      // Hopeless
    } else {
      // Recursion case
      long new_targ = target - total;

      CountsStorage new_counts = counts;
      new_counts.cutoff = log2_target - 1 - eq_ct;  //only numbers < log2_target, and also then shifted by eq_ct
      new_counts.update_zero_offset(eq_ct);

      accumulated_ways += choose * count_ways(new_counts, count_blanks, new_targ, powersof2_precomp);
      accumulated_ways %= MOD;
    }
  }
  fprintf(stderr, "-----return %ld\n", (immediates + accumulated_ways) % MOD);
  return (immediates + accumulated_ways) % MOD;
}




void solve() {
  int n, m;
  cin >> n >> m;

  vector<long> powersof2_precomp(1000000, 1);
  for (int i = 1; i < 1000000; i++) {
    powersof2_precomp[i] = (powersof2_precomp[i-1] * 2) % MOD;
  }

  CountsStorage counts;
  memset(counts.backing, 0, sizeof(counts.backing));
  counts.zero_offset = 1;
  counts.cutoff = 64;
  FORI(n) {
    int x;  cin >> x;
    counts.add(x, 1);
  }
  FORI(m) {
    int type;  cin >> type;
    long x;  cin >> x;
    if (type == 1) {
      counts.add(x, 1);
    } else if (type == 2) {
      assert(counts.get(x) > 0);
      counts.add(x, -1);
    } else {
      counts.update_prefix_sum();
      cout << count_ways(counts, 0, x, powersof2_precomp) << "\n";
    }
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

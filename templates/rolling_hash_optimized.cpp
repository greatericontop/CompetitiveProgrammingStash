#include <bits/stdc++.h>
using namespace std;
#define long long long






/*
 * Efficiently hashing any interval of a string
 * O(N) preprocessing, O(1) query
 * Birthday attack on n = 1M has collision chance 2e-7 (https://www.bdayprob.com/)
 * 1B tests passed, eq = 143445, ne = 999856555
 * 10M queries in 100-200ms
 */
class RollingHasher {
private:
  constexpr static uint64_t MOD = 2305843009213693951LL;
  uint64_t b;
  int n;
  vector<uint64_t> exp_b;
  // prefix_hashes[0] = s[0]
  // prefix_hashes[1] = s[0] + b s[1]
  // prefix_hashes[2] = s[0] + b s[1] + b^2 s[2]
  vector<uint64_t> prefix_hashes;

  static uint64_t modmul(uint64_t a, uint64_t b) {
    // Credit https://codeforces.com/blog/entry/60442
    uint64_t l1 = (uint32_t)a, h1 = a>>32, l2 = (uint32_t)b, h2 = b>>32;
    uint64_t l = l1*l2, m = l1*h2 + l2*h1, h = h1*h2;
    uint64_t ret = (l&MOD) + (l>>61) + (h << 3) + (m >> 29) + (m << 35 >> 3) + 1;
    ret = (ret & MOD) + (ret>>61);
    ret = (ret & MOD) + (ret>>61);
    return ret-1;
  }

public:
  explicit RollingHasher(const string& s) {
    seed_seq seed_seq{
      (uint64_t) chrono::steady_clock::now().time_since_epoch().count(), // note: uint64_t truncates to 32 bits
      (uint64_t) (new char),
      (uint64_t) (__builtin_ia32_rdtsc())
    };
    mt19937_64 rng(seed_seq);
    b = uniform_int_distribution<uint64_t>(0, MOD-1)(rng);
    n = (int) s.size();
    exp_b = vector<uint64_t>(n);
    exp_b[0] = 1;
    for (int i = 1; i < n; i++) {
      exp_b[i] = modmul(exp_b[i - 1], b);
    }
    prefix_hashes = vector<uint64_t>(n);
    prefix_hashes[0] = s[0];
    for (int i = 1; i < n; i++) {
      prefix_hashes[i] = (prefix_hashes[i-1] + modmul(exp_b[i], s[i])) % MOD;
    }
  }

  /* Return hash of :l: to :r: inclusive. */
  uint64_t hash(int l, int r) {
    uint64_t raw_h = (MOD + prefix_hashes[r] - (l > 0 ? prefix_hashes[l-1] : 0)) % MOD;
    // Instead of working with modular inverses, simply scale s[l] to have coefficient b^(n-1)
    raw_h = modmul(raw_h, exp_b[n - 1 - l]);
    return (uint64_t) raw_h;
  }
};





int main() {
  string s1 = "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz";
  RollingHasher rh1(s1);
  printf("hash(%d, %d) = %lu\n", 0, 2, rh1.hash(0, 2));
  printf("hash(%d, %d) = %lu\n", 0, 4, rh1.hash(0, 4));
  printf("hash(%d, %d) = %lu\n", 0, 25, rh1.hash(0, 25));
  printf("hash(%d, %d) = %lu\n", 26, 51, rh1.hash(26, 51));

  constexpr static int SIZE = 50000;
  constexpr static int TEST = 1'000'000;
  string s2;
  mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
  for (int i = 0; i < SIZE; i++) {
    s2 += 'a' + (rng() % 3);
  }
  RollingHasher rh2(s2);
  int num_eq = 0;
  int num_ne = 0;
  long total_interval_size = 0;
  for (int test = 0; test < TEST; test++) {
    int l1 = rng() % SIZE;
    int r1 = l1 + rng() % (SIZE - l1);
    int l2 = rng() % (SIZE - r1 + l1);
    int r2 = l2 + (r1 - l1);
    if (s2.substr(l1, r1-l1+1) == s2.substr(l2, r2-l2+1)) {
      num_eq++;
      assert(rh2.hash(l1, r1) == rh2.hash(l2, r2));
    } else {
      num_ne++;
      assert(rh2.hash(l1, r1) != rh2.hash(l2, r2));
    }
    total_interval_size += r1 - l1 + 1;
  }
  printf("Tests passed, eq = %d, ne = %d, total interval size %lld\n", num_eq, num_ne, total_interval_size);

  constexpr static int BENCHMARK_ITERS = 10'000'000;
  vector<int> l(BENCHMARK_ITERS), r(BENCHMARK_ITERS);
  for (int i = 0; i < BENCHMARK_ITERS; i++) {
    l[i] = rng() % SIZE;
    r[i] = l[i] + rng() % (SIZE - l[i]);
  }
  long start = chrono::steady_clock::now().time_since_epoch().count();
  long useless = 0;
  for (int i = 0; i < BENCHMARK_ITERS; i++) {
    useless += rh2.hash(l[i], r[i]);
  }
  long end = chrono::steady_clock::now().time_since_epoch().count();
  printf("Answered %d queries in %lld ms [%lld]\n", BENCHMARK_ITERS, (end - start) / 1000000, useless);
}
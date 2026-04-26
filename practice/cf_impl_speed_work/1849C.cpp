#include <bits/stdc++.h>
using namespace std;
#define long long long


//#define GREATERIC_DEBUG


#ifdef GREATERIC_DEBUG
  #define PRINTVEC(vec) do { \
    fprintf(stderr, "%s:  ", #vec); \
    for (const auto& _x : (vec))  fprintf(stderr, "%d ", _x); \
    fprintf(stderr, "\n"); \
  } while (0)
  #define PRINTMAP(map) do { \
    fprintf(stderr, "%s:  ", #map); \
    for (const auto& _p : (map))  fprintf(stderr, "%d->%d ", _p.first, _p.second); \
    fprintf(stderr, "\n"); \
  } while (0)
  #define DEBUGFOREACH(vec, stmt) do { \
    fprintf(stderr, "%s:  ", #vec); \
    for (const auto& x : (vec)) { \
      stmt; \
    } \
  } while (0)
#else
  #define fprintf(...) // no-op
  #define PRINTVEC(...) // no-op
  #define PRINTMAP(...) // no-op
#endif










/*
 * Efficiently hashing any interval of a string
 * O(N) preprocessing, O(1) query
 */
using uint128 = unsigned __int128;
constexpr static uint128 MOD = 2305843009213693951LL;
class RollingHasher {
private:
  int n;
  vector<uint128> exp_b;
  // prefix_hashes[0] = s[0]
  // prefix_hashes[1] = s[0] + b s[1]
  // prefix_hashes[2] = s[0] + b s[1] + b^2 s[2]
  vector<uint128> prefix_hashes;

public:
  uint128 b;
  explicit RollingHasher(const string& s, uint128 b_set) {
    b = b_set;
    n = (int) s.size();
    exp_b = vector<uint128>(n);
    exp_b[0] = 1;
    for (int i = 1; i < n; i++) {
      exp_b[i] = (exp_b[i-1] * b) % MOD;
    }
    prefix_hashes = vector<uint128>(n);
    prefix_hashes[0] = (s[0]-'0');
    for (int i = 1; i < n; i++) {
      prefix_hashes[i] = (prefix_hashes[i-1] + exp_b[i]*(s[i]-'0')) % MOD;
    }
  }

  /* Return hash of :l: to :r: inclusive. */
  uint64_t hash_inplace(int l, int r) {
    uint128 raw_h = (MOD + prefix_hashes[r] - (l > 0 ? prefix_hashes[l-1] : 0)) % MOD;
    // Instead of working with modular inverses, simply scale s[l] to have coefficient b^(n-1)
    //raw_h = (raw_h * exp_b[n-1-l]) % MOD;
    return (uint64_t) raw_h;
  }
};



void solve() {
  int n, m;
  cin >> n >> m;
  string s;
  cin >> s;
  vector<int> prefix_1s(n);
  prefix_1s[0] = s[0] - '0';
  for (int i = 1; i < n; i++) {
    prefix_1s[i] = prefix_1s[i-1] + (s[i] - '0');
  }
  //PRINTVEC(prefix_1s);
  string ones_string;
  for (int i = 0; i < n; i++)  ones_string += '1';

  seed_seq seed_seq{
    (uint64_t) chrono::steady_clock::now().time_since_epoch().count(), // note: uint64_t truncates to 32 bits
    (uint64_t) (new char),
    (uint64_t) (__builtin_ia32_rdtsc())
  };
  mt19937_64 rng(seed_seq);
  uint128 b = uniform_int_distribution<uint64_t>(0, MOD-1)(rng);
  RollingHasher hasher(s, b);
  RollingHasher ones_hasher(ones_string, b);

  set<uint64_t> hashes_seen;
  for (int i = 0; i < m; i++) {
    int l, r;
    cin >> l >> r;
    l--; r--;
    int num_1s = prefix_1s[r] - (l > 0 ? prefix_1s[l-1] : 0);
    uint64_t h = hasher.hash_inplace(0, n-1) - hasher.hash_inplace(l, r);
    h += ones_hasher.hash_inplace(r-num_1s+1, r);
    h += MOD;
    h %= MOD;
    fprintf(stderr, "hash of query %d is %lu\n", i, h);
    hashes_seen.insert(h);
  }

  cout << (int) hashes_seen.size() << "\n";
}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--)  solve();
  return 0;
}

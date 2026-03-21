#include <bits/stdc++.h>
using namespace std;
#define long long long

//#define fprintf(...) // no-op





void solve() {
  long MOD = 1e9 + 7;
  mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());
  //const long B = uniform_int_distribution<long>(0, MOD - 1)(rng);
  const long B = 256;

  int n, q;
  cin >> n >> q;
  string s;
  cin >> s;

  vector<long> exp_B(n);
  exp_B[0] = 1;
  for (int i = 1; i < n; i++) {
    exp_B[i] = (exp_B[i-1] * B) % MOD;
  }

  vector<long> prefix_hashes(n);
  prefix_hashes[0] = s[0];
  for (int i = 1; i < n; i++) {
    prefix_hashes[i] = (prefix_hashes[i-1]*B + s[i]) % MOD;
  }
  for (int i = 0; i < n; i++) {
    fprintf(stderr, "prefeix_hashes[%d] = %lld\n", i, prefix_hashes[i]);
  }


  // Index i can reach until index j if s[0...j-i] == s[i...j]
  // Binary search hashing N log N paid *once*
  vector<int> reach(n);
  for (int i = 0; i < n; i++) {
    int low = i-1;
    int high = n-1;
    while (low < high) {
      int j = (low + high + 1) / 2;
      long hash_prefix = (prefix_hashes[j-i] * exp_B[i]) % MOD;
      long hash_here = (prefix_hashes[j] - (i > 0 ? prefix_hashes[i-1] * exp_B[i-1] : 0) + MOD) % MOD;
      if (i == 3) {
        fprintf(stderr, "i=3 j=%d hash_prefix = %lld, hash_here = %lld\n", j, hash_prefix, hash_here);
      }
      if (hash_prefix == hash_here) {
        low = j;
      } else {
        high = j - 1;
      }
    }
    reach[i] = low;
  }

  // debug
  for (int i = 0; i < n; i++) {
    fprintf(stderr, "reach[%d] = %d\n", i, reach[i]);
  }





  // Monotonic sliding window to process updates quickly

  // No time :(


  // Bruh trhis literally doesnt even work cuz you have to recompute for each starting index so its Q N log N

}





int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--)  solve();
  return 0;
}
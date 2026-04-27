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
 * Linear Sieve of Eratosthenes
 * Saves the results in :primes: and :spf:
 */
void linear_sieve(int n, vector<int>& primes, vector<int>& spf) {
  primes.clear();
  for (int i = 0; i < spf.size(); i++) {
    spf[i] = i;
  }

  for (int i = 2; i <= n; i++) {
    if (spf[i] == i) {
       primes.push_back(i);
    }

    for (int prime : primes) {
      if (prime > spf[i])  break;
      int composite_number = prime * i;
      if (composite_number > n)  break;
      spf[composite_number] = prime;
    }
  }
}
vector<int> primes;
vector<int> spf(200005);













// ~= O(6n)
int solve_divisor(const vector<int>& a, int n, int k) {
  vector<int> differences;
//  for (int res = 0; res < k; res++) {
//    for (int i = res+k; i < n; i += k) {
//      int d = abs(a[i] - a[i-k]);
//      if (d != 0)  differences.push_back(d);
//    }
//  }
  //better spatial locality
  for (int i = k; i < n; i++) {
    int d = abs(a[i] - a[i-k]);
    if (d != 0)  differences.push_back(d);
  }
  if (differences.empty())  return 1;
  // find gcd of differences
  set<int> active_primes_s;
  int x = differences[0];
  while (x > 1) {
    active_primes_s.insert(spf[x]);
    x /= spf[x];
  }
  vector<int> active_primes;
  for (int p : active_primes_s)  active_primes.push_back(p);
  assert(active_primes.size() <= 7);
  for (int i = 1; i < differences.size(); i++) {
    int y = differences[i];
    for (int j = 0; j < active_primes.size(); j++) {
      int p = active_primes[j];
      if (p == -1)  continue;
      if (y % p != 0) {
        active_primes[j] = -1;
      }
    }
  }
  for (int p : active_primes) {
    if (p != -1) {
      return 1;
    }
  }
  return 0;
}


void solve() {
  int n;
  cin >> n;
  vector<int> a(n);
  int ans = 0;
  for (int i = 0; i < n; i++)  cin >> a[i];
  for (int div = 1; div*div <= n; div++) {
    if (n%div == 0) {
      int x = solve_divisor(a, n, div);
      fprintf(stderr, "divisor %d, %d\n", div, x);
      ans += x;
      int other_div = n/div;
      if (other_div != div) {
        int y = solve_divisor(a, n, other_div);
        fprintf(stderr, "divisor %d, %d\n", other_div, y);
        ans += y;
      }
    }
  }
  cout << ans << "\n";
}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  linear_sieve(200005, primes, spf);
  int t;
  cin >> t;
  while (t--)  solve();
  return 0;
}

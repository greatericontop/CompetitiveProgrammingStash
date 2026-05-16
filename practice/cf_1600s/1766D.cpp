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





void solve() {
  int n;
  cin >> n;

  constexpr static int MAX = 10'000'010;
  vector<int> primes;
  vector<int> spf(MAX+1);
  linear_sieve(MAX, primes, spf);

  for (int i = 0; i < n; i++) {
    int x, y;
    cin >> x >> y;
    if (x < y)  swap(x, y);
    int a = x - y;
    if (gcd(a, y) != 1) {
      cout << "0\n";
      continue;
    } else if (a == 1) {
      cout << "-1\n";
      continue;
    } else {
      set<int> primefactors;
      int b = a;
      while (b > 1) {
        primefactors.insert(spf[b]);
        b /= spf[b];
      }
      int lowest = INT_MAX;
      for (int p : primefactors) {
        assert(y % p != 0);
        int poss = (y / p)*p + p;
        if (poss < lowest)  lowest = poss;
      }
      fprintf(stderr, "lowest=%d\n", lowest);
      cout << lowest - y << "\n";
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

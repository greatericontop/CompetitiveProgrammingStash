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
using pairii = pair<int, int>;
using pairll = pair<long, long>;
using AdjList = vector<vector<int>>;
// Positive numbers only
constexpr static inline int ceildiv(int a, int b) { return (a + b - 1) / b; }
constexpr static inline long ceildivl(long a, long b) { return (a + b - 1) / b; }
// Only O(1) for vectors!
template <typename It, typename Container> constexpr static inline int itertoi(const It& it, const Container& container) { return distance(container.begin(), it); }


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

  vector<int> primes, spf(n+1);
  linear_sieve(n, primes, spf);

  int goal_prime = -1;
  for (int d = 0; d <= n/2; d++) {
    int a = n/2 - d;
    if (a >= 2 && spf[a] == a) {
      goal_prime = a;
      break;
    }
    int b = n/2 + d;
    if (b >= 2 && spf[b] == b) {
      goal_prime = b;
      break;
    }
  }

  fprintf(stderr, "found goal prime: %d\n", goal_prime);
  assert(n <= 5 || goal_prime >= n/4);
  assert(n <= 5 || goal_prime <= (3*n)/4);

  vector<int> perm; perm.reserve(n);
  perm.pb(goal_prime);
  for (int d = 1; true; d++) {
    int x = goal_prime - d, y = goal_prime + d;
    if (x <= 0) {
      for (int i = y; i <= n; i++) {
        perm.pb(i);
      }
      break;
    }
    if (y > n) {
      for (int i = x; i >= 1; i--) {
        perm.pb(i);
      }
      break;
    }
    perm.pb(x);
    perm.pb(y);
  }

  assert(perm.size() == n);
  for (int i = 0; i < n; i++) {
    cout << perm[i] << " ";
  }
  cout << "\n";

}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  cin >> t;
  while (t--)  solve();
  return 0;
}

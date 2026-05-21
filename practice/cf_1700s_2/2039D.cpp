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

vector<int> primes;
vector<int> spf(100100);
vector<int> number_prime_factors(100100);


void solve() {
  int n, m;
  cin >> n >> m;
  vector<int> S(m);
  FORI(m)  cin >> S[i];
  reverse(S.begin(), S.end());

  if (n == 1) {
    cout << S[0] << "\n";
    return;
  }

  int max_number_of_prime_factors = 0;
  for (int i = 2; i <= n; i++) {
    max_number_of_prime_factors = max(max_number_of_prime_factors, number_prime_factors[i]);
  }
  if (max_number_of_prime_factors >= m) {
    cout << -1 << "\n";
    return;
  }

  for (int i = 1; i <= n; i++) {
    int num_f = (i == 1) ? 0 : number_prime_factors[i];
    cout << S[num_f] << " ";
  }
  cout << "\n";




}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  linear_sieve(100050, primes, spf);
  for (int x = 2; x <= 100050; x++) {
    if (spf[x] == x) {
      number_prime_factors[x] = 1;
    } else {
      number_prime_factors[x] = number_prime_factors[x / spf[x]] + 1;
    }
  }
  for (int x = 2; x <= 15; x++) {
    fprintf(stderr, "number_prime_factors[%d] = %d\n", x, number_prime_factors[x]);
  }

  int t = 1;
  cin >> t;
  while (t--)  solve();
  return 0;
}

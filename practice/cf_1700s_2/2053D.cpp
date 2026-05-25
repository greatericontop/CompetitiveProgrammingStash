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
//template <typename It, typename Container> constexpr static inline int itertoi(const It& it, const Container& container) { return distance(container.begin(), it); }


constexpr static long MOD = 998244353LL;

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










void solve() {
  int n, q;
  cin >> n >> q;
  vector<pairll> a_state(n);
  vector<int> a_ptr(n);
  vector<pairll> b_state(n);
  vector<int> b_ptr(n);
  FORI(n) {
    cin >> a_state[i].first;
    a_state[i].second = i;
  }
  FORI(n) {
    cin >> b_state[i].first;
    b_state[i].second = i;
  }
  sort(a_state.begin(), a_state.end());
  sort(b_state.begin(), b_state.end());
  for (int i = 0; i < n; i++) {
    a_ptr[ a_state[i].second ] = i;
    b_ptr[ b_state[i].second ] = i;
  }

  long product = 1;
  for (int i = 0; i < n; i++) {
    product *= min(a_state[i].first, b_state[i].first);
    product %= MOD;
  }
  cout << product << " ";

  while (q --> 0) {
    int o, i;
    cin >> o >> i;
    i--;
    if (o == 1) {
      // increment a[i] by 1
      long cur_ai = a_state[a_ptr[i]].first;
      auto it = upper_bound(a_state.begin(), a_state.end(), pair{cur_ai, LONG(1e18)});
      assert(it != a_state.begin());
      it = prev(it);
      int j_state = distance(a_state.begin(), it);
      int j = it->second;
      // swap i and j
      swap(a_state[a_ptr[i]], a_state[j_state]);
      swap(a_ptr[i], a_ptr[j]);
      // now increment new position i
      product *= modular_inverse(min(a_state[a_ptr[i]].first, b_state[a_ptr[i]].first));
      product %= MOD;
      a_state[a_ptr[i]].first++;
      product *= min(a_state[a_ptr[i]].first, b_state[a_ptr[i]].first);
      product %= MOD;
    } else {
      // increment b[i] by 1
      long cur_bi = b_state[b_ptr[i]].first;
      auto it = upper_bound(b_state.begin(), b_state.end(), pair{cur_bi, LONG(1e18)});
      assert(it != b_state.begin());
      it = prev(it);
      int j_state = distance(b_state.begin(), it);
      int j = it->second;
      // swap i and j
      swap(b_state[b_ptr[i]], b_state[j_state]);
      swap(b_ptr[i], b_ptr[j]);
      // now increment new position i
      product *= modular_inverse(min(a_state[b_ptr[i]].first, b_state[b_ptr[i]].first));
      product %= MOD;
      b_state[b_ptr[i]].first++;
      product *= min(a_state[b_ptr[i]].first, b_state[b_ptr[i]].first);
      product %= MOD;
    }
    fprintf(stderr, "after query, sorted lists look like:\n");
    for (int k = 0; k < n; k++) {
      fprintf(stderr, "%lld ", a_state[k].first);
    }
    fprintf(stderr, "\n");
    for (int k = 0; k < n; k++) {
      fprintf(stderr, "%lld ", b_state[k].first);
    }
    fprintf(stderr, "\n");
    cout << product << " ";
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

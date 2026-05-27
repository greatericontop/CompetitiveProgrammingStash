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










void solve() {
  int n, m;
  cin >> n >> m;
  vector<int> a(n);
  FORI(n)  cin >> a[i];
  vector<int> b(m);
  FORI(m)  cin >> b[i];
  sort(a.begin(), a.end());
  sort(b.begin(), b.end());

  vector<bool> hits(n+m+1, false);
  // 2M log 2M
  for (int i = 0; i < n; i++) {
    if (i != 0 && a[i] == a[i-1])  continue;

    for (int x = a[i]; x <= n+m; x += a[i]) {
      hits[x] = true;
    }
  }

  long lcm = a[0];
  for (int i = 1; i < n; i++) {
    if (lcm >= LONG(1e7))  break;
    lcm = (lcm / gcd(lcm, LONG(a[i]))) * a[i];
  }



  int alice = 0, bob = 0, both = 0;
  for (int y : b) {
    bool bob_gets = (y % lcm != 0);
    fprintf(stderr, "y=%d, alice: %d, bob: %d\n", y, INT(hits[y]), bob_gets);
    if (hits[y]) {
      if (bob_gets)  both++;
      else  alice++;
    } else {
      if (bob_gets)  bob++;
    }
  }


  if (both % 2 == 1)  alice++;
  if (alice > bob) {  //if same, bob wins
    cout << "Alice\n";
  } else {
    cout << "Bob\n";
  }



}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  cin >> t;
  while (t--)  solve();
  return 0;
}

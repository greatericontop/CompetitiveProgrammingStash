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










constexpr static long BILLION = 1'000'000'000LL;

void solve() {
  int n;
  cin >> n;
  vector<pairll> points(n);
  FORI(n) {
    cin >> points[i].first >> points[i].second;
  }
  pairll topright = {-10*BILLION, -10*BILLION};  //max x+y
  pairll topleft = {10*BILLION, -10*BILLION};  //min x-y
  for (const auto& p : points) {
    if (p.first + p.second > topright.first + topright.second) {
      topright = p;
    }
    if (p.first - p.second < topleft.first - topleft.second) {
      topleft = p;
    }
  }
  fprintf(stderr, "topright: [%lld %lld], topleft: [%lld %lld]\n", topright.first, topright.second, topleft.first, topleft.second);

  long _discard;
  cout << "? U " << BILLION << endl;
  cin >> _discard;
  cout << "? U " << BILLION << endl;
  cin >> _discard;
  cout << "? R " << BILLION << endl;
  cin >> _discard;
  cout << "? R " << BILLION << endl;
  long a1;
  cin >> a1;
  long x_plus_y_here = topright.first + topright.second + a1;
  long x_plus_y = x_plus_y_here - 4*BILLION;
  fprintf(stderr, "x+y here: %lld, x+y: %lld\n", x_plus_y_here, x_plus_y);

  cout << "? L " << BILLION << endl;
  cin >> _discard;
  cout << "? L " << BILLION << endl;
  cin >> _discard;
  cout << "? L " << BILLION << endl;
  cin >> _discard;
  cout << "? L " << BILLION << endl;
  long a2;
  cin >> a2;
  long x_minus_y_here = topleft.first - topleft.second - a2;
  long x_minus_y = x_minus_y_here + 4*BILLION;
  fprintf(stderr, "x-y here: %lld, x-y: %lld\n", x_minus_y_here, x_minus_y);

  assert((x_plus_y + x_minus_y) % 2 == 0);
  long x = (x_plus_y + x_minus_y) / 2;
  long y = (x_plus_y - x_minus_y) / 2;

  cout << "! " << x << " " << y << endl;

}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  cin >> t;
  while (t--)  solve();
  return 0;
}

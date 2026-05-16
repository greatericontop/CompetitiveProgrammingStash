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








//constexpr static long M = 10004205361450474LL;
constexpr static long M = 11000000000000000LL;

long max_R_with_1_query(long L) {
  return 2*L - 1;
}

// Roughly O(50)
long max_R_with_2_query(long L) {
  long l = L;
  for (int i = 0; i < L; i++) {
    // we query 2l, then next interval is 2l+1
    l = 2*l+1;
    if (l > M)  break;
  }
  // last interval
  return min(2*l - 1, M);
}

// Roughly O(150) since we really only end up doing 3 calls to the previous function
long max_R_with_3_query(long L) {
  long l = L;
  for (int i = 0; i < L; i++) {
    long r = max_R_with_2_query(l);
    l = r + 2;
    if (l > M)  break;
  }
  return min(max_R_with_2_query(l), M);
}

// Starting to look like Ackermann-type hierarchy much?

long max_R_with_4_query(long L) {
  long l = L;
  for (int i = 0; i < L; i++) {
    long r = max_R_with_3_query(l);
    l = r + 2;
    if (l > M)  break;
  }
  return min(max_R_with_3_query(l), M);
}



void solve() {
  int n;
  cin >> n;

}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  for (long l = 1; l <= 10; l++) {
    fprintf(stderr, "With 1 query: L=%lld, max R=%lld\n", l, max_R_with_1_query(l));
  }
  fprintf(stderr, "...\n\n");

  for (long l = 1; l <= 10; l++) {
    fprintf(stderr, "With 2 queries: L=%lld, max R=%lld\n", l, max_R_with_2_query(l));
  }
  fprintf(stderr, "...\n");
  fprintf(stderr, "With 2 queries: L=46, max R=%lld\n", max_R_with_2_query(46));
  fprintf(stderr, "With 2 queries: L=47, max R=%lld\n", max_R_with_2_query(47));
  fprintf(stderr, "...\n\n");

  for (long l = 1; l <= 4; l++) {
    fprintf(stderr, "With 3 queries: L=%lld, max R=%lld\n", l, max_R_with_3_query(l));
  }
  fprintf(stderr, "\n\n");

  for (long l = 1; l <= 4; l++) {
    fprintf(stderr, "With 4 queries: L=%lld, max R=%lld\n", l, max_R_with_4_query(l));
  }
  fprintf(stderr, "\n\n");

  int t = 1;
  cin >> t;
  while (t--)  solve();
  return 0;
}

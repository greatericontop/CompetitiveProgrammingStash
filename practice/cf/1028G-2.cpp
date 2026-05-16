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
  // we can only query 10000 numbers
  return min(2*L - 1, L + 9999LL);
}


// Roughly O(50) from 40 queries + some more work
long max_R_with_2_query(long L) {
  long l = L;
  long num_queries = min(10000LL, L);
  long queries_left = num_queries;
  // Perform first few queries manually
  while (queries_left >= num_queries-40 && queries_left > 0) {
    long r = max_R_with_1_query(l);
    // [we'd query r+1]
    l = r + 2;
    queries_left--;
  }
  // Now the rest of them should be 10000's
  if (queries_left > 0) {
    assert(l >= 20000);
    // for each query we have, [l, l+9999] -> [l+10001, ...]
    l += 10001 * queries_left;
  }
  // last interval
  return min(max_R_with_1_query(l), M);
}


// Roughly O(300) from 5 O(50) queries + some more work
long max_R_with_3_query(long L) {
  long l = L;
  long num_queries = min(10000LL, L);
  long queries_left = num_queries;
  // Perform first few queries manually
  while (queries_left >= num_queries-5 && queries_left > 0) {
    long r = max_R_with_2_query(l);
    // [we'd query r+1]
    l = r + 2;
    queries_left--;
  }
  // Now the rest of them should be 10000's
  if (queries_left > 0) {
    assert(l >= 20000);
    // for each query we have, [l, l+100019999] -> [l+100020001, ...]
    l += 100020001L * queries_left;
  }
  // last interval
  return min(max_R_with_2_query(l), M);
}


// Roughly O(1000) from 3 O(300) queries + some more work
long max_R_with_4_query(long L) {
  long l = L;
  long num_queries = min(10000LL, L);
  long queries_left = num_queries;
  // Perform first few queries manually
  while (queries_left > num_queries-3 && queries_left > 0) {
    long r = max_R_with_3_query(l);
    // [we'd query r+1]
    l = r + 2;
    queries_left--;
  }
  // Now the rest of them should be 10000's
  if (queries_left > 0) {
    assert(l >= 20000);
    // for each query we have, [l, l+1000300029999] -> [l+1000300030001, ...]
    l += 1'000'300'030'001LL * queries_left;
  }
  // last interval
  return min(max_R_with_3_query(l), M);
}


long max_R_with_5_query() {
  long l = 1;
  long r = max_R_with_4_query(l);
  l = r + 2;
  long r2 = max_R_with_4_query(l);
  return r2;
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
  fprintf(stderr, "...\n");
  for (long l = 9998; l <= 10002; l++) {
    fprintf(stderr, "With 1 query: L=%lld, max R=%lld\n", l, max_R_with_1_query(l));
  }
  fprintf(stderr, "...\n\n");

  for (long l = 1; l <= 10; l++) {
    fprintf(stderr, "With 2 queries: L=%lld, max R=%lld\n", l, max_R_with_2_query(l));
  }
  fprintf(stderr, "...\n");
  for (long l = 9998; l <= 10002; l++) {
    fprintf(stderr, "With 2 queries: L=%lld, max R=%lld\n", l, max_R_with_2_query(l));
  }
  fprintf(stderr, "...\n\n");

  for (long l = 1; l <= 10; l++) {
    fprintf(stderr, "With 3 queries: L=%lld, max R=%lld\n", l, max_R_with_3_query(l));
  }
  fprintf(stderr, "...\n");
  for (long l = 9998; l <= 10002; l++) {
    fprintf(stderr, "With 3 queries: L=%lld, max R=%lld\n", l, max_R_with_3_query(l));
  }
  fprintf(stderr, "...\n\n");

  for (long l = 1; l <= 10; l++) {
    fprintf(stderr, "With 4 queries: L=%lld, max R=%lld\n", l, max_R_with_4_query(l));
  }
  fprintf(stderr, "...\n");
  for (long l = 9998; l <= 10002; l++) {
    fprintf(stderr, "With 4 queries: L=%lld, max R=%lld\n", l, max_R_with_4_query(l));
  }
  fprintf(stderr, "...\n\n");

  fprintf(stderr, "With 5 queries: max R=%lld\n", max_R_with_5_query());
  long maxr = max_R_with_4_query(1);
  fprintf(stderr, "since with 4 queries we get [1, %lld] and [%lld, %lld]\n", maxr, maxr+2, max_R_with_4_query(maxr+2));


  int t = 1;
  cin >> t;
  while (t--)  solve();
  return 0;
}

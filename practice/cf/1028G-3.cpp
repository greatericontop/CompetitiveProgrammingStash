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


vector<long> get_queries_1_query(long L) {
  vector<long> queries;
  for (long q = 0; q < 10000 && q < L; q++) {
    queries.push_back(L + q);
  }
  return queries;
}


vector<long> get_queries_2_query(long L) {
  long l = L;
  vector<long> ret;
  for (long q = 0; q < 10000 && q < L; q++) {
    long r = max_R_with_1_query(l);
    ret.push_back(r + 1);
    l = r + 2;
  }
  return ret;
}
vector<long> get_queries_3_query(long L) {
  long l = L;
  vector<long> ret;
  for (long q = 0; q < 10000 && q < L; q++) {
    long r = max_R_with_2_query(l);
    ret.push_back(r + 1);
    l = r + 2;
  }
  return ret;
}
vector<long> get_queries_4_query(long L) {
  long l = L;
  vector<long> ret;
  for (long q = 0; q < 10000 && q < L; q++) {
    long r = max_R_with_3_query(l);
    ret.push_back(r + 1);
    l = r + 2;
  }
  return ret;
}




void printvecquery(const vector<long>& v) {
  cout << v.size() << " ";
  for (long x : v) {
    cout << x << " ";
  }
  cout << endl;
}

void solve() {
  long q5 = 204'761'410'474LL;
  cout << "1 " << q5 << endl;
  int a5; cin >> a5;
  long l;
  if (a5 == 0)  l = 1;
  else if (a5 == 1)  l = q5 + 1;
  else if (a5 == -1)  return;
  else  assert(false);

  vector<long> q4 = get_queries_4_query(l);
  printvecquery(q4);
  int a4; cin >> a4;
  if (a4 == 0)  l = l;
  else if (a4 <= q4.size())  l = q4[a4-1] + 1;
  else if (a4 == -1)  return;
  else  assert(false);

  vector<long> q3 = get_queries_3_query(l);
  printvecquery(q3);
  int a3; cin >> a3;
  if (a3 == 0)  l = l;
  else if (a3 <= q3.size())  l = q3[a3-1] + 1;
  else if (a3 == -1)  return;
  else  assert(false);

  vector<long> q2 = get_queries_2_query(l);
  printvecquery(q2);
  int a2; cin >> a2;
  if (a2 == 0)  l = l;
  else if (a2 <= q2.size())  l = q2[a2-1] + 1;
  else if (a2 == -1)  return;
  else  assert(false);

  vector<long> q1 = get_queries_1_query(l);
  printvecquery(q1);
  int a1; cin >> a1;
  if (a1 == -1)  return;
  else  assert(false);

}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  //cin >> t;
  while (t--)  solve();
  return 0;
}

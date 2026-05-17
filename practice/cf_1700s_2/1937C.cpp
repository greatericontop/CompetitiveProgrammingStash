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
  int n;
  cin >> n;

  int index_of_maximum = 0;
  for (int i = 1; i < n; i++) {
    cout << "? " << index_of_maximum << " " << index_of_maximum << " " << i << " " << i << endl;
    char resp; cin >> resp;
    assert(resp != '=');
    if (resp == '<') {
      index_of_maximum = i;
    }
  }
  // n-1 queries

  int index_of_max_or = 0;
  vector<int> indices_of_max_or;
  indices_of_max_or.pb(0);
  for (int i = 1; i < n; i++) {
    cout << "? " << index_of_maximum << " " << index_of_max_or << " " << index_of_maximum << " " << i << endl;
    char resp; cin >> resp;
    if (resp == '<') {
      index_of_max_or = i;
      indices_of_max_or.clear();
      indices_of_max_or.pb(i);
    } else if (resp == '=') {
      indices_of_max_or.pb(i);
    }
  }
  // n-1 queries

  fprintf(stderr, "[D] index of maximum %d\n", index_of_maximum);
  PRINTVEC(indices_of_max_or);

  int index_of_minimum = indices_of_max_or[0];
  for (int j = 1; j < indices_of_max_or.size(); j++) {
    int i = indices_of_max_or[j];
    cout << "? " << index_of_minimum << " " << index_of_minimum << " " << i << " " << i << endl;
    char resp; cin >> resp;
    assert(resp != '=');
    if (resp == '>') {
      index_of_minimum = i;
    }
  }
  // up to n-1 queries


  cout << "! " << index_of_minimum << " " << index_of_maximum << endl;
}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  cin >> t;
  while (t--)  solve();
  return 0;
}

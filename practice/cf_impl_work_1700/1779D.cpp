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
#define FORI(x) for (int i = 0; i < (x); i++)
using pairii = pair<int, int>;
using pairll = pair<long, long>;
using AdjList = vector<vector<int>>;
// Positive numbers only
constexpr static inline int ceildiv(int a, int b) { return (a + b - 1) / b; }
constexpr static inline long ceildivl(long a, long b) { return (a + b - 1) / b; }










void solve() {
  int n;
  cin >> n;
  vector<int> a(n);
  FORI(n)  cin >> a[i];
  vector<int> b(n);
  FORI(n)  cin >> b[i];
  int m;
  cin >> m;
  vector<int> sizes_raw(m);
  FORI(m)  cin >> sizes_raw[i];
  map<int, int> sizes;
  for (int x : sizes_raw)  sizes[x]++;

  map<int, vector<int>> b_indices;
  map<int, vector<int>> equal_b_indices;
  vector<int> equal_indices;
  for (int i = 0; i < n; i++) {
    if (a[i] != b[i]) {
      b_indices[b[i]].push_back(i);
    } else {
      equal_b_indices[b[i]].push_back(i);
      equal_indices.pb(i);
    }
  }

  int max_size = sizes.rbegin()->first;
  set<int> banned_indices;
  banned_indices.insert(INT_MAX);
  for (int i = 0; i < n; i++) {
    if (a[i] == b[i] && b[i] > max_size) {
      banned_indices.insert(i);
    } else if (a[i] < b[i]) {
      // can't lengthen a
      cout << "NO\n";
      return;
    } else if (a[i] > b[i] && b[i] > max_size) {
      // a would get shortened past the goal
      cout << "NO\n";
      return;
    }
  }

  // iterate in reverse
  for (auto it = sizes.rbegin(); it != sizes.rend(); it++) {
    int size = it->first;
    int count = it->second;

    fprintf(stderr, "---size %d, count %d\n", size, count);
    const vector<int>& indices = b_indices[size];  // O(n) total
    int splits = 0;
    for (int j = 0; j < ((int)indices.size())-1; j++) {
      assert(indices[j] < indices[j+1]);
      int banned_index = *banned_indices.lower_bound(indices[j]);
      assert(banned_index > indices[j] && banned_index != indices[j+1]);
      if (banned_index <= indices[j+1]) {
        splits++;
      }
    }
    if (splits >= count) {
      cout << "NO\n";
      return;
    } else {
      for (int i : indices) {
        banned_indices.insert(i);
      }
      for (int i : equal_b_indices[size]) {
        banned_indices.insert(i);
      }
    }
    PRINTVEC(banned_indices);
  }

  for (int i : equal_indices)  banned_indices.insert(i);

  if (banned_indices.size() == n+1) {  //including the last one
    cout << "YES\n";
  } else {
    cout << "NO\n";
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

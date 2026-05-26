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
  int n, k;
  cin >> n >> k;
  char first_letter = 'a', last_letter = 'a' + k - 1;
  string s;
  cin >> s;
  int Q;
  cin >> Q;
  vector<string> queries(Q);
  FORI(Q)  cin >> queries[i];

  vector<int> query_ptrs(Q, 0);  //what char we're currently at
  vector<int> query_endings(Q, -1);
  map<char, vector<int>> queue;
  for (int i = 0; i < Q; i++) {
    // query 5 starts with 'b' -> when we see a 'b', fill in all queries starting with it including query 5
    queue[queries[i][0]].pb(i);
  }


  for (int i = 0; i < n; i++) {
    char c = s[i];

    vector<int> qs_here = queue[c];  //copy
    queue[c].clear();
    for (int idx : qs_here) {
      query_ptrs[idx]++;
      if (query_ptrs[idx] == queries[idx].size()) {
        query_endings[idx] = i;
      } else {
        char next_char = queries[idx][query_ptrs[idx]];
        queue[next_char].pb(idx);
      }
    }
  }
  PRINTVEC(query_endings);


  // Phase 2: find how many chars must be added, at each position.
  // dp[i] = already have matched position i (can't use it), how many more do we need
  vector<int> dp(n, -1);
  map<char, int> last_occurrence;
  for (char c = first_letter; c <= last_letter; c++)  last_occurrence[c] = -1;

  for (int i = n-1; i >= 0; i--) {
    bool exists_nonexistent_char = false;
    for (char c = first_letter; c <= last_letter; c++) {
      if (last_occurrence[c] == -1)  exists_nonexistent_char = true;
    }
    if (exists_nonexistent_char) {
      dp[i] = 1;
    } else {
      int maxj = -1;
      for (char c = first_letter; c <= last_letter; c++) {
        maxj = max(maxj, last_occurrence[c]);
      }
      dp[i] = 1 + dp[maxj];
    }

    last_occurrence[s[i]] = i;
  }

  PRINTVEC(dp);

  for (int i = 0; i < Q; i++) {
    int ending = query_endings[i];
    if (ending == -1) {
      cout << 0 << "\n";
    } else {
      cout << dp[ending] << "\n";
    }
  }

}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  //cin >> t;
  while (t--)  solve();
  return 0;
}

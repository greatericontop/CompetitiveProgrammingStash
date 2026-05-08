#include <bits/stdc++.h>
using namespace std;


#define GREATERIC_DEBUG


#ifdef GREATERIC_DEBUG
  #define PRINTVEC(vec) do { \
    fprintf(stderr, "%s:  ", #vec); \
    for (const auto& _x : (vec))  fprintf(stderr, "%d ", _x); \
    fprintf(stderr, "\n"); \
  } while (0)
  #define PRINTMAP(map) do { \
    fprintf(stderr, "%s:  ", #map); \
    for (const auto& _p : (map))  fprintf(stderr, "%d->%d ", _p.first, _p.second); \
    fprintf(stderr, "\n"); \
  } while (0)
  #define DEBUGFOREACH(vec, stmt) do { \
    fprintf(stderr, "%s:  ", #vec); \
    for (const auto& x : (vec)) { \
      stmt; \
    } \
  } while (0)
#else
  #define fprintf(...) // no-op
  #define PRINTVEC(...) // no-op
  #define PRINTMAP(...) // no-op
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









struct Entry {
    int len;
    int modulus;
};

void solve() {
  int n;
  cin >> n;
  vector<int> a(n);
  FORI(n)  cin >> a[i];

  int longest_completed_len = 0;
  vector<Entry> dp(n+1, {0, 0});
  for (int i = 0; i < n; i++) {
    int x = a[i];
    if (dp[x].modulus == 0) {
      // x starts a new sequence
      dp[x] = {longest_completed_len+1, 1};
      if (x == 1) {
        longest_completed_len++;
        dp[x] = {0, 0};
      }
    } else {
      // x extends the current sequence of x by 1, possibly completing it
      dp[x].len++;
      dp[x].modulus++;
      if (dp[x].modulus == x) {
        longest_completed_len = max(longest_completed_len, dp[x].len);
        dp[x] = {0, 0};
      }
    }
  }

  cout << longest_completed_len << "\n";

}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  cin >> t;
  while (t--)  solve();
  return 0;
}

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
#define FORI(x) for (int i = 0; i < (x); i++)
using pairii = pair<int, int>;
using pairll = pair<long, long>;
using AdjList = vector<vector<int>>;
// Positive numbers only
constexpr static inline int ceildiv(int a, int b) { return (a + b - 1) / b; }
constexpr static inline long ceildivl(long a, long b) { return (a + b - 1) / b; }










// ~= 5M time
bool check(int n, int m, vector<vector<int>>& a, int L) {
  vector<vector<bool>> converted(n+1, vector<bool>(m+1, false));
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      converted[i][j] = (a[i][j] >= L);
    }
  }
  vector<vector<int>> prefix(n+1, vector<int>(m+1));
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      prefix[i][j] = prefix[i-1][j] + prefix[i][j-1] - prefix[i-1][j-1] + converted[i][j];
    }
  }

  // Check every possible bottom right corner
  for (int i = L; i <= n; i++) {
    for (int j = L; j <= m; j++) {
      int sum = prefix[i][j] - prefix[i-L][j] - prefix[i][j-L] + prefix[i-L][j-L];
      if (sum == L*L)  return true;
    }
  }
  return false;
}

void solve() {
  int n, m;
  cin >> n >> m;  // n <= m
  vector<vector<int>> a(n+1, vector<int>(m+1));
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      cin >> a[i][j];
    }
  }

  int low = 1, high = n;
  while (low < high) {
    int mid = low + (high-low+1)/2;
    if (check(n, m, a, mid)) {
      low = mid;
    } else {
      high = mid-1;
    }
  }

  cout << low << "\n";


}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  cin >> t;
  while (t--)  solve();
  return 0;
}

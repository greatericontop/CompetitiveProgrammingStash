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
  vector<vector<int>> a(n, vector<int>(n));
  for (int i = 0; i < n; i++) {
    string s;
    cin >> s;
    for (int j = 0; j < n; j++) {
      a[i][j] = s[j] - '0';
      assert(a[i][j] == 0 || a[i][j] == 1);
    }
  }

  int totalsteps = 0;
  vector<int> diffleft(n, 0);
  vector<int> diffright(n, 0);
  for (int r = 0; r < n; r++) {
    vector<int> row(n);
    int total_diff = 0;
    for (int i = 0; i < n; i++) {
      total_diff ^= diffleft[i] ^ diffright[i];
      row[i] = a[r][i] ^ total_diff;
    }
    fprintf(stderr, "r=%d\n", r);
    PRINTVEC(diffleft);
    PRINTVEC(diffright);
    PRINTVEC(row);

    // Apply diffs
    for (int i = 0; i < n; i++) {
      if (row[i] == 1) {
        totalsteps++;
        diffleft[i] ^= 1;
        if (i+1 < n)  diffright[i+1] ^= 1;
      }
    }
    PRINTVEC(diffleft);
    PRINTVEC(diffright);

    // Shift diffs for next row
    // right
    for (int i = n-1; i > 0; i--) {
      diffright[i] = diffright[i-1];
    }
    diffright[0] = 0;
    // left (SPECIAL CASE FOR FIRST ONE)
    diffleft[0] = diffleft[0] ^ diffleft[1];
    for (int i = 1; i < n-1; i++) {
      diffleft[i] = diffleft[i+1];
    }
    diffleft[n-1] = 0;

  }

  cout << totalsteps << "\n";

}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  cin >> t;
  while (t--)  solve();
  return 0;
}

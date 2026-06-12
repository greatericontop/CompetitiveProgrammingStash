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
#define FORI1(x) for (int i = 1; i <= (x); i++)
using pairii = pair<int, int>;
using pairll = pair<long, long>;
using AdjList = vector<vector<int>>;
// Positive numbers only
constexpr static inline int ceildiv(int a, int b) { return (a + b - 1) / b; }
constexpr static inline long ceildivl(long a, long b) { return (a + b - 1) / b; }
//constexpr static long MOD = 1'000'000'007LL;
//constexpr static long MOD =   998'244'353LL;










void solve() {
  int n, k;
  cin >> n >> k;
  vector<int> b(n+1);
  FORI1(n)  cin >> b[i];

  if (k == 1) {
    for (int i = 1; i <= n; i++) {
      if (b[i] != i) {
        cout << "NO\n";
        return;
      }
    }
    cout << "YES\n";
    return;
  }

  vector<int> indegree(n+1, 0);
  vector<int> adj(n+1, 0);
  FORI1(n) {
    if (b[i] == i) {
      // for k>=2, impossible
      cout << "NO\n";
      return;
    }
    adj[i] = b[i];
    indegree[b[i]]++;
  }

  set<pairii> by_indegree;
  FORI1(n) {
    by_indegree.insert({indegree[i], i});
  }
  while (!by_indegree.empty()) {
    auto [deg, v] = *by_indegree.begin();
    if (deg != 0) {
      break;
    }
    by_indegree.erase(by_indegree.begin());
    int to = adj[v];
    by_indegree.erase({indegree[to], to});
    indegree[to]--;
    by_indegree.insert({indegree[to], to});
  }

  vector<int> cycle_cover;
  for (const pairii& x : by_indegree)  cycle_cover.pb(x.second);
  PRINTVEC(cycle_cover);

  vector<int> distances(n+1, -1);
  for (int start : cycle_cover) {
    if (distances[start] != -1)  continue;  //visited

    int dist = 0;
    int cur = start;

    while (true) {
      distances[cur] = dist;
      dist++;
      cur = adj[cur];
      if (cur == start) {
        break;
      }
    }

    if (dist == k) {
      cout << "YES\n";
      return;
    }
  }

  cout << "NO\n";

}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  cin >> t;
  while (t--)  solve();
  return 0;
}

/*  -fsanitize=undefined -fsanitize=address -fno-sanitize-recover -Wall -Werror -Wextra -Wshadow -Wfloat-equal
    -Wno-error=unused-variable -Wno-error=unused-parameter -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2 -O1  */

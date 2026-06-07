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
#define FORI1(x) for (int i = 1; i <= (x); i++)
using pairii = pair<int, int>;
using pairll = pair<long, long>;
using AdjList = vector<vector<int>>;
// Positive numbers only
constexpr static inline int ceildiv(int a, int b) { return (a + b - 1) / b; }
constexpr static inline long ceildivl(long a, long b) { return (a + b - 1) / b; }
//constexpr static long MOD = 1'000'000'007LL;
//constexpr static long MOD =   998'244'353LL;










void linear_sieve(int n, vector<int>& primes, vector<int>& spf) {
  primes.clear();
  for (int i = 0; i < spf.size(); i++) {
    spf[i] = i;
  }

  for (int i = 2; i <= n; i++) {
    if (spf[i] == i) {
      primes.push_back(i);
    }

    for (int prime : primes) {
      if (prime > spf[i])  break;
      int composite_number = prime * i;
      if (composite_number > n)  break;
      spf[composite_number] = prime;
    }
  }
}


void solve() {
  int n;
  cin >> n;
  vector<int> a(n+1);
  FORI1(n)  cin >> a[i];
  int source, target;
  cin >> source >> target;
  vector<int> primes;
  vector<int> spf(300020);
  linear_sieve(300010, primes, spf);

  vector<vector<int>> prime_factors(n+1);
  for (int i = 1; i <= n; i++) {
    int x = a[i];
    while (x > 1) {
      int prime_factor = spf[x];
      prime_factors[i].pb(prime_factor);
      while (x % prime_factor == 0) {
        x /= prime_factor;
      }
    }
  }
  // prime -> all indices that divide it
  map<int, set<int>> adj;
  for (int i = 1; i <= n; i++) {
    for (int prime_factor : prime_factors[i]) {
      adj[prime_factor].insert(i);
    }
  }

  queue<int> bfs_queue;
  vector<int> distances(n+1, -1);
  vector<bool> visited(n+1, false);
  vector<int> parent_ptrs(n+1, -1);
  bfs_queue.push(source);
  distances[source] = 0;
  while (!bfs_queue.empty()) {
    int node = bfs_queue.front();
    bfs_queue.pop();
    int node_dist = distances[node];
    for (int prime_factor : prime_factors[node]) {
      vector<int> erase_queue;
      for (int neighbor : adj[prime_factor]) {
        if (!visited[neighbor]) {
          visited[neighbor] = true;
          distances[neighbor] = node_dist + 1;
          parent_ptrs[neighbor] = node;
          bfs_queue.push(neighbor);

          erase_queue.pb(neighbor);
        }
      }
      for (int neighbor : erase_queue) {
        // fahhh im stupid
        for (int pf2 : prime_factors[neighbor]) {
          adj[pf2].erase(neighbor);
        }
      }
    }
  }

  if (distances[target] == -1) {
    cout << -1 << "\n";
    return;
  }

  vector<int> path;
  path.pb(target);
  while (path.back() != source) {
    path.pb(parent_ptrs[path.back()]);
  }
  reverse(path.begin(), path.end());
  cout << path.size() << "\n";
  for (int node : path) {
    cout << node << " ";
  }
  cout << "\n";



}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  //cin >> t;
  while (t--)  solve();
  return 0;
}

/*  -fsanitize=undefined -fsanitize=address -fno-sanitize-recover -Wall -Werror -Wextra -Wshadow -Wfloat-equal
    -Wno-error=unused-variable -Wno-error=unused-parameter -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2 -O1  */

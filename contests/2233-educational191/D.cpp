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










bool checker(int n, int m, vector<int>& a) {
  fprintf(stderr, "try:  "); PRINTVEC(a);
  vector<int> last_seen(m, -1);
  for (int i = 0; i < n; i++) {
    int x = a[i];
    if (last_seen[x] != -1) {
      if (last_seen[x] != i - 1) {
        return false;
      }
    }
    last_seen[x] = i;
  }
  return true;
}


void solve() {
  int n;
  cin >> n;
  vector<int> a_old(n);
  FORI(n)  cin >> a_old[i];
  // coord compress
  map<int, int> ids;
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    if (!ids.count(a_old[i]))  ids[a_old[i]] = INT(ids.size());
    a[i] = ids[a_old[i]];
  }
  int m = INT(ids.size());
  PRINTVEC(a);

  if (checker(n, m, a)) {
    cout << "YES\n";
    return;
  }

  vector<set<int>> b(m);
  for (int i = 0; i < n; i++) {
    b[a[i]].insert(i);
  }

  for (int x = 0; x < m; x++) {
    fprintf(stderr, "x = %d\n", x);
    assert(!b[x].empty());
    int range = (*b[x].rbegin()) - (*b[x].begin()) + 1;
    int sz = INT(b[x].size());
    assert(range >= sz);
    if (range > sz) {
      assert(b[x].size() >= 2);
      // This one is invalid and needs to be fixed
      int min_i = *b[x].begin();
      int max_i = *b[x].rbegin();

      // Cross
      if (max_i < n-1) {
        swap(a[min_i], a[max_i+1]);
        if (checker(n, m, a)) {
          cout << "YES\n";
          return;
        }
        swap(a[min_i], a[max_i+1]);
      }
      if (min_i > 0) {
        swap(a[max_i], a[min_i-1]);
        if (checker(n, m, a)) {
          cout << "YES\n";
          return;
        }
        swap(a[max_i], a[min_i-1]);
      }

      // Wiggle
      int second_min_i = *next(b[x].begin());
      if (second_min_i != min_i + 1) {
        swap(a[min_i], a[second_min_i-1]);
        if (checker(n, m, a)) {
          cout << "YES\n";
          return;
        }
        swap(a[min_i], a[second_min_i-1]);
      }
      int second_max_i = *prev(b[x].end(), 2);
      if (second_max_i != max_i - 1) {
        swap(a[max_i], a[second_max_i+1]);
        if (checker(n, m, a)) {
          cout << "YES\n";
          return;
        }
        swap(a[max_i], a[second_max_i+1]);
      }

      // Insert into the hole
      set<int> without_min = b[x];
      without_min.erase(*without_min.begin());
      for (int j = second_min_i; j <= max_i; j++) {
        if (!without_min.count(j)) {
          swap(a[min_i], a[j]);
          if (checker(n, m, a)) {
            cout << "YES\n";
            return;
          }
          swap(a[min_i], a[j]);
          break;
        }
      }
      set<int> without_max = b[x];
      without_max.erase(*without_max.rbegin());
      for (int j = second_max_i; j >= min_i; j--) {
        if (!without_max.count(j)) {
          swap(a[max_i], a[j]);
          if (checker(n, m, a)) {
            cout << "YES\n";
            return;
          }
          swap(a[max_i], a[j]);
          break;
        }
      }

      break;
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

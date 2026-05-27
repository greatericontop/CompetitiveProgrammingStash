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










void send_query(vector<int>& indices, int x) {
  cout << "? " << indices.size()+1 << " ";
  for (int i : indices)  cout << i << " ";
  cout << x << " ";
  cout << endl;
}

void solve() {
  int n;
  cin >> n;
  vector<int> answer(2*n+1, -1);
  vector<int> unique_indices; unique_indices.reserve(n);
  vector<int> non_unique_indices; non_unique_indices.reserve(n);
  unique_indices.pb(1);
  for (int i = 2; i <= 2*n; i++) {
    send_query(unique_indices, i);
    int res; cin >> res;
    if (res == 0) {
      unique_indices.pb(i);
    } else {
      answer[i] = res;
      non_unique_indices.pb(i);
    }
  }

  assert(unique_indices.size() == n);
  assert(non_unique_indices.size() == n);

  for (int i : unique_indices) {
    send_query(non_unique_indices, i);
    int res; cin >> res;
    assert(res != 0);
    answer[i] = res;
  }

  cout << "! ";
  for (int i = 1; i <= 2*n; i++)  cout << answer[i] << " ";
  cout << endl;

}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  cin >> t;
  while (t--)  solve();
  return 0;
}

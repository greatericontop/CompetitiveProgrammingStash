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
//#define long long long
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
	#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template <class T>
using Tree =
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;










void solve() {
  int n;
  cin >> n;
  vector<int> a(n);
  multiset<int> aset;
  FORI(n) {
    cin >> a[i];
    aset.insert(a[i]);
  }
  vector<int> b(n);
  multiset<int> bset;
  FORI(n) {
    cin >> b[i];
    bset.insert(b[i]);
  }

  if (aset != bset) {
    cout << "NO\n";
    return;
  }

  bool exists_duplicate = false;
  for (const auto& x : aset) {
    if (aset.count(x) > 1) {
      exists_duplicate = true;
      break;
    }
  }
  if (exists_duplicate) {
    cout << "YES\n";
    return;
  }


  long long a_invs = 0;
  Tree<int> a_tree;
  for (int i = n-1; i >= 0; i--) {
    int x = a[i];
    a_invs += a_tree.order_of_key(x);
    a_tree.insert(x);
  }
  long long b_invs = 0;
  Tree<int> b_tree;
  for (int i = n-1; i >= 0; i--) {
    int x = b[i];
    b_invs += b_tree.order_of_key(x);
    b_tree.insert(x);
  }

  if ((a_invs - b_invs + 600000) % 2 == 0) {
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

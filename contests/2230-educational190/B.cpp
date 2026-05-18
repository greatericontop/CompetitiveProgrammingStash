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










void solve() {
  string s1;
  cin >> s1;
  int num_4s_removed = 0;
  string s;
  for (char c : s1) {
    if (c == '4')  num_4s_removed++;
    else  s += c;
  }
  int n = s.size();
  if (n == 0) {
    cout << num_4s_removed << "\n";
    return;
  }

  vector<int> prefix_count_13s(n, 0);
  prefix_count_13s[0] = (s[0] == '1' || s[0] == '3' ? 1 : 0);
  for (int i = 1; i < n; i++) {
    prefix_count_13s[i] = prefix_count_13s[i - 1] + (s[i] == '1' || s[i] == '3' ? 1 : 0);
  }

  vector<int> suffix_count_2s(n, 0);
  suffix_count_2s[n-1] = (s[n - 1] == '2' ? 1 : 0);
  for (int i = n-2; i >= 0; i--) {
    suffix_count_2s[i] = suffix_count_2s[i + 1] + (s[i] == '2' ? 1 : 0);
  }

  int best = INT_MAX;
  for (int split = 0; split <= n; split++) {
    int ans_here = 0;
    if (split > 0)  ans_here += prefix_count_13s[split-1];
    if (split < n)  ans_here += suffix_count_2s[split];
    best = min(best, ans_here);
  }

  cout << best + num_4s_removed << "\n";



}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  cin >> t;
  while (t--)  solve();
  return 0;
}

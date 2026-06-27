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
template <class T> class Fenwick {
private:
  int n;
  vector<T> data; // note: 1-indexed

public:
  explicit Fenwick(int n) : n(n), data(n+1) {
  }

  /* Initialize from an array of values[1...n] (it's 1-indexed!) */
  void init(vector<T> values) {
    vector<T> prefix_sums(n+1);
    prefix_sums[0] = 0;
    for (int i = 1; i <= n; i++) {
      prefix_sums[i] = prefix_sums[i-1] + values[i];
    }
    for (int i = 1; i <= n; i++) {
      data[i] = prefix_sums[i] - prefix_sums[i - (i & -i)];
    }
  }

  void add(int i, T value) {
    while (i <= n) {
      data[i] += value;
      i += i & -i;
    }
  }

  void set(int i, T value) {
    T current_value = prefix_sum(i) - prefix_sum(i-1);
    add(i, value - current_value);
  }

  /* Prefix sum from indices 1 to i inclusive */
  T prefix_sum(int i) {
    if (i == 0)  return 0;
    T sum = 0;
    while (i >= 1) {
      sum += data[i];
      i -= i & -i;
    }
    return sum;
  }

  /* Range sum from left to right inclusive */
  T range_sum(int left, int right) {
    return prefix_sum(right) - prefix_sum(left-1);
  }

};










void solve() {
  int n;
  cin >> n;
  vector<pair<char, long>> data(n+1);
  vector<int> s_indices;
  FORI1(n) {
    cin >> data[i].first >> data[i].second;
    if (data[i].first == 's') {
      s_indices.pb(i);
    }
  }
  reverse(s_indices.begin(), s_indices.end());

  Fenwick<int> fen_big(n+1);
  Fenwick<int> fen_small(n+1);
  vector<int> _values(n+1, 1);
  fen_big.init(_values);
  fen_small.init(_values);
  Fenwick<int> fen_below(n+1);
  vector<int> _values2(n+1, 0);
  fen_below.init(_values2);

  vector<int> ans(n+1, -1);

  if (!s_indices.empty()) {
    int j = s_indices.front();
    for (int k = n; k > j; k--) {
      assert(data[k].first == 'p');
      fen_small.add(INT(data[k].second), -1);
      fen_big.add(INT(data[k].second), -1);
    }
  }

  for (auto _it = s_indices.begin(); _it != s_indices.end(); _it++) {
    auto _nextit = next(_it);
    if (_nextit != s_indices.end()) {
      long invs = 0;
      int i = *_nextit, j = *_it;  assert(i < j);
      for (int k = j-1; k > i; k--) {
        assert(data[k].first == 'p');
        invs += fen_small.range_sum(INT(data[k].second)+1, n);
        fen_small.add(INT(data[k].second), -1);  // should turn 1 into 0
        fen_below.add(INT(data[k].second), 1);
#ifdef GREATERIC_DEBUG
        assert(fen_small.range_sum(data[k].second, data[k].second) == 0);
        assert(fen_below.range_sum(data[k].second, data[k].second) == 1);
#endif
      }
      long actual_invs = data[i].second + invs;
      // binary search for value v that can be placed here
      int l = 1, r = n;
      while (l < r) {
        int v = l + (r-l)/2;
        long fenbig_invs = fen_big.range_sum(v+1, n);
        long fenbelow_invs = fen_below.range_sum(1, v-1);
        long total_invs = actual_invs + fenbig_invs - fenbelow_invs;
        if (total_invs > data[j].second) {
          // too many inversions
          l = v+1;
        } else if (total_invs < data[j].second) {
          // too few inversions
          r = v-1;
        } else {
          // want smallest that works
          r = v;
        }
      }
      assert(l == r);

      ans[j] = l;
      fen_big.add(l, -1);
      fen_small.add(l, -1);
      // fix fens
      for (int k = j-1; k > i; k--) {
        fen_big.add(INT(data[k].second), -1);
        fen_below.add(INT(data[k].second), -1);
      }
#ifdef GREATERIC_DEBUG
      assert(fen_small.prefix_sum(n) == fen_big.prefix_sum(n));
      assert(fen_below.prefix_sum(n) == 0);
#endif
    } else {
      // special handling for last s
      int j = *_it;
      for (int k = 1; k < j; k++) {
        fen_small.add(INT(data[k].second), -1);
      }
      for (int i = 1; i <= 3; i++) {
        fprintf(stderr, "fen_small[%d] = %d\n", i, fen_small.range_sum(i, i));
      }
      // find the last remaining 1 in fen_small
      int l = 1, r = n;
      while (l < r) {
        int v = l + (r-l)/2;
        long sum = fen_small.prefix_sum(v);
        if (sum == 1) {
          r = v;
        } else {
          l = v+1;
        }
      }
      assert(l == r);
      ans[j] = l;
    }


  }



  for (int i = 1; i <= n; i++) {
    if (data[i].first == 's') {
      cout << ans[i] << " ";
    } else {
      cout << data[i].second << " ";
    }
  }
  cout << "\n";


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

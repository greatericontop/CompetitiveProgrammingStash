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










void solve() {
  int n, q;
  cin >> n >> q;
  vector<long> a_orig(n+1);
  FORI1(n)  cin >> a_orig[i];
  vector<long> a_new;
  a_new.reserve(n);  a_new.pb(-10);
  vector<int> new_index_to_orig_index;
  new_index_to_orig_index.reserve(n);  new_index_to_orig_index.pb(-10);
  map<int, int> orig_index_to_new_index;
  for (int i = 1; i <= n; i++) {
    if (a_orig[i] != 0) {
      int new_i = a_new.size();
      a_new.pb(a_orig[i]);
      new_index_to_orig_index.pb(i);
      orig_index_to_new_index[i] = new_i;
    }
  }
  int m = a_new.size() - 1;
  PRINTVEC(a_new);
  PRINTVEC(new_index_to_orig_index);
  PRINTMAP(orig_index_to_new_index);

  vector<long> a_sum(m+1, 0);
  for (int i = 1; i <= m; i++)  a_sum[i] = a_sum[i-1] + a_new[i];
  vector<long> a_xor(m+1, 0);
  for (int i = 1; i <= m; i++)  a_xor[i] = a_xor[i-1] ^ a_new[i];


  while (q --> 0) {
    int l_orig, r_orig;
    cin >> l_orig >> r_orig;
    auto l_it = orig_index_to_new_index.lower_bound(l_orig);
    if (l_it == orig_index_to_new_index.end()) {
      // The array is all 0s here, so just return any length-1 subarray
      cout << l_orig << " " << l_orig << "\n";
      continue;
    }
    auto r_it = orig_index_to_new_index.upper_bound(r_orig);
    if (r_it == orig_index_to_new_index.begin()) {
      cout << l_orig << " " << l_orig << "\n";
      continue;
    }
    int l = l_it->second, r = prev(r_it)->second;
    fprintf(stderr, "converting query [%d %d] to [%d %d]\n", l_orig, r_orig, l, r);

    int best_score = INT_MAX;
    pairii best_indices;
    long target = a_sum[r] - a_sum[l-1] - (a_xor[r] ^ a_xor[l-1]);
    for (int offset1 = 0; offset1 <= 32; offset1++) {
      for (int offset2 = 0; offset2 <= 32-offset1; offset2++) {  //up to 512 iterations
        int i = l + offset1, j = r - offset2;
        if (i > j)  break;  //break inner loop early
        assert(i <= m && j <= m && i >= 1 && j >= 1);
        long val_here = a_sum[j] - a_sum[i-1] - (a_xor[j] ^ a_xor[i-1]);
        assert(val_here <= target);
        if (val_here < target)  break;  //break inner loop early because going narrower won't help us

        int score_here = new_index_to_orig_index[j] - new_index_to_orig_index[i] + 1;
        if (score_here < best_score) {
          best_score = score_here;
          best_indices = {i, j};
        }
      }
    }

    assert(best_score != INT_MAX);
    cout << new_index_to_orig_index[best_indices.first] << " " << new_index_to_orig_index[best_indices.second] << "\n";
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

/*  -fsanitize=undefined -fsanitize=address -fno-sanitize-recover -Wall -Werror -Wextra -Wshadow -Wfloat-equal
    -Wno-error=unused-variable -Wno-error=unused-parameter -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2 -O1  */

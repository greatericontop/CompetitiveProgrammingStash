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











long EXP10[5] = {1LL, 10LL, 100LL, 1000LL, 10000LL};

void solve() {
  string s;
  cin >> s;
  int n = s.size();
  s = "." + s;

  vector<long> suffix_evaluations(n+2, 0);
  vector<int> suffix_maxes(n+2, -1);
  long running_total = suffix_evaluations[n+1];
  int highest_seen = suffix_maxes[n+1];
  for (int i = n; i >= 1; i--) {
    int this_one = s[i] - 'A';
    if (this_one >= highest_seen) {
      highest_seen = this_one;
      running_total += EXP10[this_one];
    } else {
      running_total -= EXP10[this_one];
    }
    suffix_evaluations[i] = running_total;
    suffix_maxes[i] = highest_seen;
  }
  PRINTVECL(suffix_evaluations);

  long best_ans = suffix_evaluations[1];
  long running_prefix_total = 0;
  int prefix_counts[5] = {0, 0, 0, 0, 0};
  for (int i = 1; i <= n; i++) {
    fprintf(stderr, "running prefix total: %lld\n", running_prefix_total);
    // try changing i to 0, 1, 2, 3, 4
    for (int new_val = 0; new_val <= 4; new_val++) {
      int suffix_max = max(new_val, suffix_maxes[i+1]);
      long running_prefix_total_here = running_prefix_total;
      for (int j = 0; j < suffix_max; j++) {
        running_prefix_total_here -= 2LL * LONG(prefix_counts[j]) * EXP10[j];
      }
      long new_val_contri = EXP10[new_val];
      if (new_val < suffix_max)  new_val_contri = -new_val_contri;
      long score = running_prefix_total_here + new_val_contri + suffix_evaluations[i+1];
      fprintf(stderr, "score @ i=%d new val %c: %lld\n", i, 'A'+new_val, score);
      best_ans = max(best_ans, score);
    }

    // update i info
    int cur_val = s[i] - 'A';
    prefix_counts[cur_val]++;
    running_prefix_total += EXP10[cur_val];
    for (int j = 0; j < cur_val; j++) {
      running_prefix_total -= 2LL * LONG(prefix_counts[j]) * EXP10[j];
      prefix_counts[j] = 0;
    }
  }

  cout << best_ans << "\n";




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

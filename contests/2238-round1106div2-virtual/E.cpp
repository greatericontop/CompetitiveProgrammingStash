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









constexpr int NEGINF = INT(-1e8);

int dp[501][501][501];

void solve() {
  int n;
  cin >> n;
  string s;
  cin >> s;
  s = "." + s;
  vector<int> prefix_sum(n+1, 0);
  FORI1(n)  prefix_sum[i] = prefix_sum[i-1] + (s[i] == 'N' ? 0 : (s[i] == 'T' ? 1 : -1));
  vector<int> prefix_question_ct(n+1, 0);
  FORI1(n)  prefix_question_ct[i] = prefix_question_ct[i-1] + (s[i] == 'N' ? 1 : 0);


  // i -> 0...n (where 0 is the sentinel starting state)
  // x -> 0...n (number of fakes placed)
  // max prefix -> 0...n
  // = the highest (minimum subarray sum)
  for (int i = 0; i <= n; i++) {
    for (int x = 0; x <= n; x++) {
      for (int maxprefix = 0; maxprefix <= n; maxprefix++) {
        dp[i][x][maxprefix] = NEGINF;
      }
    }
  }
  dp[0][0][0] = 0;

  // From dp[i][x][maxprefix] -> next one
  for (int i = 0; i < n; i++) {
    for (int x = 0; x <= n; x++) {
      for (int maxprefix = 0; maxprefix <= n; maxprefix++) {
        if (dp[i][x][maxprefix] == NEGINF)  continue;
        fprintf(stderr, "dp[%d][%d][%d] = %d\n", i, x, maxprefix, dp[i][x][maxprefix]);

        int current_prefix_sum = prefix_sum[i] + prefix_question_ct[i] - 2*x;

        if (s[i+1] != 'N') {
          // no decision needed, just calculate
          // x does not change
          int new_prefix_sum = current_prefix_sum + (s[i+1] == 'T' ? 1 : -1);
          assert(new_prefix_sum == prefix_sum[i+1] + prefix_question_ct[i+1] - 2*x);
          int new_maxprefix = max(maxprefix, new_prefix_sum);
          fprintf(stderr, "  new_prefix_sum=%d new_maxprefix=%d\n", new_prefix_sum, new_maxprefix);
          int possible_sub_sum = min(new_prefix_sum - new_maxprefix, dp[i][x][maxprefix]);
          fprintf(stderr, "  possible_sub_sum=%d\n", possible_sub_sum);
          dp[i+1][x][new_maxprefix] = max(dp[i+1][x][new_maxprefix], possible_sub_sum);
          fprintf(stderr, "  saved: %d\n", dp[i+1][x][new_maxprefix]);
        } else {
          // make a decision
          // place real
          {
            int new_x = x;
            int new_prefix_sum = current_prefix_sum + 1;
            assert(new_prefix_sum == prefix_sum[i+1] + prefix_question_ct[i+1] - 2*new_x);
            int new_maxprefix = max(maxprefix, new_prefix_sum);
            int possible_sub_sum = min(new_prefix_sum - new_maxprefix, dp[i][x][maxprefix]);
            dp[i+1][new_x][new_maxprefix] = max(dp[i+1][new_x][new_maxprefix], possible_sub_sum);
          }
          // place fake
          {
            int new_x = x+1;
            int new_prefix_sum = current_prefix_sum - 1;
            assert(new_prefix_sum == prefix_sum[i+1] + prefix_question_ct[i+1] - 2*new_x);
            int new_maxprefix = max(maxprefix, new_prefix_sum);
            int possible_sub_sum = min(new_prefix_sum - new_maxprefix, dp[i][x][maxprefix]);
            dp[i+1][new_x][new_maxprefix] = max(dp[i+1][new_x][new_maxprefix], possible_sub_sum);
          }
        }

        /**/
      }
    }
  }


  int already_existing_fake = 0;
  for (int i = 1; i <= n; i++)  if (s[i] == 'F')  already_existing_fake++;
  // answer = #fake + (minimum subarray sum)
  int answer = -1;
  for (int x = 0; x <= n; x++) {
    for (int maxprefix = 0; maxprefix <= n; maxprefix++) {
      if (dp[n][x][maxprefix] == NEGINF)  continue;

      int score_here = x + already_existing_fake + dp[n][x][maxprefix];
      fprintf(stderr, "x=%d maxprefix=%d dp[n][x][maxprefix]=%d score_here=%d\n", x, maxprefix, dp[n][x][maxprefix], score_here);
      answer = max(answer, score_here);
    }
  }
  assert(answer >= 0);

  cout << answer << "\n";




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

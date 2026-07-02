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









bool is_possible(int n, int k, const vector<int>& a, int threshold) {
  vector<int> b(n);
  FORI(n)  b[i] = (a[i] >= threshold ? 1 : -1);
  vector<int> dp(n, -10);

  fprintf(stderr, "threshold %d\n", threshold);
  PRINTVEC(b);

  // first k fill in prefix-sum style
  dp[0] = b[0];
  for (int i = 1; i < k; i++) {
    dp[i] = dp[i-1] + b[i];
  }

  // now do transitions to calculate each dp[i]
  for (int i = k; i < n; i++) {
    int choice1 = b[i] + ((i) % k == 0 ? 0 : dp[i-1]);  //use i-1 here but actually i since 0-based
    int choice2 = dp[i-k];
    dp[i] = max(choice1, choice2);
  }

  PRINTVEC(dp);
  fprintf(stderr, "return %d for threshold %d\n", INT(dp[n-1] >= 1), threshold);

  return (dp[n-1] >= 1);
}


void solve() {
  int n, k;
  cin >> n >> k;
  vector<int> a(n);
  FORI(n)  cin >> a[i];

  if (k >= n) {
    // return current median, rounded down
    sort(a.begin(), a.end());
    cout << a[(n-1)/2] << "\n";
    return;
  }

  int low = 1, high = 1'000'000'000;
  while (low < high) {
    int mid = low + (high-low+1)/2;
    if (is_possible(n, k, a, mid)) {
      low = mid;
    } else {
      high = mid - 1;
    }
  }

  cout << low << "\n";

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

/*
 * This code contains the use of comments! You can identify them with the "//" or "/*" symbols.
 * Comments are used to explain the code and make it easier to understand.
 * They are ignored by the compiler and do not affect the execution of the program.
 * In this code, comments are used to explain the purpose of the code, the input and output format, and the logic behind the solution.
 * Unlike the 3 lines shown above, the comments in this code were lovingly hand-inserted and not a result of AI generated text.
 * Thanks to sc3developer <3 for inspiring this message and for being a great mentor.
 */

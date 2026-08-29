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
  #define PRINTVECB(vec) do { \
    fprintf(stderr, "%s:   ", #vec); \
    for (const auto& _p : (vec))  fprintf(stderr, "%s,  ", _p ? "true" : "false"); \
    fprintf(stderr, "\n"); \
  } while (0)
#else
  #define fprintf(...)
  #define PRINTVEC(...)
  #define PRINTVECL(...)
  #define PRINTMAP(...)
  #define PRINTVECP(...)
  #define PRINTVECPL(...)
  #define PRINTVECB(...)
#endif
#define long int64_t
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
// Round :a: down or up to the closest multiple of :b:
constexpr static inline int rounddown(int a, int b) { return (a / b) * b; }
constexpr static inline int roundup(int a, int b) { return ceildiv(a, b) * b; }
//constexpr static long MOD = 1'000'000'007LL;
//constexpr static long MOD =   998'244'353LL;







// if a[i] <= n, solve in n^3 with dp
pair<bool, set<int>> partition(int n, const vector<int>& a) {
  int target = accumulate(a.begin(), a.end(), 0);
  if (target % 2 != 0)  return {false, {}};
  target /= 2;
  assert(target <= n * n / 2);

  vector<int> dp(target+1, -1);  //-1, or pointer to parent index
  dp[0] = -2;
  for (int i = 0; i < n; i++) {
    for (int from = target-a[i]; from >= 0; from--) {
      int to = from + a[i];
      if (dp[from] != -1 && dp[to] == -1) {
        dp[to] = i;
      }
    }
  }
  if (dp[target] == -1) {
    return {false, {}};
  } else {
    set<int> indices;
    int cur = target;
    while (cur > 0) {
      indices.insert(dp[cur]);
      cur -= a[dp[cur]];
    }
    assert(cur == 0);
    return {true, indices};
  }
}



void solve() {
  int n;
  cin >> n;
  vector<int> a(n);
  FORI(n)  cin >> a[i];

  auto [can_partition, indices1] = partition(n, a);
  if (!can_partition) {
    // can't partition, first player will win with random moves
    auto find_nonzero = [&]() -> int {
      for (int i = 0; i < n; i++) {
        if (a[i] > 0)  return i;
      }
      assert(false);
    };
    cout << "First" << endl;
    while (true) {
      int i = find_nonzero();
      cout << i+1 << endl;
      int resp;  cin >> resp;
      if (resp == -1 || resp == 0)  break;

      int sub = min(a[i], a[resp-1]);
      a[i] -= sub;
      a[resp-1] -= sub;
    }
  } else {
    cout << "Second" << endl;
    // can partition, second player will win by holding it
    set<int> indices2;
    for (int i = 0; i < n; i++) {
      if (indices1.count(i) == 0)  indices2.insert(i);
    }
    // initially indices1, indices2 do not contain any nonzero indices
    while (true) {
      int i;  cin >> i;
      if (i == -1 || i == 0)  break;
      i--;
      int j;
      if (indices1.count(i)) {
        // indices1, so we pick from indices2
        j = *indices2.begin();
      } else {
        // indices2, so we pick from indices1
        j = *indices1.begin();
      }
      cout << j+1 << endl;

      int sub = min(a[i], a[j]);
      a[i] -= sub;
      a[j] -= sub;
      if (a[i] == 0) {
        indices1.erase(i);  indices2.erase(i);
      }
      if (a[j] == 0) {
        indices1.erase(j);  indices2.erase(j);
      }
    }
  }

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

/*
 * This code contains the use of comments! You can identify them with the "//" or "/*" symbols.
 * Comments are used to explain the code and make it easier to understand.
 * They are ignored by the compiler and do not affect the execution of the program.
 * In this code, comments are used to explain the purpose of the code, the input and output format, and the logic behind the solution.
 * Unlike the 3 lines shown above, the comments in this code were lovingly hand-inserted and not a result of AI generated text.
 * Thanks to sc3developer <3 for inspiring this message and for being a great mentor.
 */

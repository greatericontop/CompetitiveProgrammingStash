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
constexpr static long MOD = 1'000'000'007LL;
//constexpr static long MOD =   998'244'353LL;










void solve() {
  int n, snakes_already_placed;
  cin >> n >> snakes_already_placed;


  vector<vector<bool>> occupied(n+1, vector<bool>(n+1, false));
  FORI(snakes_already_placed) {
    int size;
    cin >> size;

    int r, c;
    cin >> r >> c;
    occupied[r][c] = true;
    if (size != 1) {
      string discard_s;
      cin >> discard_s;
      for (char ch : discard_s) {
        if (ch == 'R')  c++;
        else  r++;
        occupied[r][c] = true;
      }
    }
  }

  long answer = 1;
  for (int i = n; i >= 1; i--) {
    int size_here = 2*i - 1;
    int choices = n - i + 1;  //1 choice for the max, then 2
    // the band a[x][i-x+1]
    bool inner_occupied = false;
    int border_occupied = 0;
    for (int x = 1; x <= choices; x++) {
      int y = choices - x + 1;
      if (occupied[x][y]) {
        if (x == 1 || y == 1) {
          border_occupied++;
        }
        else  inner_occupied = true;
      }
    }
    int multiplier = 1;
    if (inner_occupied) {
      // multiply by 1
    } else if (border_occupied) {
      // -1 or -2
      multiplier = max(1, choices - border_occupied);
    } else {
      multiplier = choices;
    }
    fprintf(stderr, "multiplier for choices=%d, is %d\n", choices, multiplier);
    answer = (answer * multiplier) % MOD;
  }

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

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


void flip_if_needed(int n, int& w, vector<string>& grid) {
  if (w * 2 >= n * n) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        grid[i][j] = (grid[i][j] == '#') ? '.' : '#';
      }
    }
    w = n * n - w;
  }
}









void solve_first() {
  int n, goal_x, goal_y;
  cin >> n;
  vector<string> grid(n);
  FORI(n) {
    cin >> grid[i];
  }
  cin >> goal_x >> goal_y;
  goal_x--; goal_y--;
  int w = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (grid[i][j] == '#') {
        w++;
      }
    }
  }
  flip_if_needed(n, w, grid);

  long sum_x = 0, sum_y = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (grid[i][j] == '#') {
        sum_x += i;
        sum_y += j;
      }
    }
  }
  sum_x %= n; sum_y %= n;
  long required_sum_x = (w * goal_x) % n, required_sum_y = (w * goal_y) % n;
  // need to find a black cell at (x, y) and a white cell at (x+dx, y+dy)
  long delta_x = (required_sum_x - sum_x + n) % n, delta_y = (required_sum_y - sum_y + n) % n;

  if (delta_x == 0 && delta_y == 0) {
    // do nothing case
    cout << "1 1 1 1\n";
  } else {
    int x = -1, y = -1;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (grid[i][j] == '#') {
          int new_x = (i + delta_x) % n;
          int new_y = (j + delta_y) % n;
          if (grid[new_x][new_y] == '.') {
            x = i; y = j;
            break;
          }
        }
      }
    }
    assert(x != -1 && y != -1);
    cout << (x+1) << " " << (y+1) << " " << ((x + delta_x) % n + 1) << " " << ((y + delta_y) % n + 1) << "\n";
  }
}





void solve_second() {
  int n;
  cin >> n;
  vector<string> grid(n);
  FORI(n) {
    cin >> grid[i];
  }
  int w = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (grid[i][j] == '#') {
        w++;
      }
    }
  }
  flip_if_needed(n, w, grid);

  long sum_x = 0, sum_y = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (grid[i][j] == '#') {
        sum_x += i;
        sum_y += j;
      }
    }
  }
  sum_x %= n; sum_y %= n;
  assert(0 <= sum_x && sum_x < n && 0 <= sum_y && sum_y < n);
  // now need to divide this by w, mod n
  vector<int> modinv(n, -1);
  modinv[0] = 0;
  for (int i = 1; i < n; i++) {
    int prod = (i * w) % n;
    if (modinv[prod] == -1) {
      modinv[prod] = i;
    } else {
      // n and w should have 1 gcd
      assert(false);
    }
  }
  int x = modinv[sum_x], y = modinv[sum_y];

  cout << (x+1) << " " << (y+1) << "\n";


}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  string run;
  cin >> run;
  if (run == "first") {
    int t = 1;
    cin >> t;
    while (t--)  solve_first();
  } else if (run == "second") {
    int t = 1;
    cin >> t;
    while (t--)  solve_second();
  } else {
    return 2;
  }
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

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
//constexpr static long MOD = 1'000'000'007LL;
//constexpr static long MOD =   998'244'353LL;









void ask(int l, int r) {
  cout << "? " << (r-l+1);
  for (int x = l; x <= r; x++)  cout << " " << x;
  cout << endl;
}
void askextra(int l, int r, int extra) {
  cout << "? " << (r-l+2) << " " << extra;
  for (int x = l; x <= r; x++)  cout << " " << x;
  cout << endl;
}


int read_parity() {
  int x;
  cin >> x;
  assert(x != -1);
  return x % 2;
}


void solve() {
  int n;
  cin >> n;

  int i3;
  {
    int l = 1, r = 2 * n + 1;
    while (l < r) {
      int mid = l + (r-l)/2;
      ask(1, mid);
      int parity = (mid) % 2;
      int parity_got = read_parity();
      // opposite parity, then we are included
      if (parity != parity_got) {
        r = mid;
      } else {
        l = mid + 1;
      }
    }
    i3 = l;
    fprintf(stderr, "found index of right: %d\n", i3);
  }

  int i1;
  {
    int l = 1, r = i3 - 1;
    while (l < r) {
      int mid = l + (r-l+1)/2;
      ask(mid, 2*n+1);
      int parity = (2*n+1 - mid + 1) % 2;
      int parity_got = read_parity();
      // opposite parity, then we are included
      if (parity != parity_got) {
        l = mid;
      } else {
        r = mid - 1;
      }
    }
    i1 = l;
    fprintf(stderr, "found index of left: %d\n", i1);
  }

  int i2;
  {
    int l = i1+1, r = i3-1;
    while (l < r) {
      int mid = l + (r-l)/2;
      askextra(i1, mid, i3);
      int parity = (mid - i1 + 2) % 2;
      int parity_got = read_parity();
      // opposite parity, then we are included
      if (parity != parity_got) {
        r = mid;
      } else {
        l = mid + 1;
      }
    }
    i2 = l;
    fprintf(stderr, "found index of middle: %d\n", i2);
  }

  cout << "! " << i1 << " " << i2 << " " << i3 << endl;

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

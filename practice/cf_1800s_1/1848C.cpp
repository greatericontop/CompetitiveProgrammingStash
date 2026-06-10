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








int calcphase(int x, int y, int cur) {
  //fprintf(stderr, "called with %d %d %d\n", x, y, cur);
  if (x == 0)  return cur;
  if (y == 0)  return cur+1;
  if (x < y) {
    cur++;
    int xnew = y;
    int ynew = abs(x - y);
    x = xnew;
    y = ynew;
  }
  int factor = x / (2*y);
  if (x == factor * (2*y))  factor--;
  x -= factor * (2*y);
  // noc hange to cur
  cur %= 3;

  cur++;
  int xnew = y;
  int ynew = abs(x - y);
  //fprintf(stderr, "return %d %d %d\n", xnew, ynew, cur);
  return calcphase(xnew, ynew, cur);
}


void solve() {
  int n;
  cin >> n;
  vector<int> a(n), b(n);
  FORI(n)  cin >> a[i];
  FORI(n)  cin >> b[i];


  bool has_0 = false, has_1 = false, has_2 = false;
  for (int i = 0; i < n; i++) {
    int x = a[i], y = b[i];
    if (x == 0 && y == 0)  continue;  //all phase
    int phase = calcphase(x, y, 0);
    phase %= 3;
    fprintf(stderr, "phase of %d %d is %d\n", x, y, phase);
    if (phase == 0)  has_0 = true;
    else if (phase == 1)  has_1 = true;
    else  has_2 = true;
  }

  int how_many = INT(has_0) + INT(has_1) + INT(has_2);
  if (how_many > 1)  cout << "NO\n";
  else  cout << "YES\n";

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

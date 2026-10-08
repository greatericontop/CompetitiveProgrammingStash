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








/* L is the size of the interval, if L > m/d, then there must be at least d of >=L */
void solve_b(int n, int m, int L) {
  cout << "Bernardo" << endl;
  set<int> taken;
  set<int> available;
  for (int x = L; x <= m; x += L) {
    available.insert(x);
  }

  for (int turn = 1; turn <= n; turn++) {
    int y, a;  cin >> y >> a;
    // a is start location, y is length

    if (y >= L) {
      auto it1 = taken.lower_bound(a);
      if (it1 != taken.end() && *it1 < a+y) {
        cout << *it1 << endl;  //and we win
      } else {
        auto it2 = available.lower_bound(a);
        assert(it2 != available.end() && *it2 < a+y);
        cout << *it2 << endl;

        taken.insert(*it2);
        available.erase(it2);
      }
    } else {
      //whatever
      cout << a << endl;
    }
  }
}


void solve() {
  int n, m;
  cin >> n >> m;
  vector<int> a(n);
  FORI(n)  cin >> a[i];
  vector<int> a_sorted = a;
  sort(a_sorted.begin(), a_sorted.end());

  for (int d = 2; d <= m; d++) {
    // count number that are strictly > m/d
    auto it = upper_bound(a_sorted.begin(), a_sorted.end(), m / d);
    int ct = a_sorted.end() - it;
    if (ct >= d) {
      int L = m/d + 1;
      solve_b(n, m, L);
      return;
    }
  }

  // otherwise A wins by doing nothing
  cout << "Alessia" << endl;
  sort(a.begin(), a.end(), greater<int>());
  set<pairii> active_intervals;
  active_intervals.insert({1, m});
  for (int sz : a) {
    // search for any segment that works; we could use prio queue but I'm lazy
    // O(5000 * bad std::set constant * 100) is easily fine
    pairii interval;
    bool found = false;
    for (const auto& i : active_intervals) {
      if (i.second - i.first + 1 >= sz) {
        interval = i;
        found = true;
        break;
      }
    }
    assert(found);
    cout << sz << " " << interval.first << endl;

    int b;  cin >> b;
    active_intervals.erase(interval);
    active_intervals.insert({interval.first, b-1});
    active_intervals.insert({b+1, interval.second});
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

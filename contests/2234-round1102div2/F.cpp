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










constexpr static long INF = 1e10;

struct Event {
  int idx;
  long height;
};

void solve() {
  int n;
  cin >> n;
  vector<int> h_old(n);
  FORI(n)  cin >> h_old[i];
  int max_h = -1;
  int index_of_max_h;
  FORI(n) {
    if (h_old[i] > max_h) {
      max_h = h_old[i];
      index_of_max_h = i;
    }
  }
  int array_offset = index_of_max_h + 1;
  vector<int> h(n);
  FORI(n) {
    h[i] = h_old[(i + array_offset) % n];
  }
  PRINTVEC(h_old);
  fprintf(stderr, "offset: %d\n", array_offset);
  PRINTVEC(h);

  vector<long> prefix_answers(n);
  vector<Event> event_stack;
  event_stack.pb({-1, INF});
  long total = 0;
  for (int i = 0; i < n; i++) {
    Event e = {i, h[i]};
    while (e.height >= event_stack.back().height) {
      Event back = event_stack.back();
      Event secondback = event_stack[event_stack.size() - 2];
      total -= LONG(back.idx - secondback.idx) * (back.height);
      event_stack.pop_back();
    }
    Event back = event_stack.back();
    total += LONG(i - back.idx) * (e.height);
    event_stack.pb(e);
    prefix_answers[i] = total;
  }
  PRINTVECL(prefix_answers);

  vector<long> suffix_answers(n);
  event_stack.clear();
  event_stack.pb({n, INF});
  total = 0;
  for (int i = n - 1; i >= 1; i--) {
    Event e = {i, h[i-1]};
    while (e.height >= event_stack.back().height) {
      Event back = event_stack.back();
      Event secondback = event_stack[event_stack.size() - 2];
      total -= LONG(secondback.idx - back.idx) * (back.height);
      event_stack.pop_back();
    }
    Event back = event_stack.back();
    total += LONG(back.idx - i) * (e.height);
    event_stack.pb(e);
    suffix_answers[i] = total;
  }
  PRINTVECL(suffix_answers);


  for (int i_orig = 0; i_orig < n; i_orig++) {
    int i = (i_orig - array_offset + 2*n) % n;
    long ans = 0;
    if (i > 0)  ans += prefix_answers[i-1];
    if (i < n - 1)  ans += suffix_answers[i+1];
    cout << ans << " ";
  }
  cout << "\n";

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

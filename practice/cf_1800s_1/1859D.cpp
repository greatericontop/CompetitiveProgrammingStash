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










struct Portal {
  int l;
  int r;
  int a;
  int b;

  bool operator < (const Portal& other) const {
    return b < other.b;
  }
};

struct AnswerEntry {
  int l;  //working number
  int r;  //all within range [l, r] can be teleported to r
};

void solve() {
  int n;
  cin >> n;
  vector<Portal> portals(n);
  FORI(n) {
    cin >> portals[i].l >> portals[i].r >> portals[i].a >> portals[i].b;
  }
  int q;
  cin >> q;
  vector<int> queries(q);
  FORI(q)  cin >> queries[i];
  sort(portals.begin(), portals.end());

  vector<AnswerEntry> ans_stack;
  ans_stack.pb(AnswerEntry{portals.back().l, portals.back().b});

  for (int i = n-2; i >= 0; i--) {
    Portal p = portals[i];

    // check if it overlaps the current frame
    if (p.b >= ans_stack.back().l) {
      // extend current frame
      ans_stack.back().l = min(ans_stack.back().l, p.l);
    } else {
      // add a new frame
      ans_stack.pb(AnswerEntry{p.l, p.b});
    }
  }

  reverse(ans_stack.begin(), ans_stack.end());

  for (int query : queries) {
    // find the segment that contains us, if applicable
    auto it = lower_bound(ans_stack.begin(), ans_stack.end(), query, [](const AnswerEntry& entry, int q) {
      return entry.r < q;
    });
    if (it == ans_stack.end()) {
      cout << query << " ";
    } else {
      if (it->l <= query) {
        cout << it->r << " ";
      } else {
        // not actually in range
        cout << query << " ";
      }
    }
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

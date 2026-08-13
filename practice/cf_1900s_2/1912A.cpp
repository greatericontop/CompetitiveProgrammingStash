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









struct Chunk {
  long total_delta;
  long required_x;
  int list_id;

  bool operator < (const Chunk& other) const {
    // sort by required_x, lowest first
    return required_x < other.required_x;
  }
};


void solve() {
  long x; int m;
  cin >> x >> m;
  vector<vector<int>> lists(m);
  for (int i = 0; i < m; i++) {
    int l;  cin >> l;
    lists[i].resize(l);
    for (int j = 0; j < l; j++) {
      cin >> lists[i][j];
    }
  }
  vector<vector<Chunk>> chunks(m);
  for (int i = 0; i < m; i++) {
    long total_delta = 0;
    long required_x = 0;
    for (int j = 0; j < lists[i].size(); j++) {
      // end the current chunk if lists[i][j] is negative and total_delta is positive. discard the last one if needed
      if (total_delta > 0 && lists[i][j] < 0) {
        chunks[i].pb(Chunk{total_delta, required_x, i});
        total_delta = 0;
        required_x = 0;
      }
      total_delta += lists[i][j];
      required_x = max(required_x, -total_delta);
    }
    if (total_delta > 0) {
      // last one
      chunks[i].pb(Chunk{total_delta, required_x, i});
    }
    reverse(chunks[i].begin(), chunks[i].end());
  }

  multiset<Chunk> active_chunks;
  for (int i = 0; i < m; i++) {
    if (!chunks[i].empty()) {
      active_chunks.insert(chunks[i].back());
      chunks[i].pop_back();
    }
  }
  while (!active_chunks.empty()) {
    auto it = active_chunks.begin();
    Chunk c = *it;
    active_chunks.erase(it);
    if (c.required_x > x) {
      break;
    } else {
      x += c.total_delta;
      if (!chunks[c.list_id].empty()) {
        // push next one (which is at the back of the list)
        active_chunks.insert(chunks[c.list_id].back());
        chunks[c.list_id].pop_back();
      }
    }
  }

  cout << x << "\n";

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

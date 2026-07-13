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









struct VertexEntry {
  int v;
  int deg;

  bool operator < (const VertexEntry& other) const {
    if (deg != other.deg)  return deg > other.deg;
    return v < other.v;
  }
};


void solve() {
  int n;
  cin >> n;
  vector<int> degrees(n+1);
  FORI1(n)  cin >> degrees[i];

  vector<VertexEntry> entries(n);
  FORI1(n)  entries[i-1] = VertexEntry{i, degrees[i]};
  sort(entries.begin(), entries.end());

  vector<int> colors(n+1, -1);
  int next_color = 1;

  for (int p = 0; p < n; p++) {
    VertexEntry entry = entries[p];
    fprintf(stderr, "entries[%d] vertex %d degree %d\n", p, entry.v, entry.deg);
    if (colors[entry.v] != -1)  continue;  //already visited

    set<int> our_glob;
    our_glob.insert(entry.v);
    bool glob_is_new = true;
    for (int q = 0; q < degrees[entry.v]; q++) {
      cout << "? " << entry.v << endl;
      int u;
      cin >> u;
      assert(u != -1);

      if (colors[u] != -1) {
        // merge our glob with theirs
        for (int v : our_glob) {
          colors[v] = colors[u];
        }
        glob_is_new = false;
        break;
      } else {
        // otherwise this is part of our glob
        our_glob.insert(u);
      }
    }

    if (glob_is_new) {
      for (int v : our_glob) {
        colors[v] = next_color;
      }
      next_color++;
    }
  }

  cout << "!";
  for (int i = 1; i <= n; i++) {
    cout << " " << colors[i];
  }
  cout << endl;

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

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
// Round :a: down or up to the closest multiple of :b:
constexpr static inline int rounddown(int a, int b) { return (a / b) * b; }
constexpr static inline int roundup(int a, int b) { return ceildiv(a, b) * b; }
//constexpr static long MOD = 1'000'000'007LL;
//constexpr static long MOD =   998'244'353LL;








struct Monster {
  int id;
  int atk;
  int def;

  bool operator < (const Monster& other) const {
    return id < other.id;
  }
};



void solve() {
  int n;
  cin >> n;
  vector<Monster> monsters(n);
  FORI(n)  monsters[i].id = i;
  FORI(n)  cin >> monsters[i].atk;
  FORI(n)  cin >> monsters[i].def;

  set<Monster> alive_monsters;
  FORI(n)  alive_monsters.insert(monsters[i]);
  vector<int> deletion_queue;  deletion_queue.reserve(n+10);
  FORI(n) {
    int dmg = 0;
    if (i > 0)  dmg += monsters[i-1].atk;
    if (i < n-1)  dmg += monsters[i+1].atk;
    if (dmg > monsters[i].def)  deletion_queue.pb(i);
  }
  vector<int> evaluation_queue;  evaluation_queue.reserve(n+10);

  for (int round = 1; round <= n; round++) {
    fprintf(stderr, "Round %d:  active monsters:", round);
    for (const auto& m : alive_monsters)  fprintf(stderr, " %d", m.id);
    fprintf(stderr, ";  deleting  ");
    PRINTVEC(deletion_queue);
    // delete all monsters in deletion queue, and push their neighbors to evaluation queue
    int delct = 0;
    for (int id : deletion_queue) {
      auto it = alive_monsters.find(monsters[id]);
      if (it == alive_monsters.end())  continue;  //deletion_queue could contain dupes
      if (it != alive_monsters.begin())  evaluation_queue.pb(prev(it)->id);
      if (next(it) != alive_monsters.end())  evaluation_queue.pb(next(it)->id);
      alive_monsters.erase(it);
      delct++;
    }
    // calc deletions for next round
    deletion_queue.clear();
    for (int id : evaluation_queue) {
      auto it = alive_monsters.find(monsters[id]);
      if (it == alive_monsters.end())  continue;  // maybe they got deleted
      int dmg = 0;
      if (it != alive_monsters.begin())  dmg += prev(it)->atk;
      if (next(it) != alive_monsters.end())  dmg += next(it)->atk;
      if (dmg > it->def)  deletion_queue.pb(it->id);
    }
    evaluation_queue.clear();
    cout << delct << " ";
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

/*
 * This code contains the use of comments! You can identify them with the "//" or "/*" symbols.
 * Comments are used to explain the code and make it easier to understand.
 * They are ignored by the compiler and do not affect the execution of the program.
 * In this code, comments are used to explain the purpose of the code, the input and output format, and the logic behind the solution.
 * Unlike the 3 lines shown above, the comments in this code were lovingly hand-inserted and not a result of AI generated text.
 * Thanks to sc3developer <3 for inspiring this message and for being a great mentor.
 */

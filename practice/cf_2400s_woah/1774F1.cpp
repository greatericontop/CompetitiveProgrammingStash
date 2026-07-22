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
constexpr static long MOD =   998'244'353LL;


constexpr int CREATE = 1;
constexpr int HURT = 2;
constexpr int REPEAT = 3;
constexpr int MAXHP = 8;
//constexpr int MAXHP = 200000;
struct Operation {
  int type;
  int x;
};
struct State {
  map<long, long> pigs;
  long total_dmg;
  long zero_offset;

  void print() const {
    fprintf(stderr, "state: [");
    for (auto [h, ct] : pigs) {
      fprintf(stderr, "%ld (%ld) x%ld,  ", h, h-zero_offset, ct);
    }
    fprintf(stderr, "],  zero offset %ld,  total_dmg: %ld\n", zero_offset, total_dmg);
  }
};







void solve() {
  int n;
  cin >> n;
  vector<Operation> ops(n);
  FORI(n) {
    cin >> ops[i].type;
    if (ops[i].type != REPEAT) {
      cin >> ops[i].x;
    } else {
      ops[i].x = -1;
    }
  }

  int index_of_first_hurt = 0;
  while (index_of_first_hurt < n && ops[index_of_first_hurt].type != HURT) {
    index_of_first_hurt++;
  }
  vector<long> suffix_product(n+1);
  suffix_product[index_of_first_hurt] = 1;
  for (int i = index_of_first_hurt-1; i >= 0; i--) {
    if (ops[i].type == REPEAT) {
      suffix_product[i] = suffix_product[i+1] * 2;
      suffix_product[i] %= MOD;
    } else {
      suffix_product[i] = suffix_product[i+1];
    }
  }

  State state = {.pigs = {}, .total_dmg = 0, .zero_offset = 0};
  for (int i = 0; i <= index_of_first_hurt; i++) {
    if (ops[i].type == CREATE) {
      state.pigs[ops[i].x] += suffix_product[i];
      state.pigs[ops[i].x] %= MOD;
    }
  }

  state.print();

  for (int i = index_of_first_hurt; i < n; i++) {
    if (ops[i].type == CREATE) {
      state.pigs[ops[i].x + state.zero_offset]++;
      state.pigs[ops[i].x + state.zero_offset] %= MOD;
    } else if (ops[i].type == HURT) {
      state.total_dmg += ops[i].x;
      state.zero_offset += ops[i].x;  //what number in the map is considered zero
    } else {  //REPEAT
      if (state.total_dmg >= 200'000) {
        // no-op
      } else {
        // expensive step, but only done up to 18 times
        State state_cur = state;

        // new state :state: already contains new pigs, so let's add the old pigs
        for (auto [old_health, old_ct] : state_cur.pigs) {
          long new_health = old_health - state_cur.total_dmg;
          if (new_health > state_cur.zero_offset) {
            state.pigs[new_health] += old_ct;
            state.pigs[new_health] %= MOD;
          }
        }

        state.total_dmg = state_cur.total_dmg * 2;
      }
    }

    //trimming
    //runs at most ~=200k times total
    for (auto it = state.pigs.begin(); it != state.pigs.end(); ) {
      if (it->first <= state.zero_offset) {
        it = state.pigs.erase(it);
      } else {
        break;
      }
    }

    fprintf(stderr, "after op %d:   ", i);  state.print();
  }


  long pigs_alive = 0;
  for (auto [health, ct] : state.pigs) {
    if (health > state.zero_offset) {
      pigs_alive += ct;
      pigs_alive %= MOD;
    }
  }
  cout << pigs_alive << "\n";
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
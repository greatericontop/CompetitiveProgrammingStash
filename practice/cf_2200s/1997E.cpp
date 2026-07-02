#include <bits/stdc++.h>
using namespace std;


//#define GREATERIC_DEBUG


#ifdef GREATERIC_DEBUG
  #define PRINTVECB(vec) do { \
    fprintf(stderr, "%s:  ", #vec); \
    for (const auto& _x : (vec))  fprintf(stderr, "%d ", INT(_x)); \
    fprintf(stderr, "\n"); \
  } while (0)
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
#define PRINTVECB(...)
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









//int BORDER = 10000, MAXLVL = 10;
//int BORDER = -1, MAXLVL = 25;

constexpr int BORDER = 627;
constexpr int MAXLVL = 320;  // due to memory limit


struct Query {
  int idx;
  int kval;
  int query_i;
};


void solve() {
  int n, q;
  cin >> n >> q;
  vector<int> a(n+1);
  FORI1(n)  cin >> a[i];
  vector<Query> queries(q);
  FORI(q) {
    cin >> queries[i].idx >> queries[i].kval;
    queries[i].query_i = i;
  }
  sort(queries.begin(), queries.end(), [](const Query& q1, const Query& q2) {
    return q1.kval < q2.kval;
  });
  int qptr = 0;  //points to next unanswered query
  vector<bool> q_answers(q);


  // Handle kval <= BORDER
  for (int k = 1; k <= BORDER; k++) {
    vector<bool> fights(n+1, false);
    int lvl = 0;
    int partial_fights = 0;
    for (int i = 1; i <= n; i++) {
      if (a[i] > lvl) {
        partial_fights++;
        fights[i] = true;
        if (partial_fights >= k) {
          partial_fights = 0;
          lvl++;
        }
      }
    }
    if (k <= 10) { fprintf(stderr, "k = %d\n", k); PRINTVECB(fights); }

    // now answer queries
    while (qptr < q && queries[qptr].kval == k) {
      q_answers[queries[qptr].query_i] = fights[queries[qptr].idx];
      qptr++;
    }
  }


  // Jump table calculation
  // jumptablei[lvl][i] -> what # it is
  // jumptablenum[lvl][#] -> first index that gets it
  vector<vector<int>> jumptablei(MAXLVL+1, vector<int>(n+2, INT_MAX));
  vector<vector<int>> jumptablenum(MAXLVL+1, vector<int>(n+2, INT_MAX));
  for (int lvl = 0; lvl <= MAXLVL; lvl++) {
    jumptablei[lvl][0] = 0;
    jumptablenum[lvl][0] = 0;
    int num = 0;
    for (int i = 1; i <= n; i++) {
      if (a[i] > lvl) {
        num++;
        jumptablei[lvl][i] = num;
        jumptablenum[lvl][num] = i;
      } else {
        jumptablei[lvl][i] = num;
      }
    }
  }


  for (; qptr < q; qptr++) {
    int query_idx = queries[qptr].idx;
    int kval = queries[qptr].kval;

    int lvl_start_i = 1;
    int lvl = 0;
    while (true) {

      int num_of_current = jumptablei[lvl][lvl_start_i-1];
      int lvl_end_i = jumptablenum[lvl][min(num_of_current + kval, n+1)];  //will be INT_MAX if we go past the end

      if (query_idx <= lvl_end_i) {
        bool was_fight = (a[query_idx] > lvl);
        q_answers[queries[qptr].query_i] = was_fight;
        break;
      } else {
        lvl++;
        lvl_start_i = lvl_end_i + 1;
      }
    }
  }

  for (int i = 0; i < q; i++) {
    cout << (q_answers[i] ? "YES" : "NO") << "\n";
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

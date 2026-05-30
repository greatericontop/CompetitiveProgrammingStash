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










void solve() {
  int n;
  long x, s;
  cin >> n >> x >> s;
  string str;
  cin >> str;

  string str_e = str;
  int a_count = 0;
  set<int> a_indices;
  for (int i = 0; i < n; i++) {
    if (str[i] == 'A') {
      a_count++;
      a_indices.insert(i);
      str_e[i] = 'E';
    }
  }

  vector<int> suffix_e_count(n+1, 0);
  vector<int> suffix_i_count(n+1, 0);
  for (int i = n-1; i >= 0; i--) {
    suffix_e_count[i] = suffix_e_count[i+1] + (str_e[i] == 'E' ? 1 : 0);
    suffix_i_count[i] = suffix_i_count[i+1] + (str_e[i] == 'I' ? 1 : 0);
  }
  vector<int> dropped_e(n+1);
  dropped_e[n] = 0;
  for (int i = n-1; i >= 0; i--) {
    int prev = dropped_e[i+1];
    if (str_e[i] == 'E') {
      prev++;
    } else {
      prev = max(0, prev - INT(s-1));
    }
    dropped_e[i] = prev;
  }




  // try all is E (since this is not checked by the loop)
  int tables = 0;
  int total_seats = 0;
  for (char c : str_e) {
    if (c == 'I') {
      if (tables < x) {
        tables++;
        total_seats++;
      }
    } else {
      if (total_seats < tables * s) {
        total_seats++;
      }
    }
  }

  long best_answer_so_far = total_seats;
  fprintf(stderr, "initial answer: %lld\n", best_answer_so_far);

  long i_count_sweeped = 0;
  long e_count_sweeped = 0;
  int e_surplus = 0;

  for (int i = 0; i < n; i++) {

    if (str[i] == 'I') {
      i_count_sweeped++;
      e_surplus += s-1;
    } else if (str[i] == 'E') {
      if (e_surplus > 0) {
        e_surplus--;
        e_count_sweeped++;
      }  //no surplus, do nothing, irrecoverably lost
    } else {  //str[i] == 'A'
      fprintf(stderr, "str[%d] is A\n", i);
      // turn into an I
      i_count_sweeped++;
      e_surplus += s-1;
      fprintf(stderr, "  i sweeped: %lld, e surplus: %d\n", i_count_sweeped, e_surplus);

      // see how much of the future we can sweep
      int total_future_e = suffix_e_count[i+1];
      int e_dropped = dropped_e[i+1];
      fprintf(stderr, "  e dropped initially: %d of %d\n", e_dropped, total_future_e);
      e_dropped = max(0, e_dropped - e_surplus);
      int bonus_e = total_future_e - e_dropped;
      int bonus_i = suffix_i_count[i+1];
      long total_e = min(e_count_sweeped + bonus_e, x*(s-1));
      long total_i = min(i_count_sweeped + bonus_i, x);
      fprintf(stderr, "  e dropped (after surplus) %d, total e %lld\n", e_dropped, total_e);

      long answer = total_e + total_i;
      best_answer_so_far = max(best_answer_so_far, answer);
      fprintf(stderr, "  answer here = %lld\n", answer);

    }


  }

  cout << best_answer_so_far << "\n";

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

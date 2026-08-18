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




// evaluate single expression
pair<long, bool> eval(string s) {
  long result = 0;

  int cur_multiplier = 1;
  long cur_num = 0;
  int cur_digits = 0;
  bool cur_leading_zero = false;

  s += '+';  //end character
  for (char c : s) {
    if (c == '+' || c == '-') {
      if (cur_digits == 0) {
        goto fail;
      } else {
        fprintf(stderr, "  adding %d * %ld\n", cur_multiplier, cur_num);
        result += cur_multiplier * cur_num;
        cur_multiplier = (c == '+') ? 1 : -1;
        cur_num = 0;
        cur_digits = 0;
        cur_leading_zero = false;
      }
    } else if (isdigit(c)) {
      int d = c - '0';
      if (cur_digits == 0)  cur_leading_zero = (d == 0);
      cur_num = 10*cur_num + d;
      cur_digits++;
      if (cur_leading_zero && cur_digits > 1) {
        goto fail;
      } else if (cur_digits > 10) {
        goto fail;
      }
    } else {
      goto fail;
    }
  }
  fprintf(stderr, "return %s ---> %ld\n", s.c_str(), result);
  return {result, true};

  fail:
  return {-1, false};
}


bool check(string s) {
  int pos_of_eq = s.find('=');
  string s1 = s.substr(0, pos_of_eq);
  string s2 = s.substr(pos_of_eq + 1);
  auto [val1, ok1] = eval(s1);
  auto [val2, ok2] = eval(s2);
  if (!ok1 || !ok2)  return false;
  return val1 == val2;
}




void solve() {
  string s;  cin >> s;
  int n = s.size();

  if (check(s)) {
    cout << "Correct\n";
    return;
  }

  for (int i = 0; i < n; i++) {
    if (!isdigit(s[i]))  continue;
    string s1 = s.substr(0, i) + s.substr(i+1);
    for (int j = 0; j < n-1; j++) {
      string s2 = s1.substr(0, j) + s[i] + s1.substr(j);
      if (check(s2)) {
        cout << s2 << "\n";
        return;
      }
    }
    string s3 = s[i] + s1;
    if (check(s3)) {
      cout << s3 << "\n";
      return;
    }

  }

  cout << "Impossible\n";

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

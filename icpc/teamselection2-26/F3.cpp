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




char flip(char x) {
  return x == 'T' ? 'F' : 'T';
}


void solve() {
  int n, k;
  cin >> n >> k;
  vector<string> a(n);
  FORI(n)  cin >> a[i];

  string forced_answers(k, 'X');
  vector<vector<int>> same(k);
  vector<vector<int>> different(k);
  bool impossible = false;


  // Combine a[i] and a[j] students
  auto combine = [&](int i, int j) {
    assert(i != j);
    if (j < i)  swap(i, j);
    vector<int> differ_pos;
    string new_entry(k, '.');
    for (int h = 0; h < k; h++) {
      if (a[i][h] == 'X') {
        new_entry[h] = a[j][h];
      } else if (a[j][h] == 'X') {
        new_entry[h] = a[i][h];
      } else {
        if (a[i][h] == a[j][h]) {
          new_entry[h] = a[i][h];
        } else {
          differ_pos.pb(h);
          new_entry[h] = 'X';
        }
      }
    }
    if (differ_pos.size() <= 1) {
      // Delete old, push new
      //a.erase(a.begin() + j);
      //a.erase(a.begin() + i);
      //a.pb(new_entry);
    } else if (differ_pos.size() >= 3) {
      impossible = true;
    } else {
      for (int h = 0; h < k; h++) {
        if (new_entry[h] != 'X') {
          if (forced_answers[h] == new_entry[h])  impossible = true;
          forced_answers[h] = flip(new_entry[h]);
        }
      }
      // then add constraint with the new differs
      int d1 = differ_pos[0], d2 = differ_pos[1];  assert(d1 < d2);
      // if a is T and T then one of them needs to be false
      if (a[i][d1] == a[i][d2]) {
        different[d2].pb(d1);
      } else {
        same[d2].pb(d1);
      }

      //a.erase(a.begin() + j);
      //a.erase(a.begin() + i);
    }
  };



  for (int i = 0; i < n; i++) {
    for (int j = i+1; j < n; j++) {
      combine(i, j);
    }
  }

  fprintf(stderr, "Students:\n");
  for (int i = 0; i < a.size(); i++) {
    fprintf(stderr, "%s\n", a[i].c_str());
  }
  fprintf(stderr, "poss: %d, forced: %s\n", impossible ? 0 : 1, forced_answers.c_str());

  // try to set the bit at i
  for (int i = 0; i < n; i++) {
    fprintf(stderr, "i=%d = %c\n", i, forced_answers[i]);
    if (forced_answers[i] == 'X') {
      forced_answers[i] = 'F';
    }
    fprintf(stderr, "i=%d = %c\n", i, forced_answers[i]);
    // now propagate implications
    for (int s = 0; s < n; s++) {  //student s
      vector<int> correct_answers;
      for (int h = 0; h < k; h++) {
        if (a[s][h] != 'X' && a[s][h] == forced_answers[h]) {
          correct_answers.pb(h);
        }
      }
      fprintf(stderr, "  student %d has correct answers", s); PRINTVEC(correct_answers);
      if (correct_answers.size() >= 2) {
        impossible = true;
        break;
      } else if (correct_answers.size() >= 1) {
        // then rest must be false
        for (int h = 0; h < k; h++) {
          if (h == correct_answers.front())  continue;
          if (a[s][h] == 'X')  continue;
          if (forced_answers[h] == a[s][h]) {
            impossible = true;
            break;
          } else {
            fprintf(stderr, "  student %d forces position %d\n", s, h);
            forced_answers[h] = flip(a[s][h]);
          }
        }
      }
    }
  }

  if (impossible) {
    cout << "-1\n";
  } else {
    cout << forced_answers << "\n";
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

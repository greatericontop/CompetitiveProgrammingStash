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








bool final_step(multiset<long> fib, multiset<long> counts_left, long who, const vector<long>& fib_all_v) {
  auto it1 = counts_left.find(who);
  counts_left.erase(it1);

  fprintf(stderr, "  decomposing %ld into\n", who);
  for (int i = 0; i < fib_all_v.size(); i += 2) {
    long f = fib_all_v[i];  //1, 2, 5, 13 ---> 21
    fprintf(stderr, "    %ld\n", f);
    who -= f;
    auto it = fib.find(f);
    if (it == fib.end())  return false;
    fib.erase(it);
    if (who == 0)  break;
    if (who < 0)  return false;
  }

  // now check that sets are equal
  if (fib != counts_left)  return false;
  return true;
}



void solve() {
  int n;  cin >> n;
  vector<long> counts(n);
  FORI(n)  cin >> counts[i];
  long total = accumulate(counts.begin(), counts.end(), 0LL);
  multiset<long> fib;
  vector<long> fib_all_v;  multiset<long> fib_all_s;
  long a = 0, b = 1, fib_sum = 0;
  while (true) {
    if (fib_sum + b > total) {
      break;
    }
    fib.insert(b);
    fib_sum += b;
    long c = a + b;  a = b;  b = c;
  }
  a = 0;  b = 1;
  while (b <= LONG(1e15)) {
    fib_all_v.pb(b);  fib_all_s.insert(b);
    long c = a + b;  a = b;  b = c;
  }
  if (fib_sum != total) {
    cout << "NO\n";
    return;
  }

  multiset<long> counts_left;
  multiset<long> counts_set;  for (long x : counts)  counts_set.insert(x);
  while (!counts_set.empty()) {
    long x = *counts_set.begin();
    counts_set.erase(counts_set.begin());

    if (fib_all_s.count(x)) {
      // this is a fib number so we have to handle it specially
      counts_left.insert(x);
    } else {
      // otherwise we must subtract the largest fib number
      long largest_fib = *prev(upper_bound(fib_all_v.begin(), fib_all_v.end(), x));
      assert(largest_fib < x);
      if (!fib.count(largest_fib)) {
        cout << "NO\n";
        return;
      }
      fib.erase(fib.find(largest_fib));
      x -= largest_fib;
      counts_set.insert(x);
    }
  }

  fprintf(stderr, "now we have:\n");
  PRINTVECL(counts_left);
  PRINTVECL(fib);

  for (long who : counts_left) {
    if (final_step(fib, counts_left, who, fib_all_v)) {
      fprintf(stderr, "success for who=%ld\n", who);
      cout << "YES\n";
      return;
    }
  }
  cout << "NO\n";

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

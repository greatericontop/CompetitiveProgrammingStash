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


#pragma GCC optimize("Ofast")


using MaxHeap = priority_queue<long, vector<long>, less<long>>;
using MinHeap = priority_queue<long, vector<long>, greater<long>>;



struct SumMultiset {
  MaxHeap internal;
  long sum;

  void insert(long x) {
    internal.push(x);
    sum += x;
  }

  long top() {
    return internal.top();
  }

  void erase_max(long x) {
    //assert(internal.top() == x);
    internal.pop();
    sum -= x;
  }
};



vector<int> count(int n, const vector<long>& a, long limit) {
  vector<int> ans(n);
  SumMultiset taken;  taken.sum = 0;
  MinHeap untaken;

  for (int i = 0; i < n; i++) {
    if (!taken.internal.empty() && a[i] < taken.top()) {
      // swap them
      long x = a[i], y = taken.top();
      taken.erase_max(y);
      untaken.push(y);
      taken.insert(x);
    } else {
      untaken.push(a[i]);
    }

    // now add elts while we can
    while (!untaken.empty()) {
      long z = untaken.top();
      if (taken.sum + z <= limit) {
        taken.insert(z);
        untaken.pop();
      } else {
        break;
      }
    }

    ans[i] = taken.internal.size();
  }
  return ans;
}


bool possible(int n, const vector<long>& a, const vector<long>& a_rev, int k, long limit) {
  vector<int> left_sizes = count(n, a, limit);
  vector<int> right_sizes = count(n, a_rev, limit);  reverse(right_sizes.begin(), right_sizes.end());
  fprintf(stderr, "called on limit=%ld\n", limit);
  PRINTVEC(left_sizes);
  PRINTVEC(right_sizes);

  // i is where right starts
  for (int i = 0; i <= n; i++) {
    int left_size = i == 0 ? 0 : left_sizes[i-1];
    int right_size = i == n ? 0 : right_sizes[i];
    if (left_size + right_size >= k) {
      return true;
    }
  }
  return false;
}




void solve() {
  int n, k;  cin >> n >> k;
  vector<long> a(n);
  FORI(n)  cin >> a[i];
  vector<long> a_rev = a;  reverse(a_rev.begin(), a_rev.end());

  long l = 0, r = LONG(3e14);
  while (l < r) {
    long mid = l + (r-l)/2;
    if (possible(n, a, a_rev, k, mid)) {
      r = mid;
    } else {
      l = mid + 1;
    }
  }

  cout << l << "\n";

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

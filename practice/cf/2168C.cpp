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










void solve_first() {
  int x;
  cin >> x;
  x--;
  uint8_t bits[21] = {};  //should be 0-1
  for (int i = 1; i <= 15; i++) {
    bits[i] = (x >> (i-1)) & 1;
  }
  bits[16] = bits[1] ^ bits[3] ^ bits[5] ^ bits[7] ^ bits[9] ^ bits[11] ^ bits[13] ^ bits[15];
  bits[17] = bits[2] ^ bits[3] ^ bits[6] ^ bits[7] ^ bits[10] ^ bits[11] ^ bits[14] ^ bits[15];
  bits[18] = bits[4] ^ bits[5] ^ bits[6] ^ bits[7] ^ bits[12] ^ bits[13] ^ bits[14] ^ bits[15];
  bits[19] = bits[8] ^ bits[9] ^ bits[10] ^ bits[11] ^ bits[12] ^ bits[13] ^ bits[14] ^ bits[15];
  bits[20] = bits[16] ^ bits[17] ^ bits[18] ^ bits[19];

  vector<int> output;
  int output_sz = 0;
  for (int b = 1; b <= 20; b++) {
    if (bits[b]) {
      output.pb(b);
      output_sz++;
    }
  }
  cout << output_sz << "\n";
  for (int o : output) {
    cout << o << " ";
  }
  cout << "\n";
}


void solve_second() {
  int n;
  cin >> n;
  uint8_t bits[21] = {};
  FORI(n) {
    int x;
    cin >> x;
    bits[x] = 1;
  }
  if (bits[16] ^ bits[17] ^ bits[18] ^ bits[19] ^ bits[20]) {
    // parity error occurred, so the main data bits are safe
  } else {
    // no parity error, so see if the main data bits are flipped
    uint8_t p0 = bits[16] ^ bits[1] ^ bits[3] ^ bits[5] ^ bits[7] ^ bits[9] ^ bits[11] ^ bits[13] ^ bits[15];
    uint8_t p1 = bits[17] ^ bits[2] ^ bits[3] ^ bits[6] ^ bits[7] ^ bits[10] ^ bits[11] ^ bits[14] ^ bits[15];
    uint8_t p2 = bits[18] ^ bits[4] ^ bits[5] ^ bits[6] ^ bits[7] ^ bits[12] ^ bits[13] ^ bits[14] ^ bits[15];
    uint8_t p3 = bits[19] ^ bits[8] ^ bits[9] ^ bits[10] ^ bits[11] ^ bits[12] ^ bits[13] ^ bits[14] ^ bits[15];
    int flipped_bit_address = p0 + (p1<<1) + (p2<<2) + (p3<<3);
    if (flipped_bit_address != 0) {
      bits[flipped_bit_address] ^= 1;
    }
  }
  int ans = 0;
  for (int b = 0; b < 15; b++) {
    ans |= bits[b+1] << b;
  }
  ans++;
  cout << ans << "\n";
}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  string run;
  cin >> run;
  if (run == "first") {
    int t = 1;
    cin >> t;
    while (t--)  solve_first();
  } else if (run == "second") {
    int t = 1;
    cin >> t;
    while (t--)  solve_second();
  } else {
    return 2;
  }
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

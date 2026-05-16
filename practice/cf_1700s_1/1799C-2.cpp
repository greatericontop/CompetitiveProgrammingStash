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
#define FORI(x) for (int i = 0; i < (x); i++)
using pairii = pair<int, int>;
using pairll = pair<long, long>;
using AdjList = vector<vector<int>>;
// Positive numbers only
constexpr static inline int ceildiv(int a, int b) { return (a + b - 1) / b; }
constexpr static inline long ceildivl(long a, long b) { return (a + b - 1) / b; }










void solve() {
  string s;
  cin >> s;
  int n = (int) s.size();

  map<char, int> freq;
  set<char> chars;
  for (char c : s) {
    freq[c]++;
    chars.insert(c);
  }
  if (chars.size() == 1) {
    cout << s << "\n";
    return;
  }
  char second_to_last = *prev(chars.end(), 2);

  string s_new(n, '.');
  int i = 0, j = n-1;
  char odd_char = '.';
  for (char c = 'a'; c <= 'z'; c++) {
    int f = freq[c];
    while (f >= 2) {
      s_new[i++] = c;
      s_new[j--] = c;
      f -= 2;
    }
    if (f % 2 == 0) {
      // do nothing
    } else if (odd_char == '.') {
      if (c == second_to_last) {
        // save it
        odd_char = c;
      } else {
        // transition to end state
        s_new[j--] = c;
        for (char d = c+1; d <= 'z'; d++) {
          int f2 = freq[d];
          while (f2 >= 1) {
            s_new[i++] = d;
            f2--;
          }
        }
        assert(i == j+1);
        break;
      }
    } else {
      // odd char already made: transition to end state
      s_new[j--] = odd_char;
      s_new[i++] = c;
      for (char d = c+1; d <= 'z'; d++) {
        int f2 = freq[d];
        while (f2 >= 1) {
          s_new[i++] = d;
          f2--;
        }
      }
      assert(i == j+1);
      odd_char = '.';
      break;
    }
  }

  if (odd_char != '.') {
    assert(i == j);
    s_new[i] = odd_char;
  }

  cout << s_new << "\n";

}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  cin >> t;
  while (t--)  solve();
  return 0;
}

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
#define INT(x) ((int) (x))
#define FORI(x) for (int i = 0; i < (x); i++)
using pairii = pair<int, int>;
using pairll = pair<long, long>;
using AdjList = vector<vector<int>>;
// Positive numbers only
constexpr static inline int ceildiv(int a, int b) { return (a + b - 1) / b; }
constexpr static inline long ceildivl(long a, long b) { return (a + b - 1) / b; }
// Only O(1) for vectors!
template <typename It, typename Container> constexpr static inline int itertoi(const It& it, const Container& container) { return distance(container.begin(), it); }










void solve() {
  string s;
  cin >> s;
  int n = s.size();

  int count_vowel = 0;
  int count_y = 0;
  int count_cons = 0;
  int count_n = 0;
  int count_g = 0;
  for (char c : s) {
    if (c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U')  count_vowel++;
    else if (c == 'Y')  count_y++;
    else if (c == 'G')  count_g++;
    else if (c == 'N')  count_n++;
    else  count_cons++;
  }
  int count_ng = min(count_n, count_g);
  count_cons += max(count_n, count_g) - count_ng;

  fprintf(stderr, "vowel: %d, y: %d, cons: %d, ng: %d\n", count_y, count_y, count_n, count_ng);

  // How many groups can we create
  int l = 0, r = n/3+10;
  while (l < r) {
    int groups = l + (r-l+1)/2;
    // need groups vowels
    int ys_consumed = max(0, groups - count_vowel);
    if (ys_consumed > count_y) {
      r = groups-1;
      continue;
    }

    int consonants = count_cons + (count_y - ys_consumed) + 2*count_ng;
    if (consonants >= 2*groups)  l = groups;
    else  r = groups-1;
  }

  int groups = l;
  fprintf(stderr, "groups: %d\n", groups);
  int ys_consumed = max(0, groups - count_vowel);
  int consonants = count_cons + (count_y - ys_consumed);
  int required_consonants = 2*groups;
  int consonant_letters_used;
  if (consonants + count_ng >= required_consonants) {
    // use count_ng first
    int ng_used = min(count_ng, required_consonants);
    consonant_letters_used = 2*ng_used;
    consonant_letters_used += (required_consonants-ng_used);
  } else {
    // split some ng
    consonant_letters_used = required_consonants;
  }

  int ans = consonant_letters_used + groups;
  cout << ans << "\n";



}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  //cin >> t;
  while (t--)  solve();
  return 0;
}

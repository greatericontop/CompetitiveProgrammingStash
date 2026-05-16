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
using pairii = pair<int, int>;
using pairll = pair<long, long>;
using AdjList = vector<vector<int>>;
// Positive numbers only
constexpr static inline int ceildiv(int a, int b) { return (a + b - 1) / b; }
constexpr static inline long ceildivl(long a, long b) { return (a + b - 1) / b; }
// Only O(1) for vectors!
template <typename It, typename Container> constexpr static inline int itertoi(const It& it, const Container& container) { return distance(container.begin(), it); }









long vectonum(const vector<int>& v) {
  long ret = 0;
  for (int d : v) {
    ret = ret * 10 + d;
  }
  return ret;
}


long afill(long a, const vector<int>& av, vector<int>& alreadyfilled, const set<int>& digits) {
  if (alreadyfilled.size() == av.size()) {
    return vectonum(alreadyfilled);
  }
  // try overshooting current digit
  auto it = digits.upper_bound(av[alreadyfilled.size()]);
  if (it == digits.end())  it = prev(it);
  vector<int> alreadyfilled1 = alreadyfilled;
  alreadyfilled1.pb(*it);
  for (int i = alreadyfilled1.size(); i < av.size(); i++) {
    alreadyfilled1.pb(*digits.begin());  //min digit
  }
  long overshoot_val = vectonum(alreadyfilled1);

  // try correctshooting it
  long correctshoot_val = -1;
  if (digits.count(av[alreadyfilled.size()])) {
    vector<int> alreadyfilled2 = alreadyfilled;
    alreadyfilled2.pb(av[alreadyfilled.size()]);
    correctshoot_val = afill(a, av, alreadyfilled2, digits);
  }


  long better = min(overshoot_val, correctshoot_val);
  long worse = max(overshoot_val, correctshoot_val);
  if (better >= a) {
    return better;
  } else {
    return worse;
  }
}


long belowfill(long a, const vector<int>& av, vector<int>& alreadyfilled, const set<int>& digits) {
  if (alreadyfilled.size() == av.size()) {
    return vectonum(alreadyfilled);
  }
  // try under current digit
  auto it = digits.lower_bound(av[alreadyfilled.size()]);
  if (it != digits.begin())  it = prev(it);
  vector<int> alreadyfilled1 = alreadyfilled;
  alreadyfilled1.pb(*it);
  for (int i = alreadyfilled1.size(); i < av.size(); i++) {
    alreadyfilled1.pb(*digits.rbegin());  //max digit
  }
  long overshoot_val = vectonum(alreadyfilled1);

  // try correctshooting it
  long correctshoot_val = LONG(5e18);
  if (digits.count(av[alreadyfilled.size()])) {
    vector<int> alreadyfilled2 = alreadyfilled;
    alreadyfilled2.pb(av[alreadyfilled.size()]);
    correctshoot_val = belowfill(a, av, alreadyfilled2, digits);
  }


  long better = max(overshoot_val, correctshoot_val);
  long worse = min(overshoot_val, correctshoot_val);
  if (better <= a) {
    return better;
  } else {
    return worse;
  }
}


void solve() {
  long a; int n;
  cin >> a >> n;
  set<int> digits;
  for (int i = 0; i < n; i++) {
    int d; cin >> d;
    digits.insert(d);
  }
  if (digits.size() == 1 && *digits.begin() == 0) {
    cout << a << "\n";
    return;
  }
  if (a == 0) {
    cout << *digits.begin() << "\n";
    return;
  }
  int max_digit = *digits.rbegin();
  int min_digit = *digits.begin();
  int min_digit_nonzero = min_digit == 0 ? *next(digits.begin()) : min_digit;

  long a1 = a;
  vector<int> av;
  while (a1 > 0) {
    av.pb(a1 % 10);
    a1 /= 10;
  }
  reverse(av.begin(), av.end());

  PRINTVEC(av);

  int av_digits = av.size();
  long max_number_same_digits = max_digit;
  for (int i = 1; i < av_digits; i++) {
    max_number_same_digits = max_number_same_digits * 10 + max_digit;
  }
  fprintf(stderr, "max_number_same_digits: %lld\n", max_number_same_digits);

  long above = 0;
  if (max_number_same_digits < a) {
    above = min_digit_nonzero;
    for (int i = 0; i < av_digits; i++) {
      above = above * 10 + min_digit;
    }
  } else {
    vector<int> v = vector<int>();
    above = afill(a, av, v, digits);
  }
  assert(above >= a);
  fprintf(stderr, "above: %lld\n", above);

  vector<int> v1 = vector<int>();
  long below = belowfill(a, av, v1, digits);
  if (below > a) {
    // go down a digit
    below = 0;
    for (int i = 0; i < av_digits - 1; i++) {
      below = below * 10 + max_digit;
    }
  }
  if (below == 0 && digits.count(0) == 0) {
    below = LONG(2e18);
  }
  fprintf(stderr, "below: %lld\n", below);

  long ans = min(abs(a-below), abs(a-above));
  cout << ans << "\n";

}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  cin >> t;
  while (t--)  solve();
  return 0;
}

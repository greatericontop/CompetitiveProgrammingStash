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
#define FORI(x) for (int i = 0; i < (x); i++)
using pairii = pair<int, int>;
using pairll = pair<long, long>;
using AdjList = vector<vector<int>>;
// Positive numbers only
constexpr static inline int ceildiv(int a, int b) { return (a + b - 1) / b; }
constexpr static inline long ceildivl(long a, long b) { return (a + b - 1) / b; }









// O(n)
string trim(const string& s) {
  int i = 0;
  while (i < s.size() && s[i] == '0')  i++;
  return s.substr(i);
}

// O(n)
string combine_or(const string& s1, const string& s2) {
  if (s1.size() > s2.size())  return combine_or(s2, s1);
  string result;
  int diff = s2.size() - s1.size();
  for (int i = 0; i < diff; i++) {
    result += s2[i];
  }
  for (int i = 0; i < s1.size(); i++) {
    if (s1[i] == '1' || s2[i+diff] == '1')  result += '1';
    else  result += '0';
  }
  return result;
}

// O(n)
bool lessthan(const string& s1, const string& s2) {
  assert(s1.front() == '1' && s2.front() == '1');
  if (s1.size() > s2.size())  return false;
  if (s1.size() < s2.size())  return true;
  for (int i = 0; i < s1.size(); i++) {
    if (s1[i] < s2[i])  return true;
    if (s1[i] > s2[i])  return false;
  }
  return false;
}

void solve() {
  int n;
  cin >> n;
  string s;
  cin >> s;
  s = trim(s);
  if (s.empty()) {
    cout << "0\n";
    return;
  }

  string s1 = s;
  int num_ones = 0;
  while (num_ones < s.size() && s[num_ones] == '1')  num_ones++;
  assert(num_ones <= 80);  //if the data is actually random, this should never happen
  fprintf(stderr, "s=%s, num ones %d\n", s.c_str(), num_ones);

  string best_result = s;
  for (int shift = 0; shift <= num_ones; shift++) {
    string result = combine_or(s1, s);
    fprintf(stderr, "%s OR %s = %s\n", s1.c_str(), s.c_str(), result.c_str());

    if (lessthan(best_result, result))  best_result = result;

    // delete the last char, shift 1 = 1st last char is missing
    s.pop_back();
  }

  cout << best_result << "\n";
}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  //cin >> t;
  while (t--)  solve();
  return 0;
}

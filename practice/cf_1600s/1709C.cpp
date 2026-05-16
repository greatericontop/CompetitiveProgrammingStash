#include <bits/stdc++.h>
using namespace std;
#define long long long


#define GREATERIC_DEBUG
//#define STRESSTESTING


#ifdef GREATERIC_DEBUG
  #define PRINTVEC(vec) do { \
    fprintf(stderr, "%s:  ", #vec); \
    for (const auto& _x : (vec))  fprintf(stderr, "%d ", _x); \
    fprintf(stderr, "\n"); \
  } while (0)
  #define PRINTMAP(map) do { \
    fprintf(stderr, "%s:  ", #map); \
    for (const auto& _p : (map))  fprintf(stderr, "%d->%d ", _p.first, _p.second); \
    fprintf(stderr, "\n"); \
  } while (0)
  #define DEBUGFOREACH(vec, stmt) do { \
    fprintf(stderr, "%s:  ", #vec); \
    for (const auto& x : (vec)) { \
      stmt; \
    } \
  } while (0)
  #pragma GCC diagnostic error "-Wall"
  #pragma GCC diagnostic error "-Wextra"
  #pragma GCC diagnostic error "-Wshadow"
  //#pragma GCC diagnostic error "-Wconversion"
  #pragma GCC diagnostic error "-Wfloat-equal"
  #pragma GCC diagnostic error "-Wduplicated-cond"
  #pragma GCC diagnostic error "-Wlogical-op"
#else
  #define fprintf(...) // no-op
  #define PRINTVEC(...) // no-op
  #define PRINTMAP(...) // no-op
#endif










void solve(string s) {
  int n = (int) s.size();
  assert(n % 2 == 0);

  int count_l = 0;
  int count_r = 0;
  int count_q = 0;
  for (int i = 0; i < n; i++) {
    if (s[i] == '(')  count_l++;
    else if (s[i] == ')')  count_r++;
    else if (s[i] == '?')  count_q++;
    else  assert(false);
  }

  if (abs(count_l - count_r) == count_q) {
    // unique
    cout << "YES\n";
    return;
  }

  int first_left_free = -1;
  int balance = 0;
  for (int i = 0; i < n; i++) {
    assert(balance >= 0);
    if (s[i] == '(')  balance++;
    else if (s[i] == ')')  balance--;
    else if (s[i] == '?') {
      if (balance > 0) {
        first_left_free = i;
        break;
      } else {
        // Set to '('
        balance++;
      }
    }
  }

  int first_right_free = -1;
  balance = 0;
  for (int i = n-1; i >= 0; i--) {
    assert(balance >= 0);
    if (s[i] == ')')  balance++;
    else if (s[i] == '(')  balance--;
    else if (s[i] == '?') {
      if (balance > 0) {
        first_right_free = i;
        break;
      } else {
        balance++;
      }
    }
  }

  if (first_left_free == -1 || first_right_free == -1 || first_left_free >= first_right_free) {
    cout << "YES\n";
  } else {
    cout << "NO\n";
  }




}










void stresstest(int run) {
  //mt19937_64 rng(run);
  mt19937_64 rng((uint64_t)chrono::steady_clock::now().time_since_epoch().count() + run);
  int n = 60;
  string ans;
  for (int i = 0; i < n; i++) {
    int r = rng() % 2;
    if (r == 0)  ans += '(';
    else  ans += ')';
  }
  int balance = 0;
  for (int i = 0; i < n; i++) {
    if (ans[i] == '(')  balance++;
    else  balance--;
    if (balance < 0) {
      return; // skip
    }
  }
  if (balance != 0) {
    return;
  }
  string given = ans;
  int i = rng() % n;
  int j = rng() % n;
  if (i == j)  return;
  if (given[i] == '(')  given[i] = ')';
  else  given[i] = '(';
  if (given[j] == '(')  given[j] = ')';
  else  given[j] = '(';

  balance = 0;
  for (int x = 0; x < n; x++) {
    if (given[x] == '(')  balance++;
    else  balance--;
    if (balance < 0) {
      return; // skip
    }
  }
  if (balance != 0) {
    return;
  }

  given[i] = '?';
  given[j] = '?';

  fprintf(stderr, "Running a test with\n    ans=%s\n  given=%s\n", ans.c_str(), given.c_str());
  solve(given);
}


int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
#ifdef STRESSTESTING
  fprintf(stderr, "Starting stresstest\n");
  static constexpr int RUNS = 15000;
  for (int i = 0; i < RUNS; i++)  stresstest(i);
  fprintf(stderr, "completed %d runs\n", RUNS);
#else
  int t;
  cin >> t;
  while (t--) {
    string s;
    cin >> s;
    solve(s);
  }
#endif
  return 0;
}

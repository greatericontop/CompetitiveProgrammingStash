#include <bits/stdc++.h>
using namespace std;
#define long long long


//#define GREATERIC_DEBUG


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
#else
  #define fprintf(...) // no-op
  #define PRINTVEC(...) // no-op
  #define PRINTMAP(...) // no-op
#endif










void solve() {
  int n, l, r;
  cin >> n >> l >> r;
  vector<int> a_raw(n);
  for (int i = 0; i < n; i++)  cin >> a_raw[i];
  sort(a_raw.begin(), a_raw.end());

  long l_score = 0, r_score = 0;
  int l_taken = 0, r_taken = 0;  //l_taken is you win more if you pick left
  vector<int> a;
  for (int i = 0; i < n; i++) {
    if (a_raw[i] <= l) {
      r_taken++;
      l_score += l-a_raw[i];
      r_score += r-a_raw[i];
    } else if (a_raw[i] >= r) {
      l_taken++;
      l_score += a_raw[i]-l;
      r_score += a_raw[i]-r;
    } else {
      a.push_back(a_raw[i]);
    }
  }
  fprintf(stderr, "After free picks:\n");
  fprintf(stderr, "l_taken=%d, r_taken=%d, l_score=%lld, r_score=%lld\n", l_taken, r_taken, l_score, r_score);
  PRINTVEC(a);

  int i = 0, j = a.size()-1;
  if (l_taken < r_taken) {
    // take :ct: more l's, from the end
    int ct = min(r_taken-l_taken, (int)a.size());
    for (; j >= (int)a.size()-ct; j--) {
      l_score += a[j]-l;
      r_score += a[j]-r;
    }
  } else {
    int ct = min(l_taken-r_taken, (int)a.size());
    for (; i < ct; i++) {
      l_score += l-a[i];
      r_score += r-a[i];
    }
  }
  fprintf(stderr, "i=%d, j=%d, l_score=%lld, r_score=%lld\n", i, j, l_score, r_score);
  assert(i == a.size() || j == -1 || l_score == r_score);

  long best = min(l_score, r_score);
  while (i < j) {
    l_score += l-a[i] + a[j]-l;
    r_score += r-a[i] + a[j]-r;
    best = max(best, min(l_score, r_score));
    i++; j--;
  }

  cout << best << "\n";
}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--)  solve();
  return 0;
}

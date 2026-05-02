#include <bits/stdc++.h>
using namespace std;
#define long long long


//#define GREATERIC_DEBUG


#ifdef GREATERIC_DEBUG
  #define PRINTVEC(vec) do { \
    fprintf(stderr, "%s:  ", #vec); \
    for (const auto& _x : (vec))  fprintf(stderr, "%lld, ", _x); \
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
  int n, m;
  cin >> n >> m;
  vector<long> A(n+m+1);
  vector<long> B(n+m+1);
  for (int i = 0; i < n+m+1; i++)  cin >> A[i];
  for (int i = 0; i < n+m+1; i++)  cin >> B[i];

  vector<bool> prefer_a(n+m+1, false);
  vector<int> prefer_a_prefix(n+m+1, 0);
  vector<bool> prefer_b(n+m+1, false);
  vector<int> prefer_b_prefix(n+m+1, 0);
  for (int i = 0; i < n+m+1; i++) {
    if (A[i] > B[i]) {
      prefer_a[i] = true;
    } else {
      prefer_b[i] = true;
    }
    if (i >= 1) {
      prefer_a_prefix[i] = prefer_a_prefix[i-1] + prefer_a[i];
      prefer_b_prefix[i] = prefer_b_prefix[i-1] + prefer_b[i];
    } else {
      prefer_a_prefix[i] = prefer_a[i];
      prefer_b_prefix[i] = prefer_b[i];
    }
  }
  if (prefer_a_prefix[n+m] <= n) {
    // If #A <= n, A is not the bottleneck
    swap(n, m);
    swap(A, B);
    swap(prefer_a, prefer_b);
    swap(prefer_a_prefix, prefer_b_prefix);
  }
  vector<long> prefix_sum_a(n+m+1, 0);
  vector<long> prefix_sum_b(n+m+1, 0);
  vector<long> prefix_sum_prefer_a(n+m+1, 0);
  vector<long> prefix_sum_prefer_b(n+m+1, 0);
  for (int i = 0; i < n+m+1; i++) {
    if (i >= 1) {
      prefix_sum_a[i] = prefix_sum_a[i - 1] + A[i];
      prefix_sum_b[i] = prefix_sum_b[i - 1] + B[i];
      prefix_sum_prefer_a[i] = prefix_sum_prefer_a[i - 1] + (prefer_a[i] ? A[i] : 0);
      prefix_sum_prefer_b[i] = prefix_sum_prefer_b[i - 1] + (prefer_b[i] ? B[i] : 0);
    } else {
      prefix_sum_a[i] = A[i];
      prefix_sum_b[i] = B[i];
      prefix_sum_prefer_a[i] = prefer_a[i] ? A[i] : 0;
      prefix_sum_prefer_b[i] = prefer_b[i] ? B[i] : 0;
    }
  }
  PRINTVEC(prefix_sum_a);
  PRINTVEC(prefix_sum_b);


  for (int exclude = 0; exclude < n+m+1; exclude++) {
    fprintf(stderr, "exclude %d\n", exclude);
    if (n == 0) {
      long score = prefix_sum_b[n+m];
      score -= B[exclude];
      cout << score << " ";
      continue;
    }
    // Bin search for first index i s.t. (# of prefer A in 0...i) == n
    int l = 0, h = n + m;
    while (l < h) {
      int mid = l + (h - l) / 2;
      int ct = prefer_a_prefix[mid];
      if (exclude <= mid && prefer_a[exclude]) ct--;
      if (ct >= n) {
        h = mid;
      } else {
        l = mid + 1;
      }
    }
    fprintf(stderr, "  cutoff index %d\n", l);
    // 0...l: add prefer A, prefer B
    long score = 0;
    score += prefix_sum_prefer_a[l];
    score += prefix_sum_prefer_b[l];
    if (exclude <= l) {
      if (prefer_a[exclude])  score -= A[exclude];
      else  score -= B[exclude];
    }
    fprintf(stderr, "  score from first half: %lld\n", score);
    // l+1...end: add B
    score += prefix_sum_b[n+m] - prefix_sum_b[l];
    if (exclude > l) {
      score -= B[exclude];
    }
    cout << score << " ";
  }
  cout << "\n";


}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--)  solve();
  return 0;
}

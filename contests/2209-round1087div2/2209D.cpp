#include <bits/stdc++.h>
using namespace std;
#define long long long

#define fprintf(...) // no-op





void solve() {
  int r1, g1, b1;
  cin >> r1 >> g1 >> b1;

  char majchar, midchar, minchar;
  int maj, mid, min;
  majchar = 'R';
  maj = r1;
  midchar = 'G';
  mid = g1;
  minchar = 'B';
  min = b1;
  if (mid > maj) {
    swap(majchar, midchar);
    swap(maj, mid);
  }
  if (min > mid) {
    swap(midchar, minchar);
    swap(mid, min);
  }
  if (mid > maj) {
    swap(majchar, midchar);
    swap(maj, mid);
  }

  fprintf(stderr, "%c %d  %c %d  %c %d\n", majchar, maj, midchar, mid, minchar, min);

  // Triangle ineq
  if (maj > mid + min + 1) {
    maj = mid + min + 1;
  }

  string ans;

  // BBBBBBBBBBBBBB  BGBGBGBG
  int b_block = mid - min;
  // maj >= mid - min
  // So first construct BRBRBRBRBR
  for (int i = 0; i < b_block; i++) {
    ans += midchar;
    ans += majchar;
  }
  maj -= b_block;
  mid -= b_block;
  assert(mid == min);

  fprintf(stderr, "b_block: %s\n", ans.c_str());
  fprintf(stderr, "%c %d  %c %d  %c %d\n", majchar, maj, midchar, mid, minchar, min);

  // BG BG BG
  // GRBR BG BG
  bool extra_r_at_start = false;
  if (maj % 2 == 1) {
    extra_r_at_start = true;
    maj--;
  } // now maj is even

  int group_blocks_total = mid;
  int group_blocks_r = maj / 2;
  int group_blocks_plain = group_blocks_total - group_blocks_r;

  for (int i = 0; i < group_blocks_r; i++) {
    ans += minchar;
    ans += majchar;
    ans += midchar;
    ans += majchar;
  }
  for (int i = 0; i < group_blocks_plain; i++) {
    ans += midchar;
    ans += minchar;
  }

  if (extra_r_at_start) {
    ans = majchar + ans;
  }

  cout << ans << "\n";

}





int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--)  solve();
  return 0;
}
#include <bits/stdc++.h>
using namespace std;
#define int long long

const int N = 200;
const long long LLINF = 1e18 + 3;

int n, m;
int a[N][N];
int threshold[N];
vector<int> nen;

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      cin >> a[i][j];
      if (a[i][j] != -1) nen.push_back(a[i][j]);
    }
  }
  sort(nen.begin(), nen.end());
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (a[i][j] != -1) a[i][j] = lower_bound(nen.begin(), nen.end(), a[i][j]) - nen.begin() + 1;
    }
  }

  int ans = LLINF;

  int cur = 0;
  int idx = 0;
  for (int sum = 2; sum <= n+m; sum++) {
    ++idx;
    threshold[idx] = 0;
    for (int i = 1; i <= n; i++) {
      int j = sum - i;
      if (j > m) continue;
      if (j == 0) break;
      if (a[i][j] != -1) threshold[idx] += 1;
    }
    threshold[idx] += threshold[idx - 1];
    for (int i = 1; i <= n; i++) {
      int j = sum - i;
      if (j > m) continue;
      if (j == 0) break;
      if (a[i][j] == -1) continue;
      if (a[i][j] > threshold[idx - 1] && a[i][j] <= threshold[idx]) {
      }
      else cur += 1;
    }
  }
  // for (int i=1; i<=n; i++) {
  //   for (int j=1; j<=m; j++) {
  //     cout << a[i][j] << " ";
  //   }
  //   cout << endl;
  // }
  //
  // for (int i=1; i<=n+m; i++) {
  //   cout << threshold[i] << " ";
  // }
  // cout << endl;
  // cout << cur << endl;
  ans = min(ans,cur);

  cur = 0;
  idx = 0;
  for (int sub=n-1; sub>=1-m; sub--) {
    ++idx;
    threshold[idx] = 0;
    for (int i=1; i<=n; i++) {
      int j = i-sub;
      if (j <=0) continue;
      if (j >m) break;
      if (a[i][j] != -1) threshold[idx] += 1;
    }
    threshold[idx] += threshold[idx-1];
    for (int i=1; i<=n; i++) {
      int j = i-sub;
      if (j <=0) continue;
      if (j > m) break;
      // cout << i << " " << j << " " << a[i][j] << " " << threshold[idx];
      if (a[i][j] == -1) continue;
      if (a[i][j] > threshold[idx-1] && a[i][j] <= threshold[idx]) {
      }
      else cur +=1;
    }
  }
  // for (int i=1; i<=n+m; i++) {
  //   cout << threshold[i] << " ";
  // }
  // cout << endl;
  // cout << cur << endl;
  ans = min(ans,cur);

  for (int i=1; i<=n; i++) {
    for (int j=1; j<=m/2; j++) {
      swap(a[i][j], a[i][m-j+1]);
    }
  }

  cur = 0;
  idx = 0;
  for (int sum = 2; sum <= n+m; sum++) {
    ++idx;
    threshold[idx] = 0;
    for (int i = 1; i <= n; i++) {
      int j = sum - i;
      if (j > m) continue;
      if (j == 0) break;
      if (a[i][j] != -1) threshold[idx] += 1;
    }
    threshold[idx] += threshold[idx - 1];
    for (int i = 1; i <= n; i++) {
      int j = sum - i;
      if (j > m) continue;
      if (j == 0) break;
      if (a[i][j] == -1) continue;
      if (a[i][j] > threshold[idx - 1] && a[i][j] <= threshold[idx]) {
      }
      else cur += 1;
    }
  }
  // for (int i=1; i<=n+m; i++) {
  //   cout << threshold[i] << " ";
  // }
  // cout << endl;
  // cout << cur << endl;
  ans = min(ans,cur);

  cur = 0;
  idx = 0;
  for (int sub=n-1; sub>=1-m; sub--) {
    ++idx;
    threshold[idx] = 0;
    for (int i=1; i<=n; i++) {
      int j = i-sub;
      if (j <=0) continue;
      if (j >m) break;
      if (a[i][j] != -1) threshold[idx] += 1;
    }
    threshold[idx] += threshold[idx-1];
    for (int i=1; i<=n; i++) {
      int j = i-sub;
      if (j <=0) continue;
      if (j > m) break;
      if (a[i][j] == -1) continue;
      if (a[i][j] > threshold[idx-1] && a[i][j] <= threshold[idx]) {
      }
      else cur +=1;
    }
  }
  // for (int i=1; i<=n+m; i++) {
  //   cout << threshold[i] << " ";
  // }
  // cout << endl;
  // cout << cur << endl;
  ans = min(ans,cur);
  cout << ans << endl;
}

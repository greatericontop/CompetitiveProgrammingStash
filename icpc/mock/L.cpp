#include <bits/stdc++.h>
using namespace std;
#define int long long

const int N = 100;
const long long LLINF = 1e18+3;

int n, m;
int a[N][N];

void dfs(int u) {
  if (!vis[u]) sum += a[u];
  if (!vis[u] && deg[u] == 0) {
    ans = min(ans,sum);
  }

  for (auto v:adj[u]) {
    dfs(v);
  }

  if (!vis[u]) sum -= a[u];
}

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  cin >> n >> m;
  for (int i=1; i<=n; i++) {
    for (int j=1; j<=m; j++) {
      cin >> a[i][j];
    }
  }

  for (int sum=2; sum<=n; sum++) {
    for (int i=1; i<=n; i++) {
      int j = sum - i;
      if ()
    }
  }

  cout << ans << endl;
}
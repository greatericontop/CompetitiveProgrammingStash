#include <bits/stdc++.h>
using namespace std;
#define int long long

const int N = 2e5;
const long long LLINF = 1e18+3;

int n, m;
int a[N];
vector<int> adj[N];
int parent[N];
int deg[N];
int vis[N];
int ans = LLINF;
int sum = 0;

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
    cin >> a[i];
  }
  for (int i=1; i<=m; i++) {
    int u,v; cin >> u >> v;
    adj[u].push_back(v);
    parent[v] = u;
    deg[u]++;
  }

  parent[0] = -1;
  vis[0] = true;
  for (int i=1; i<=n; i++) {
    if (parent[i] == 0) {
      adj[0].push_back(i);
    }
  }

  for (int i=1; i<=n; i++) {
    if (deg[i] == 0) {
      int cur = i;
      while (cur!=0) {
        vis[cur] = true;
        sum += a[cur];
        cur = parent[cur];
      }

      dfs(0);

      cur = i;
      while (cur!=0) {
        vis[cur] = false;
        sum -= a[cur];
        cur = parent[cur];
      }
    }
  }

  cout << ans << endl;
}
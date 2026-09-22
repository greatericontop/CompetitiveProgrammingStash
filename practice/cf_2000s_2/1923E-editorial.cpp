#include <bits/stdc++.h>

#define forn(i, n) for (int i = 0; i < int(n); i++)

using namespace std;

int n;
vector<int> a;
vector<vector<int>> g;

long long ans;
vector<map<int, int>> cnt;

void dfs(int v, int p = -1){
  int bst = -1;
  for (int u : g[v]) if (u != p){
    dfs(u, v);
    if (bst == -1 || cnt[bst].size() < cnt[u].size())
      bst = u;
  }
  for (int u : g[v]) if (u != p && u != bst){
    for (auto it : cnt[u]){
      int x = it.first, y = it.second;
      if (x != a[v]) ans += cnt[bst][x] * 1ll * y;
      cnt[bst][x] += y;
    }
  }
  if (bst != -1) swap(cnt[bst], cnt[v]);
  ans += cnt[v][a[v]];
  cnt[v][a[v]] = 1;
}

int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);
  int t;
  cin >> t;
  while (t--){
    int n;
    cin >> n;
    a.resize(n);
    forn(i, n) cin >> a[i];
    g.assign(n, {});
    forn(_, n - 1){
      int v, u;
      cin >> v >> u;
      --v, --u;
      g[v].push_back(u);
      g[u].push_back(v);
    }
    ans = 0;
    cnt.assign(n, {});
    dfs(0);
    cout << ans << '\n';
  }
  return 0;
}
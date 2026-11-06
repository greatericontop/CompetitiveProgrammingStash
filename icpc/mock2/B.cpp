#include <bits/stdc++.h>
#define int long long
using namespace std;

const int maxn = 2e5+100;
int a[maxn];
int n, k;
int sum[maxn];
int ans = 0;
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> k;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];

  }
  sort(a + 1, a + n + 1);
  for (int i = 1; i <= n; i++) {

    sum[i%k]+=a[i];
    ans += sum[i%k];
  }
  cout << ans << endl;
}
#include <bits/stdc++.h>
using namespace std;

#define pii pair<int,int>
#define int long long

const int N = 2e5+10;
const int INF = 1e9+10;

int a[N];
int u[N], v[N], s[N], e[N];
int n,t;
struct Item {
  int time;
  int type;
  int idx, val;

  Item (int a, int b, int c, int d) {
    time = a;
    type = b;
    idx = c;
    val = d;
  }

  bool operator <(Item& other) const {
    if (time == other.time) {
      return type > other.type;
    }
    return time > other.time;
  }
  // bool operator >(Item& other) {
  //   if (time == other.time) {
  //     return type > other.type;
  //   }
  //   return time > other.time;
  // }
};

signed main() {
  cin >> n >> t;
  a[1] = 0;
  for (int i=2; i<=n; i++) {
    a[i] = INF;
  }

  priority_queue<pair<pii,pii>, vector<pair<pii,pii>>, greater<pair<pii,pii>>> pq;

  int ans = INF;
  for (int i=1; i<=t; i++) {
    cin >> u[i] >> v[i] >> s[i] >> e[i];
    pq.push({{s[i], 1}, {u[i], i}});
  }
  while (!pq.empty()) {
    auto info = pq.top();
    pq.pop();
    int type = info.first.second;
    int time = info.first.first;
    int pos = info.second.first;
    int val = info.second.second;


    if (type == 0) {
      a[pos] = min(a[pos],val);
      if (pos == n) {
        ans = min(ans, val + time);
      }
    }
    else {
      int qidx = val;
      int val = a[pos];
      pq.push({{e[qidx], 0},{v[qidx], val - (e[qidx] - s[qidx])}});
    }
  }

  if (ans >= INF) {
    cout << -1 << endl;
  }
  else {
    cout << ans << endl;
  }
}
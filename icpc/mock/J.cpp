#include <bits/stdc++.h>
using namespace std;
#define int long long

const int maxn = 1e5 + 5;
int l[maxn], r[maxn], a[maxn];

signed main() {
 ios::sync_with_stdio(0);
 cin.tie(0);
 cout.tie(0);

 int n;
 cin >> n;
 for (int i = 1; i <=n; i++) cin>>a[i];
 stack<int> s;
 for (int i = 1; i <=n; i++) {

   while (!s.empty() && a[s.top()] >= a[i]) s.pop();
   if (s.empty())
    l[i] = 0;
   else l[i] = s.top();
   s.push(i);
  // cout << l[i] << ' ';
 }
  cout << endl;
  while (!s.empty()) s.pop();
  for (int i = n; i >= 1; i--) {
    while (!s.empty() && a[s.top()] >= a[i]) s.pop();
    if (s.empty()) r[i] = n + 1;
    else r[i] = s.top();
    s.push(i);

 // cout << r[i] << ' ';
  }
  cout << endl;
  int st = INT_MAX, e = INT_MAX;
  int ans = 0;
  for (int i = 1; i <=n; i++) {
    int sum = (r[i] - l[i]-1) * a[i];
    if (ans <= sum) {
      if (ans < sum) {
        st = l[i] + 1, e= r[i] - 1;
        ans = sum;
      } else if (l[i] + 1< st) st = l[i] + 1, e= r[i] - 1;
    }
  }
  cout << st << " " << e << " "<<ans<< endl;
}
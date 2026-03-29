#include <bits/stdc++.h>
using namespace std;
#define long long long

#define fprintf(...) // no-op





long lcm(int a, int b) {
  return ((long)a) * ((long)b) / ((long)gcd(a, b));
}

void solve() {
  int n;
  cin >> n;
  vector<int> A(n);
  vector<int> B(n);
  for (int i = 0; i < n; i++)  cin >> A[i];
  for (int i = 0; i < n; i++)  cin >> B[i];

  int ct = 0;
  for (int i = 1; i < n-1; i++) {
    int a = gcd(A[i-1], A[i]);
    int b = gcd(A[i], A[i+1]);
    long x = lcm(a, b);
    if (x < A[i]) {
      ct++;
    }
  }
  // edges
  if (gcd(A[0], A[1]) < A[0])  ct++;
  if (gcd(A[n-2], A[n-1]) < A[n-1])  ct++;

  cout << ct << "\n";
}





int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--)  solve();
  return 0;
}
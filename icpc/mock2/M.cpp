#include <bits/stdc++.h>
using namespace std;
#define long int64_t



bool xor_basis_push(set<int, greater<int>>& xor_basis, int val) {
  for (int existing_val : xor_basis) {
    if ((val ^ existing_val) < val)  val ^= existing_val;
  }
  if (val == 0)  return false;
  xor_basis.insert(val);
  return true;
}


int main() {
  int n;  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; i++)  cin >> a[i];



  long nonsuitable = 0;
  for (int start = 0; start < n; start++) {
    set<int, greater<int>> xor_basis;
    int num_zeros = 0;

    // array from start to j inclusive
    for (int j = start; j < n; j++) {
      // push j
      bool ret = true;
      if (a[j] == 0)  num_zeros++;
      else  ret = xor_basis_push(xor_basis, a[j]);

      if (num_zeros >= 2 || !ret) {
        break;
      }
      nonsuitable++;
    }
  }

  long tot = ((long) n) * ((long) n+1) / 2;
  cout << tot - nonsuitable << "\n";




}

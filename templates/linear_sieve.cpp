#include <bits/stdc++.h>
using namespace std;





/*
 * Linear Sieve of Eratosthenes
 * Saves the results in :primes: and :spf:
 */
void linear_sieve(int n, vector<int>& primes, vector<int>& spf) {
  primes.clear();
  for (int i = 0; i < spf.size(); i++) {
    spf[i] = i;
  }

  for (int i = 2; i <= n; i++) {
    if (spf[i] == i) {
       primes.push_back(i);
    }

    for (int prime : primes) {
      if (prime > spf[i])  break;
      int composite_number = prime * i;
      if (composite_number > n)  break;
      spf[composite_number] = prime;
    }
  }
}





int main() {
  int n = 150;

  vector<int> primes;
  vector<int> spf(n+1);
  linear_sieve(n, primes, spf);

  for (int x = 1; x <= n; x++) {
    cout << "spf[" << x << "] = " << spf[x] << endl;
  }
  cout << "Primes:";
  for (int prime : primes) {
    cout << " " << prime;
  }
  cout << endl;
}

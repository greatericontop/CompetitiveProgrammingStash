#include <bits/stdc++.h>
using namespace std;
#define long long long

//#define fprintf(...) // no-op





vector<int> PRIMES;

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

  vector<vector<int>> problematic_segments;
  int count = 0;

  for (int i = 0; i < n; i++) {
    long x;
    if (i == 0) {
      x = gcd(A[0], A[1]);
    } else if (i == n-1) {
      x = gcd(A[n-1], A[n-2]);
    } else {
      x = lcm(gcd(A[i], A[i-1]), gcd(A[i], A[i+1]));
    }
    if (B[i] < x) {
      // can't adjust
      continue;
    }
    if (x == A[i]) {
      if (B[i] < 2*x) {
        continue;
      }
      if (problematic_segments.empty()) {
        problematic_segments.push_back({i});
      } else {
        if (problematic_segments.back().back() == i-1) {
          problematic_segments.back().push_back(i);
        } else {
          problematic_segments.push_back({i});
        }
      }

      count++;
    } else {
      count++;
    }
  }

  for (auto & segment : problematic_segments) {
    fprintf(stderr, "Segment from %d to %d\n", segment[0], segment.back());

    if (segment.size() == 1) {
      int i = segment[0];
      bool prime_works = false;
      for (int prime : PRIMES) {
        if (prime > B[i]/A[i])  break;
        if (i >= 1) {
          if (A[i-1] % prime == 0) {
            continue;
          }
        }
        if (i < n-1) {
          if (A[i+1] % prime == 0) {
            continue;
          }
        }
        prime_works = true;
        break;
      }
      if (prime_works) {
        fprintf(stderr, "  Singleton segment %d, found a prime that works\n", i);
      }
      fprintf(stderr, "  Singleton segment %d, found no prime that works\n", i);
      count--;
      continue;
    }

    map<int, int> max_multi;
    for (int i : segment) {
      max_multi[i] = B[i] / A[i];
    }
    // Front & back
    int front_highest_prime = -1;
    int back_highest_prime = -1;
    for (int prime : PRIMES) {
      if (prime > max_multi[segment[0]])  break;
      if (segment[0] >= 1) {
        if (A[segment[0]-1] % prime == 0) {
          continue;
        }
      }
      front_highest_prime = prime;
    }
    for (int prime : PRIMES) {
      if (prime > max_multi[segment.back()])  break;
      if (segment.back() < n-1) {
        if (A[segment.back()+1] % prime == 0) {
          continue;
        }
      }
      back_highest_prime = prime;
    }

    if (front_highest_prime == -1) {
      segment.erase(segment.begin());
    } else if (front_highest_prime == 2) {
      max_multi[segment[0]] = 2;
    } else if (front_highest_prime == 3) {
      max_multi[segment[0]] = 3;
      segment.insert(segment.begin(), segment[0]-1);
      max_multi[segment[0] - 1] = 2;
      count--;
    }
    if (back_highest_prime == -1) {
      segment.pop_back();
    } else if (back_highest_prime == 2) {
      max_multi[segment.back()] = 2;
    } else if (back_highest_prime == 3) {
      max_multi[segment.back()] = 3;
      segment.push_back(segment.back() + 1);
      max_multi[segment.back()] = 2;
      count--;
    }

    int loss = 0;

    int last_2;
    bool paid_for_prev = false;
    bool found_5 = false;
    for (int i : segment) {
      if (max_multi[i] == 2) {
        if ((!found_5) && (i - last_2) % 2 == 1) {
          if (paid_for_prev) {
            paid_for_prev = false;
          } else {
            loss++;
            paid_for_prev = true;
          }
          last_2 = i;
        } else {
          last_2 = i;
          found_5 = false;
        }
      }
      if (max_multi[i] >= 5) {
        found_5 = true;
      }
    }

    count -= loss;

  }





  cout << count << "\n";
}





int main() {
  PRIMES = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--)  solve();
  return 0;
}
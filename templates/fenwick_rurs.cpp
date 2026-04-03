#include <bits/stdc++.h>
using namespace std;





template <class T> class Fenwick {
private:
  int n;
  vector<T> data; // note: 1-indexed

public:
  explicit Fenwick(int n) : n(n), data(n+1) {
  }

  /* Initialize from an array of values[1...n] (it's 1-indexed!) */
  void init(vector<T> values) {
    vector<T> prefix_sums(n+1);
    prefix_sums[0] = 0;
    for (int i = 1; i <= n; i++) {
      prefix_sums[i] = prefix_sums[i-1] + values[i];
    }
    for (int i = 1; i <= n; i++) {
      data[i] = prefix_sums[i] - prefix_sums[i - (i & -i)];
    }
  }

  void add(int i, T value) {
    while (i <= n) {
      data[i] += value;
      i += i & -i;
    }
  }

  void set(int i, T value) {
    T current_value = prefix_sum(i) - prefix_sum(i-1);
    add(i, value - current_value);
  }

  /* Prefix sum from indices 1 to i inclusive */
  T prefix_sum(int i) {
    if (i == 0)  return 0;
    T sum = 0;
    while (i >= 1) {
      sum += data[i];
      i -= i & -i;
    }
    return sum;
  }

};


template <class T> class FenwickRURS {
private:
  int n;
  vector<T> prefix_sums;
  Fenwick<T> suffix_adds;
  Fenwick<T> suffix_subs;

public:
  explicit FenwickRURS(int n) : n(n), prefix_sums(n+1), suffix_adds(n), suffix_subs(n) {
  }

  void init(vector<T> values) {
    prefix_sums[0] = 0;
    for (int i = 1; i <= n; i++) {
      prefix_sums[i] = prefix_sums[i-1] + values[i];
    }
    suffix_adds.init(vector<T>(n+1, 0));
    suffix_subs.init(vector<T>(n+1, 0));
  }

  void suffix_add(int i, T value) {
    suffix_adds.add(i, (n-i+1)*value);
    suffix_subs.add(i, value);
  }

  /* Add value to [left, right] inclusive. */
  void range_add(int left, int right, T value) {
    suffix_add(left, value);
    if (right < n) {
      suffix_add(right+1, -value);
    }
  }

  /* 1 to i inclusive */
  T prefix_sum(int i) {
    return prefix_sums[i] + suffix_adds.prefix_sum(i) - (n-i)*suffix_subs.prefix_sum(i);
  }

  /* left to right inclusive */
  T range_sum(int left, int right) {
    return prefix_sum(right) - prefix_sum(left-1);
  }

};


void stresstest() {
  int n = 20000;
  FenwickRURS<int> fenwick(n);
  mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

  cout << "Stresstesting...\n";
  vector<int> A(n+1);
  for (int i = 1; i <= n; i++) {
    A[i] = rng() % 10000;
  }
  fenwick.init(A);
  for (int bundle = 0; bundle < 10; bundle++) {
    for (int test = 0; test < 100'000; test++) {
      int op = rng() % 2;
      if (op == 0) {
        int left = (rng() % n) + 1;
        int right = (rng() % n) + 1;
        if (left > right)  swap(left, right);
        int amount = (rng() % 20000) - 10000;
        fenwick.range_add(left, right, amount);
        for (int i = left; i <= right; i++) {
          A[i] += amount;
        }
      } else {
        int left = (rng() % n) + 1;
        int right = (rng() % n) + 1;
        if (left > right)  swap(left, right);
        int answer = 0;
        for (int i = left; i <= right; i++) {
          answer += A[i];
        }
        int fen_answer = fenwick.range_sum(left, right);
        if (answer != fen_answer) {
          fprintf(stderr, "Fenwick incorrect! expected %d, got %d\n", answer, fen_answer);
          exit(1);
        }
      }
    }
    printf("Bundle %d (100k tests) passed!\n", bundle+1);
  }
  cout << "Stresstest passed!\n";
}


int main() {
  stresstest();
}

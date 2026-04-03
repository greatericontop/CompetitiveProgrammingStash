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

  /* Range sum from left to right inclusive */
  T range_sum(int left, int right) {
    return prefix_sum(right) - prefix_sum(left-1);
  }

};


void stresstest() {
  int n = 20000;
  Fenwick<int> fenwick(n);
  mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

  cout << "Stresstesting...\n";
  vector<int> A(n+1);
  for (int i = 1; i <= n; i++) {
    A[i] = rng() % 10000;
  }
  fenwick.init(A);
  for (int bundle = 0; bundle < 10; bundle++) {
    for (int test = 0; test < 100'000; test++) {
      int op = rng() % 4;
      if (op == 0) {
        int i = (rng() % n) + 1;
        int new_value = rng() % 10000;
        A[i] = new_value;
        fenwick.set(i, new_value);
      } else if (op == 1) {
        int i = (rng() % n) + 1;
        int offset = (rng() % 20000) - 10000;
        A[i] += offset;
        fenwick.add(i, offset);
      } else {
        int left = (rng() % n) + 1;
        int right = (rng() % n) + 1;
        if (left > right)  swap(left, right);
        int answer = 0;
        for (int i = left; i <= right; i++) {
          answer += A[i];
        }
        int fen_answer = fenwick.range_sum(left, right);
        int fen_answer_2 = fenwick.prefix_sum(right) - fenwick.prefix_sum(left-1);
        assert(fen_answer == fen_answer_2);
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

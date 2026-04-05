#include <bits/stdc++.h>
using namespace std;






#define exp(x) (1 << (x))
template <class T> class LazySegmentTree {
private:
  int max_layer;
  int n;
  // segments[l] contains 0 to 2^l - 1
  vector<vector<T>> segments;
  // Tag is applied to the entire segment
  // segments[l][i] takes into account all tags STRICTLY below it (not its own tag)
  vector<vector<T>> tags;
  T zero;

public:
  explicit LazySegmentTree(int max_layer, T zero, const vector<T>&& initialize)
      : max_layer(max_layer), n(exp(max_layer)), segments(max_layer+1), tags(max_layer+1),
      zero(zero) {
    assert(max_layer <= 30);
    assert(initialize.size() <= n);
    segments[0] = initialize;
    while (segments[0].size() < n)  segments[0].push_back(zero);
    tags[0] = vector<T>(n, zero);
    for (int layer = 1; layer <= max_layer; layer++) {
      for (int i = 0; i < exp(max_layer-layer); i++) {
        segments[layer].push_back(segments[layer-1][2*i] + segments[layer-1][2*i+1]);
        tags[layer].push_back(zero);
      }
    }
  }

  /* Range update layer :layer: segment :i:, from :l: to :r: inclusive (relative to the segment) */
  void _range_update(int layer, int i, int l, int r, T amount) {
    if (layer == 0) {
      // Single element
      assert(l == 0 && r == 0);
      tags[layer][i] += amount;
      return;
    }
    int seg_size = exp(layer);
    int child_seg_size = exp(layer-1);
    assert(l >= 0 && r < seg_size);
    assert(l <= r);
    if (l == 0 && r == seg_size-1) {
      // Encompasses entire range, so just tag it
      tags[layer][i] += amount;
      return;
    }
    // Update subsegments
    if (l <= child_seg_size-1) {
      _range_update(layer-1, 2*i, l, min(r, child_seg_size-1), amount);
    }
    if (r >= child_seg_size) {
      _range_update(layer-1, 2*i+1, max(0, l-child_seg_size), r-child_seg_size, amount);
    }
    // Update self
    T new_sum = segments[layer-1][2*i] + child_seg_size*tags[layer-1][2*i]
        + segments[layer-1][2*i+1] + child_seg_size*tags[layer-1][2*i+1];
    segments[layer][i] = new_sum;
  }

  /*
   * Range sum layer :layer: segment :i:, from :l: to :r: inclusive (relative to the segment), with
   * :accumulator: being the sum of all tags from layers above (not including the current layer)
   */
  T _range_sum(int layer, int i, int l, int r, T accumulator) {
    T updated_accumulator = accumulator + tags[layer][i];
    if (layer == 0) {
      // Single element
      assert(l == 0 && r == 0);
      return segments[layer][i] + updated_accumulator;
    }
    int seg_size = exp(layer);
    int child_seg_size = exp(layer-1);
    assert(l >= 0 && r < seg_size);
    assert(l <= r);
    if (l == 0 && r == seg_size-1) {
      return segments[layer][i] + seg_size*updated_accumulator;
    }
    T ret = zero;
    if (l <= child_seg_size-1) {
      ret += _range_sum(layer-1, 2*i, l, min(r, child_seg_size-1), updated_accumulator);
    }
    if (r >= child_seg_size) {
      ret += _range_sum(layer-1, 2*i+1, max(0, l-child_seg_size), r-child_seg_size, updated_accumulator);
    }
    return ret;
  }

  void range_add(int l, int r, T amount) {
    _range_update(max_layer, 0, l, r, amount);
  }

  T range_sum(int l, int r) {
    return _range_sum(max_layer, 0, l, r, zero);
  }

};










void stresstest() {
  int n = 16300, max_layer = 14;
  int64_t seed = chrono::steady_clock::now().time_since_epoch().count();
  cout << "Seed: " << seed << "\n";
  mt19937 rng(seed);
  //mt19937 rng(42);

  cout << "Stresstesting...\n";
  vector<int> A(n+1);
  for (int i = 1; i <= n; i++) {
    A[i] = rng() % 10000;
  }
  LazySegmentTree<int> lst(max_layer, 0, vector<int>(A));
  for (int bundle = 0; bundle < 10; bundle++) {
    for (int test = 0; test < 100'000; test++) {
      int op = rng() % 2;
      if (op == 0) {
        int left = (rng() % n) + 1;
        int right = (rng() % n) + 1;
        if (left > right)  swap(left, right);
        int amount = (rng() % 20000) - 10000;
        lst.range_add(left, right, amount);
        for (int i = left; i <= right; i++) {
          A[i] += amount;
        }
        //fprintf(stderr, "#%d add %d...%d by %d\n", test, left, right, amount);
      } else {
        int left = (rng() % n) + 1;
        int right = (rng() % n) + 1;
        if (left > right)  swap(left, right);
        int answer = 0;
        for (int i = left; i <= right; i++) {
          answer += A[i];
        }
        int lst_answer = lst.range_sum(left, right);
        //fprintf(stderr, "#%d query %d...%d = expect %d got %d\n", test, left, right, answer, lst_answer);
        if (answer != lst_answer) {
          fprintf(stderr, "LST incorrect! expected %d, got %d (on #%d)\n", answer, lst_answer, test);
          exit(1);
        }
      }
    }
    printf("Bundle %d (100k tests) passed!\n", bundle+1);
  }
  cout << "Stresstest passed!\n";
}

int main() {
  int n = 16, layers = 4;
  vector<int> A(n);

  for (int i = 0; i < n; i++) {
    A[i] = 1;
  }
  LazySegmentTree<int> lst1(layers, 0, vector<int>(A));
  assert(lst1.range_sum(0, 15) == 16);
  assert(lst1.range_sum(1, 14) == 14);
  assert(lst1.range_sum(3, 10) == 8);
  lst1.range_add(0, 15, 1);
  assert(lst1.range_sum(0, 15) == 32);
  assert(lst1.range_sum(1, 14) == 28);
  lst1.range_add(0, 5, -2);
  assert(lst1.range_sum(0, 5) == 0);
  assert(lst1.range_sum(1, 6) == 2);
  cout << "Manual test 1 passed!\n";

  n = 16, layers = 4;
  for (int i = 0; i < n; i++) {
    A[i] = 0;
  }
  LazySegmentTree<int> lst2(layers, 0, vector<int>(A));
  lst2.range_add(9, 14, -20);
  assert(lst2.range_sum(14, 15) == -20);
  cout << "Manual test 2 passed!\n";

  stresstest();
}

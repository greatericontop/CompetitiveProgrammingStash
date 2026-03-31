#include <bits/stdc++.h>
using namespace std;
#define long long long

//#define fprintf(...) // no-op





/*
 * Segment tree skeleton. Fill stuff in where appropriate.
 * Handwritten by me (might be slightly slow).
 */
#define exp(x) (1 << (x))
template <class T, class Combiner> class SegmentTree {
private:
  int max_layer;
  int n;
  vector<vector<T>> segments; // segments[l] contains 0 to 2^l - 1
  Combiner combiner;
  T combine_empty; // the identity/null element (e.g. 0 for sum, INT_MAX for min, etc.)

public:
  explicit SegmentTree(int max_layer, Combiner combiner, T combine_empty, const vector<T>&& initialize)
      : max_layer(max_layer), n(exp(max_layer)), segments(max_layer + 1),
      combiner(combiner), combine_empty(combine_empty) {
    assert(initialize.size() <= n);
    segments[0] = initialize;
    while (segments[0].size() < n)  segments[0].push_back(combine_empty);

    for (int layer = 1; layer <= max_layer; layer++) {
      for (int i = 0; i < exp(max_layer-layer); i++) {
        segments[layer].push_back(combiner(segments[layer-1][2*i], segments[layer-1][2*i+1]));
      }
    }
  }

  void point_update(int i, T new_value) {
    segments[0][i] = new_value;
    for (int layer = 1; layer <= max_layer; layer++) {
      i /= 2;
      segments[layer][i] = combiner(segments[layer-1][2*i], segments[layer-1][2*i+1]);
    }
  }

  /* Range query left to right inclusive, 0-indexed */
  T range_query(int left, int right) {
    T answer = combine_empty;
    while (left <= right) {
      // Find biggest interval (aka what's the biggest power of 2 that divides a)
      int layer_i = left;
      int layer = 0;
      while ((left % (2 << layer) == 0) && (layer < 18) && (left + (2 << layer) - 1 <= right)) {
        layer++;
        layer_i /= 2;
      }
      answer = combiner(answer, segments[layer][layer_i]);
      left += exp(layer);
    }
    return answer;
  }
};





void solve() {
  int n;
  cin >> n;
  vector<int> even, odd;
  for (int i = 1; i <= n; i++) {
    int x;
    cin >> x;
    if (i % 2 == 0) {
      even.push_back(x);
    } else {
      odd.push_back(x);
    }
  }
  fprintf(stderr, "odd: "); for (int i = 0; i < odd.size(); i++) fprintf(stderr, "%d ", odd[i]); fprintf(stderr, "\n");

  auto add_combiner = [](int a, int b) { return a + b; };
  long even_invs = 0;
  int layers = 0;
  while (exp(layers) < n+10)  layers++;
  SegmentTree<int, decltype(add_combiner)> even_segtree(layers, add_combiner, 0, vector<int>(n+1, 0));
  for (int i = 0; i < even.size(); i++) {
    assert(even_segtree.range_query(even[i], even[i]) == 0);
    even_invs += even_segtree.range_query(even[i]+1, n);
    even_segtree.point_update(even[i], 1);
  }
  long odd_invs = 0;
  SegmentTree<int, decltype(add_combiner)> odd_segtree(layers, add_combiner, 0, vector<int>(n+1, 0));
  for (int i = 0; i < odd.size(); i++) {
    assert(odd_segtree.range_query(odd[i], odd[i]) == 0);
    odd_invs += odd_segtree.range_query(odd[i]+1, n);
    odd_segtree.point_update(odd[i], 1);
  }

  even_invs %= 2; odd_invs %= 2;
  sort(even.begin(), even.end());
  sort(odd.begin(), odd.end());
  if (even_invs != odd_invs) {
    if (n % 2 == 0) {
      // Even length array: swap last 2 in even
      swap(even[even.size()-1], even[even.size()-2]);
    } else {
      // Odd length array: swap last 2 in odd
      swap(odd[odd.size()-1], odd[odd.size()-2]);
    }
  }

  for (int i = 1; i <= n; i++) {
    if (i % 2 == 1) {
      cout << odd[i/2] << " ";
    } else {
      cout << even[i/2-1] << " ";
    }
  }
  cout << "\n";

}





int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--)  solve();
  return 0;
}




#include <bits/stdc++.h>
using namespace std;





/*
 * Segment tree skeleton. Fill stuff in where appropriate.
 * Handwritten by me (might be slightly slow).
 */
#define exp(x) (1 << (x))
class SegmentTree {
private:
  int max_layer;
  int n;
  vector<vector<int>> segments; // segments[l] contains 0 to 2^l - 1

public:
  explicit SegmentTree(int max_layer) : max_layer(max_layer), n(exp(max_layer)), segments(max_layer + 1) {
    // TODO: initialize
    segments[0] = vector<int>(n, 0);

    for (int layer = 1; layer <= max_layer; layer++) {
      for (int i = 0; i < exp(max_layer-layer); i++) {
        // TODO: combiner function
        segments[layer].push_back(min(segments[layer-1][2*i], segments[layer-1][2*i+1]));
      }
    }
  }

  void point_update(int i, int new_value) {
    segments[0][i] = new_value;
    for (int layer = 1; layer <= max_layer; layer++) {
      i /= 2;
      // TODO: combiner function
      segments[layer][i] = min(segments[layer-1][2*i], segments[layer-1][2*i+1]);
    }
  }

  /* Range query left to right inclusive, 0-indexed */
  int range_query(int left, int right) {
    // TODO: starting point for combiner function
    int answer = INT_MAX;
    while (left <= right) {
      // Find biggest interval (aka what's the biggest power of 2 that divides a)
      int layer_i = left;
      int layer = 0;
      while ((left % (2 << layer) == 0) && (layer < 18) && (left + (2 << layer) - 1 <= right)) {
        layer++;
        layer_i /= 2;
      }
      // TODO: combiner function
      answer = min(answer, segments[layer][layer_i]);
      left += exp(layer);
    }
    return answer;
  }
};





void stresstest() {
  int n = 16384;
  SegmentTree segment_tree(14);

  cout << "Stresstesting...\n";
  vector<int> A(n);
  for (int i = 0; i < n; i++) {
    A[i] = rand() % 10000;
    segment_tree.point_update(i, A[i]);
  }
  for (int bundle = 0; bundle < 10; bundle++) {
    for (int test = 0; test < 100'000; test++) {
      int op = rand() % 2;
      if (op == 0) {
        int i = rand() % n;
        int new_value = rand() % 10000;
        A[i] = new_value;
        segment_tree.point_update(i, new_value);
      } else {
        int left = rand() % n;
        int right = rand() % n;
        if (left > right) swap(left, right);
        int answer = INT_MAX;
        for (int i = left; i <= right; i++) {
          answer = min(answer, A[i]);
        }
        int segment_tree_answer = segment_tree.range_query(left, right);
        if (answer != segment_tree_answer) {
          fprintf(stderr, "Segment tree incorrect! expected %d, got %d\n", answer, segment_tree_answer);
          exit(1);
        }
      }
    }
    printf("Bundle %d (100k tests) passed!\n", bundle+1);
  }
  cout << "Stresstest passed!\n";
}

int main() {
  SegmentTree segment_tree(3); // n = 8
  printf("Minimum from 0 to 7: %d\n", segment_tree.range_query(0, 7));
  segment_tree.point_update(3, -1);
  segment_tree.point_update(7, -10);
  printf("A[3] = -1\n");
  printf("A[7] = -10\n");
  printf("Minimum from 0 to 5: %d\n", segment_tree.range_query(0, 5));
  printf("Minimum from 6 to 7: %d\n", segment_tree.range_query(6, 7));
  segment_tree.point_update(2, -2);
  printf("A[2] = -2\n");
  printf("Minimum from 0 to 5: %d\n", segment_tree.range_query(0, 5));

  stresstest();
}

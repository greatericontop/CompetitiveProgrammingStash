#include <bits/stdc++.h>
using namespace std;





#define exp(x) (1 << (x))
class SegmentTree {
private:
  int max_layer;
  int n;
  vector<vector<int>> segments; // segments[l] contains 0 to 2^l - 1

public:
  explicit SegmentTree(int max_layer) : max_layer(max_layer), n(exp(max_layer)), segments(max_layer + 1) {
    segments[0] = vector<int>(n, 0);

    for (int layer = 1; layer <= max_layer; layer++) {
      for (int i = 0; i < exp(max_layer-layer); i++) {
        segments[layer].push_back(segments[layer-1][2*i] + segments[layer-1][2*i+1]);
      }
    }
  }

  void point_update(int i, int new_value) {
    segments[0][i] = new_value;
    for (int layer = 1; layer <= max_layer; layer++) {
      i /= 2;
      segments[layer][i] = segments[layer-1][2*i] + segments[layer-1][2*i+1];
    }
  }

  /* Range query a to right inclusive, 0-indexed */
  int range_query(int left, int right) {
    int answer = 0;
    while (left <= right) {
      // Find biggest interval (aka what's the biggest power of 2 that divides a)
      int layer_i = left;
      int layer = 0;
      while ((left % (2 << layer) == 0) && (layer < 18) && (left + (2 << layer) - 1 <= right)) {
        layer++;
        layer_i /= 2;
      }
      answer = answer + segments[layer][layer_i];
      left += exp(layer);
    }
    return answer;
  }
};


using AdjList = vector<vector<int>>;

/* tour[v].first corresponds to v, tour[v].second corresponds to the last endpoint of the segment, inclusive. */
using EulerTour = vector<pair<int, int>>;

void euler_tour(int v, AdjList& adj, EulerTour& tour, int& counter) {
  tour[v].first = counter;
  counter++;
  for (int child : adj[v]) {
    euler_tour(child, adj, tour, counter);
  }
  tour[v].second = counter - 1;
}









int main() {
  ifstream cin("promote.in");
  ofstream cout("promote.out");

  int N;
  cin >> N;
  // <skill, cow id>
  vector<pair<int, int>> skills(N);
  for (int i = 0; i < N; i++) {
    cin >> skills[i].first;
    skills[i].second = i;
  }
  sort(skills.begin(), skills.end(), greater<pair<int, int>>());
  AdjList adj(N);
  for (int i = 1; i < N; i++) {
    int parent;
    cin >> parent;
    parent--;
    adj[parent].push_back(i);
  }

  EulerTour tour(N);
  int counter = 0;
  euler_tour(0, adj, tour, counter);

  SegmentTree segtree(17); // 131072
  vector<int> answers(N);
  for (auto [skill, cow_id] : skills) {
    int left = tour[cow_id].first;
    int right = tour[cow_id].second;
    answers[cow_id] = segtree.range_query(left, right);
    // Set to 1 so this cow gets counted for all future (less-skilled) cows
    segtree.point_update(left, 1);
  }

  for (int i = 0; i < N; i++) {
    cout << answers[i] << "\n";
  }
}

// Accepted

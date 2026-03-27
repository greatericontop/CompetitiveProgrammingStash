#include <bits/stdc++.h>
using namespace std;





#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template <class T> using OST = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;





int main() {
  ifstream cin("balancing.in");
  ofstream cout("balancing.out");

  int N;
  cin >> N;
  vector<pair<int, int>> cows(N); // x, y
  for (int i = 0; i < N; i++) {
    cin >> cows[i].first >> cows[i].second;
  }
  sort(cows.begin(), cows.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
    if (a.first == b.first) {
      return a.second < b.second;
    }
    return a.first < b.first;
  });


  // Store y coordinates of left half / right half as we sweep left to right
  OST<pair<int, int>> left;
  OST<pair<int, int>> right;
  for (int i = 0; i < N; i++) {
    right.insert({cows[i].second, i}); // .second is a unique id
  }
  int best_so_far = INT_MAX;

  vector<int> y_splits;
  //y_splits.push_back(0);
  for (int i = 0; i < N; i++) {
    y_splits.push_back(cows[i].second + 1);
  }
  sort(y_splits.begin(), y_splits.end());
  y_splits.erase(unique(y_splits.begin(), y_splits.end()), y_splits.end());

  for (int sweep_i = 0; sweep_i < N; sweep_i++) {
    right.erase({cows[sweep_i].second, sweep_i});
    left.insert({cows[sweep_i].second, sweep_i});
    if (sweep_i != N-1 && cows[sweep_i].first == cows[sweep_i+1].first) {
      // Have to move across all cows with the same x coordinate if any
      continue;
    }
    assert(left.size() == sweep_i+1);
    assert(right.size() == N-sweep_i-1);

    // Need to find best cut point for us
    int low = 0, high = y_splits.size()-1;
    while (low + 3 < high) {
      int mid = low + (high-low)/2;
      int top_left = left.order_of_key({y_splits[mid], 67});
      int bottom_left = left.size() - top_left;
      int left_contrib = max(top_left, bottom_left);
      int top_right = right.order_of_key({y_splits[mid], 67});
      int bottom_right = right.size() - top_right;
      int right_contrib = max(top_right, bottom_right);

      if (left_contrib >= right_contrib) {
        // Making left worse would be stupid
        if (top_left >= bottom_left) {
          // Want to split higher (lower y)
          high = mid;
        } else {
          low = mid;
        }
      } else {
        if (top_right >= bottom_right) {
          high = mid;
        } else {
          low = mid;
        }
      }
    }

    int ans = INT_MAX;
    for (int i = low; i <= high; i++) {
      int top_left = left.order_of_key({y_splits[i], 67});
      int bottom_left = left.size() - top_left;
      int left_contrib = max(top_left, bottom_left);
      int top_right = right.order_of_key({y_splits[i], 67});
      int bottom_right = right.size() - top_right;
      int right_contrib = max(top_right, bottom_right);
      ans = min(ans, max(left_contrib, right_contrib));
    }
    best_so_far = min(best_so_far, ans);
  }


  cout << best_so_far << "\n";
}


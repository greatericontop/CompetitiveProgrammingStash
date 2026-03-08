#include <bits/stdc++.h>
using namespace std;
#define long long long

//#define fprintf(...) // no-op





void solve() {
  int n;
  long h;
  cin >> n >> h;
  vector<long> original_heights(n);
  for (int i = 0; i < n; i++) {
    cin >> original_heights[i];
  }


  // Run coordinate compression
  // Height of the row of 0 is equal to sorted_heights[1] - sorted_heights[0]
  vector<long> sorted_heights = original_heights;
  sorted_heights.push_back(0);
  sorted_heights.push_back(h);
  sort(sorted_heights.begin(), sorted_heights.end());
  sorted_heights.erase(unique(sorted_heights.begin(), sorted_heights.end()), sorted_heights.end());
  vector<long> heights(n);
  for (int i = 0; i < n; i++) {
    heights[i] = lower_bound(sorted_heights.begin(), sorted_heights.end(), original_heights[i]) - sorted_heights.begin();
  }

  fprintf(stderr, "sorted_heights: ");
  for (long height : sorted_heights)  fprintf(stderr, "%lld ", height);
  fprintf(stderr, "\nheights (compressed): ");
  for (long height : heights)  fprintf(stderr, "%lld ", height);
  fprintf(stderr, "\n");


  // Run floodfill to see how much value we can capture ourselves (n^2 total)
  vector<long> floodfill_results(n);
  vector<vector<long>> floodfill_highest_walls(n, vector<long>(n));
  for (int col = 0; col < n; col++) {
    long total = 0;
    // Right (+ self)
    int i = col;
    long highest_wall = heights[i];
    while (i < n) {
      highest_wall = max(heights[i], highest_wall);
      floodfill_highest_walls[col][i] = highest_wall;
      // Contribution at our column = (top - highest_wall)
      total += (h - sorted_heights[highest_wall]);
      i++;
    }
    // Left
    i = col - 1;
    highest_wall = heights[col];
    while (i >= 0) {
      highest_wall = max(heights[i], highest_wall);
      floodfill_highest_walls[col][i] = highest_wall;
      total += (h - sorted_heights[highest_wall]);
      i--;
    }
    floodfill_results[col] = total;
  }

  fprintf(stderr, "floodfill_results: ");
  for (long result : floodfill_results)  fprintf(stderr, "%lld ", result);
  fprintf(stderr, "\n");
  fprintf(stderr, "floodfill_highest_walls:\n");
  for (int i = 0; i < n; i++) {
    fprintf(stderr, "col %d: ", i);
    for (int j = 0; j < n; j++) {
      fprintf(stderr, "%lld ", floodfill_highest_walls[i][j]);
    }
    fprintf(stderr, "\n");
  }


  // Now calculating combinations for both
  for (int left_col = 0; left_col < n-1; left_col++) {



    for (int right_col = left_col + 1; right_col < n; right_col++) {

    }
  }





}





int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--)  solve();
  return 0;
}
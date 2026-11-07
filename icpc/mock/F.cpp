#include <bits/stdc++.h>
using namespace std;
#define float long double
#define fprintf //


constexpr float epsilon = 1e-8;

struct Circle {
  float x, y;
  float r;
  float speed;

  bool collide(const Circle& other) {
    float distancesquared = (x-other.x)*(x-other.x) + (y-other.y)*(y-other.y);
    return distancesquared <= (r+other.r)*(r+other.r) + epsilon;
  }

  float time_till_collision(const Circle& other) {
    float distancesquared = (x-other.x)*(x-other.x) + (y-other.y)*(y-other.y);
    float distance = sqrtl(distancesquared) - r - other.r;
    return distance / (speed + other.speed);
  }
};


void dfs(int v, const vector<vector<int>>& adj, vector<bool>& visited) {
  if (visited[v])  return;
  visited[v] = true;
  for (int u : adj[v]) {
    dfs(u, adj, visited);
  }
}


signed main() {
  int n;  cin >> n;
  vector<Circle> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i].x >> a[i].y >> a[i].r >> a[i].speed;
  }

  bool trap = false;

  float time = 0;
  while (a.size() > 1) {
    bool collisions = false;
    float soonest_collision = 1e300;
    int one_of_colliding_is = -1;
    vector<vector<int>> adj(n);
    for (int i = 0; i < a.size(); i++) {
      for (int j = i+1; j < a.size(); j++) {
        if (a[i].collide(a[j])) {
          collisions = true;
          adj[i].push_back(j);
          adj[j].push_back(i);
          one_of_colliding_is = i;
        } else {
          soonest_collision = min(soonest_collision, a[i].time_till_collision(a[j]));
        }
      }
    }
    if (!collisions) {
      //if (trap) {
      //  assert(false);
      //}
      if (trap) {
        soonest_collision += 1e-8;
      }
      time += soonest_collision;
      for (Circle& c : a) {
        c.r += soonest_collision * c.speed;
      }
      trap = true;
    } else {
      trap = false;
      vector<int> circles;

      fprintf(stderr, "adj: ");
      for (int i = 0; i < a.size(); i++) {
        fprintf(stderr, "v=%d:", i);
        for (int v : adj[i]) {
          fprintf(stderr, "  %d", v);
        }
        fprintf(stderr, "\n");
      }

      vector<bool> visited(a.size(), false);
      dfs(one_of_colliding_is, adj, visited);
      for (int i = 0; i < a.size(); i++) {
        if (visited[i])  circles.push_back(i);
      }
      fprintf(stderr, "circles i: ");
      for (int i = 0; i < circles.size(); i++)  fprintf(stderr, "%d ", circles[i]);
      fprintf(stderr, "\n");
      assert(circles.size() >= 2);

      float sumx = 0, sumy = 0, sumrsquared = 0, maxs = 0;
      for (int i : circles) {
        sumx += a[i].x;
        sumy += a[i].y;
        sumrsquared += a[i].r * a[i].r;
        maxs = max(maxs, a[i].speed);
      }
      sumx /= circles.size();
      sumy /= circles.size();
      Circle newcircle = {sumx, sumy, sqrtl(sumrsquared), maxs};

      sort(circles.begin(), circles.end(), greater<int>());
      for (int i : circles) {
        a.erase(a.begin() + i);
      }

      a.push_back(newcircle);
    }
  }

  cout << fixed << setprecision(9) << a[0].x << " " << a[0].y << "\n";
  cout << a[0].r << "\n";


}
#include <bits/stdc++.h>
using namespace std;
#define long int64_t



struct Point {
  int i;
  int x, y;
  bool operator < (const Point& other) const {
    return i < other.i;
  }
};
struct PointSet {
  set<Point> points;
  map<int, set<Point>> x_counters;
  map<int, set<Point>> y_counters;

  void ins(Point p) {
    points.insert(p);
    x_counters[p.x].insert(p);
    y_counters[p.y].insert(p);
  }

  void rem(Point p, set<int>& x_del_queue, set<int>& y_del_queue) {
    points.erase(p);
    x_counters[p.x].erase(p);
    if (x_counters[p.x].size() == 1)  x_del_queue.insert(p.x);
    y_counters[p.y].erase(p);
    if (y_counters[p.y].size() == 1)  y_del_queue.insert(p.y);
  }
};





int main() {
  int n;  cin >> n;
  PointSet points;
  for (int i = 1; i <= n; i++) {
    int x, y;  cin >> x >> y;
    points.ins(Point{i, x, y});
  }
  set<int> x_del_queue_prev, y_del_queue_prev, x_del_queue_cur, y_del_queue_cur;
  for (auto [x, vals] : points.x_counters) {
    if (vals.size() == 1)  x_del_queue_prev.insert(x);
  }
  for (auto [y, vals] : points.y_counters) {
    if (vals.size() == 1)  y_del_queue_prev.insert(y);
  }

  int answer_from_last_time = -1;
  while (true) {
    if (points.points.empty()) {
      // return previous answer
      break;
    }
    if (x_del_queue_prev.empty() && y_del_queue_prev.empty()) {
      // infinite game
      answer_from_last_time = INT_MAX;
      for (Point p : points.points) {
        answer_from_last_time = min(answer_from_last_time, p.i);
      }
      break;
    }
    int lowest_index_deleted = INT_MAX;

    for (int x : x_del_queue_prev) {
      set<Point>& pts = points.x_counters[x];
      if (pts.empty())  continue;  //maybe got enqueued previously but also later deleted
      assert(pts.size() == 1);
      Point p = *pts.begin();
      points.rem(p, x_del_queue_cur, y_del_queue_cur);
      lowest_index_deleted = min(lowest_index_deleted, p.i);
    }
    for (int y : y_del_queue_prev) {
      set<Point>& pts = points.y_counters[y];
      if (pts.empty())  continue;  //maybe already got deleted
      assert(pts.size() == 1);
      Point p = *pts.begin();
      points.rem(p, x_del_queue_cur, y_del_queue_cur);
      lowest_index_deleted = min(lowest_index_deleted, p.i);
    }

    swap(x_del_queue_prev, x_del_queue_cur);
    swap(y_del_queue_prev, y_del_queue_cur);
    x_del_queue_cur.clear();
    y_del_queue_cur.clear();
    assert(lowest_index_deleted < INT_MAX);
    answer_from_last_time = lowest_index_deleted;
  }

  cout << answer_from_last_time << endl;




}

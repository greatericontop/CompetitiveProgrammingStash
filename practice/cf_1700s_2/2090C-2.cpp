#include <bits/stdc++.h>
using namespace std;


#define GREATERIC_DEBUG


#ifdef GREATERIC_DEBUG
  #define PRINTVEC(vec) do { \
    fprintf(stderr, "%s:  ", #vec); \
    for (const auto& _x : (vec))  fprintf(stderr, "%d ", _x); \
    fprintf(stderr, "\n"); \
  } while (0)
  #define PRINTVECL(vec) do { \
    fprintf(stderr, "%s:  ", #vec); \
    for (const auto& _x : (vec))  fprintf(stderr, "%lld ", _x); \
    fprintf(stderr, "\n"); \
  } while (0)
  #define PRINTMAP(map) do { \
    fprintf(stderr, "%s:   ", #map); \
    for (const auto& _p : (map))  fprintf(stderr, "%d->%d  ", _p.first, _p.second); \
    fprintf(stderr, "\n"); \
  } while (0)
  #define PRINTVECP(vec) do { \
    fprintf(stderr, "%s:   ", #vec); \
    for (const auto& _p : (vec))  fprintf(stderr, "[%d %d],  ", _p.first, _p.second); \
    fprintf(stderr, "\n"); \
  } while (0)
  #define PRINTVECPL(vec) do { \
    fprintf(stderr, "%s:   ", #vec); \
    for (const auto& _p : (vec))  fprintf(stderr, "[%lld %lld],  ", _p.first, _p.second); \
    fprintf(stderr, "\n"); \
  } while (0)
#else
  #define fprintf(...)
  #define PRINTVEC(...)
  #define PRINTVECL(...)
  #define PRINTMAP(...)
  #define PRINTVECP(...)
  #define PRINTVECPL(...)
#endif
#define long long long
#define pb push_back
#define LONG(x) ((long) (x))
#define INT(x) ((int) (x))
#define FORI(x) for (int i = 0; i < (x); i++)
using pairii = pair<int, int>;
using pairll = pair<long, long>;
using AdjList = vector<vector<int>>;
// Positive numbers only
constexpr static inline int ceildiv(int a, int b) { return (a + b - 1) / b; }
constexpr static inline long ceildivl(long a, long b) { return (a + b - 1) / b; }
// Only O(1) for vectors!
template <typename It, typename Container> constexpr static inline int itertoi(const It& it, const Container& container) { return distance(container.begin(), it); }









struct Cell {
  int x;
  int y;

  constexpr inline int origin_dist() const {
    int extra = (x%3==2 && y%3==2 ? 2 : 0);
    return x + y + extra;
  }

  bool operator < (const Cell& other) const {
    int od_self = origin_dist(), od_other = other.origin_dist();
    if (od_self != od_other)  return od_self < od_other;
    if (x != other.x)  return x < other.x;
    return y < other.y;
  }
};


void solve() {
  int n;
  cin >> n;

  set<Cell> cells;
  set<Cell> unoccupied_table_cells;
  int sqrtn = 0;
  while (sqrtn * sqrtn < n)  sqrtn++;
  sqrtn += 2;
  for (int i = 0; i <= 2*sqrtn; i++) {
    for (int j = 0; j <= 2*sqrtn; j++) {
      if (i + j > 2*sqrtn)  continue;
      cells.insert({3*i+1, 3*j+1});
      cells.insert({3*i+1, 3*j+2});
      cells.insert({3*i+2, 3*j+1});
      cells.insert({3*i+2, 3*j+2});
      unoccupied_table_cells.insert({3*i+1, 3*j+1});
    }
  }
  fprintf(stderr, "cells: %ld, tables: %ld\n", cells.size(), unoccupied_table_cells.size());

  for (int t = 0; t < n; t++) {
    int characteristic; cin >> characteristic;
    if (characteristic == 0) {
      // completely unoccupied table
      auto it = unoccupied_table_cells.begin();
      assert(it != unoccupied_table_cells.end());
      cout << it->x << " " << it->y << "\n";
      cells.erase(*it);
      unoccupied_table_cells.erase(it);
    } else {
      // take nearest seat
      auto it = cells.begin();
      assert(it != cells.end());
      cout << it->x << " " << it->y << "\n";
      if (unoccupied_table_cells.count(*it))  unoccupied_table_cells.erase(*it);  //trick: first one we remove is always the one in this set
      cells.erase(it);
    }
  }

}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  cin >> t;
  while (t--)  solve();
  return 0;
}

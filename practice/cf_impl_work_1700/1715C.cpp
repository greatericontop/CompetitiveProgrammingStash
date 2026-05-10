#include <bits/stdc++.h>
using namespace std;


//#define GREATERIC_DEBUG


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
#define FORI(x) for (int i = 0; i < (x); i++)
using pairii = pair<int, int>;
using pairll = pair<long, long>;
using AdjList = vector<vector<int>>;
// Positive numbers only
constexpr static inline int ceildiv(int a, int b) { return (a + b - 1) / b; }
constexpr static inline long ceildivl(long a, long b) { return (a + b - 1) / b; }









struct Block {
    int l;
    int r;
    int num;
    bool operator<(const Block& other) const {
        return r < other.r;
    }

    long value(long n) const {
      long a = l;
      long b = n-r;
      return n*(n+1)/2 - a*(a-1)/2 - b*(b+1)/2;
    }
};

void printblockset(const set<Block>& blocks) {
#ifdef GREATERIC_DEBUG
  fprintf(stderr, "blocks:\n");
  for (const auto& block : blocks) {
    fprintf(stderr, "  [%d, %d] num%d\n", block.l, block.r, block.num);
  }
#else
#endif
}

void fix(set<Block>& blocks, set<Block>::iterator it, long& cur_value, int n) {
  Block b = *it;
  if (it != blocks.begin() && prev(it)->num == b.num) {
    Block left = *prev(it);
    cur_value -= left.value(n);
    cur_value -= b.value(n);
    blocks.erase(prev(it));
    blocks.erase(it);
    Block new_block = {left.l, b.r, b.num};
    blocks.insert(new_block);
    cur_value += new_block.value(n);

    b = new_block;
    it = blocks.find(new_block);
  }
  if (next(it) != blocks.end() && next(it)->num == b.num) {
    Block right = *next(it);
    cur_value -= right.value(n);
    cur_value -= b.value(n);
    blocks.erase(next(it));
    blocks.erase(it);
    Block new_block = {b.l, right.r, b.num};
    blocks.insert(new_block);
    cur_value += new_block.value(n);
  }
}

void solve() {
  int n, m;
  cin >> n >> m;
  vector<int> a(n+1);
  for (int i = 1; i <= n; i++)  cin >> a[i];
  set<Block> blocks;
  Block cur = {1, 1, a[1]};
  for (int i = 2; i <= n; i++) {
    if (a[i] == cur.num) {
      cur.r = i;
    } else {
      blocks.insert(cur);
      cur = {i, i, a[i]};
    }
  }
  blocks.insert(cur);

  long cur_value = 0;
  for (const auto& block : blocks)  cur_value += block.value(n);

  for (int q = 0; q < m; q++) {
    int pos, x;
    cin >> pos >> x;
    auto it = blocks.lower_bound({0, pos, 0});
    Block b = *it;
    //ok
    //fprintf(stderr, "query: pos%d x%d, cur block [%d %d]\n", pos, x, b.l, b.r);
    Block new_left = {b.l, pos-1, b.num};
    Block new_cur = {pos, pos, x};
    Block new_right = {pos+1, b.r, b.num};
    blocks.erase(it);
    cur_value -= b.value(n);
    if (new_left.l <= new_left.r) {
      blocks.insert(new_left);
      cur_value += new_left.value(n);
    }
    if (new_right.l <= new_right.r) {
      blocks.insert(new_right);
      cur_value += new_right.value(n);
    }
    blocks.insert(new_cur);
    cur_value += new_cur.value(n);
    auto it1 = blocks.find(new_cur);
    fprintf(stderr, "after query 'a[%d] = %d', before fixing:\n", pos, x);
    printblockset(blocks);
    fix(blocks, it1, cur_value, n);
    fprintf(stderr, "after query 'a[%d] = %d':\n", pos, x);
    printblockset(blocks);
    cout << cur_value << "\n";
  }



}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  //cin >> t;
  while (t--)  solve();
  return 0;
}

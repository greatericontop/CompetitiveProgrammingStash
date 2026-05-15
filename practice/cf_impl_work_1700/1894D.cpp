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










struct Entry {
  int val;
  int i;
};

struct HeadEntry {
  int val;
  int i;
  int seq_i;

  bool operator < (const HeadEntry& other) const {
    if (val != other.val)  return val < other.val;
    if (i != other.i)  return i < other.i;
    return seq_i < other.seq_i;
  }
};

void solve() {
  int n, m;
  cin >> n >> m;
  vector<int> a(n);
  FORI(n)  cin >> a[i];
  vector<int> b(m);
  FORI(m)  cin >> b[i];
  sort(b.begin(), b.end(), greater<int>());

  // Decompose a into the minimum number of LDS (non-strict)
  vector<vector<Entry>> lds;
  set<HeadEntry> heads;
  for (int i = 0; i < n; i++) {
    Entry entry = {a[i], i};
    auto it = heads.lower_bound({entry.val, -1, -1});
    if (it == heads.end()) {
      // Make new lds
      lds.push_back(vector<Entry>());
      lds.back().pb(entry);
      heads.insert({entry.val, entry.i, INT(lds.size()) - 1});
    } else {
      // Insert into
      int seq_i = it->seq_i;
      lds[seq_i].pb(entry);
      heads.erase(it);
      heads.insert({entry.val, entry.i, seq_i});
    }
  }
  assert(lds.size() >= 1);
  fprintf(stderr, "Decomposed into %d sequences (this is the length of LIS)\n", (int) lds.size());
  for (int seq_i = 0; seq_i < lds.size(); seq_i++) {
    fprintf(stderr, "Sequence %d: ", seq_i);
    for (const auto& entry : lds[seq_i])  fprintf(stderr, "%d ", entry.val);
    fprintf(stderr, "\n");
  }

  int b_ptr = 0;
  vector<Entry>& seq = lds[0];
  int j = 0;  //pointing into seq
  vector<int> ans(n+m);
  int k = 0;
  for (int i = 0; i < n; i++) {
    // add a[i] to answer
    if (j < seq.size() && seq[j].i == i) {
      fprintf(stderr, "  pushing j=%d, seq[j].val=%d seq[j].i=%d\n", j, seq[j].val, seq[j].i);
      // push current values in b first
      while (b_ptr < m && b[b_ptr] >= seq[j].val) {
        ans[k++] = b[b_ptr++];
      }
      j++;
    }
    ans[k++] = a[i];
  }

  // push remaining values in b
  while (b_ptr < m) {
    ans[k++] = b[b_ptr++];
  }
  assert(k == n + m);

  for (int i = 0; i < n + m; i++) {
    cout << ans[i] << " ";
  }
  cout << "\n";





}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  cin >> t;
  while (t--)  solve();
  return 0;
}

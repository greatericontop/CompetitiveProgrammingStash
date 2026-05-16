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









long card_to_num(const vector<int>& card) {
  long num = 0;
  for (int i = 0; i < (int) card.size(); i++) {
    num = num * 4 + card[i];
  }
  return num;
}

constexpr static inline int extract(long num, int pos) {
  return (num >> (2*pos)) & 0b11;
}


void solve() {
  int n, k;
  cin >> n >> k;
  vector<long> cards(n);
  map<long, int> indices;
  for (int i = 0; i < n; i++) {
    vector<int> card(k);
    for (int j = 0; j < k; j++)  cin >> card[j];
    cards[i] = card_to_num(card);
    indices[cards[i]] = i;
  }

  vector<long> set_counts(n, 0);
  for (int i = 0; i < n; i++) {
    for (int j = i+1; j < n; j++) {
      // 500k * ~30 = 15M
      vector<int> third(k);
      for (int pos = 0; pos < k; pos++) {
        int a = extract(cards[i], k-1-pos);
        int b = extract(cards[j], k-1-pos);
        if (a == b)  third[pos] = a;
        else  third[pos] = 3 - a - b;
      }
      fprintf(stderr, "cards %d and %d require \n", i, j);
      PRINTVEC(third);
      long third_num = card_to_num(third);
      if (indices.count(third_num)) {
        int thirdidx = indices[third_num];
        set_counts[i]++;
        set_counts[j]++;
        set_counts[thirdidx]++;
      }
    }
  }

  for (int i = 0; i < n; i++) {
    set_counts[i] /= 3;
  }
  PRINTVECL(set_counts);

  long ans = 0;
  for (int i = 0; i < n; i++) {
    ans += set_counts[i] * (set_counts[i] - 1) / 2;
  }
  cout << ans << "\n";

}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  //cin >> t;
  while (t--)  solve();
  return 0;
}

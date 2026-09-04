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
  #define PRINTVECB(vec) do { \
    fprintf(stderr, "%s:   ", #vec); \
    for (const auto& _p : (vec))  fprintf(stderr, "%s,  ", _p ? "true" : "false"); \
    fprintf(stderr, "\n"); \
  } while (0)
#else
  #define fprintf(...)
  #define PRINTVEC(...)
  #define PRINTVECL(...)
  #define PRINTMAP(...)
  #define PRINTVECP(...)
  #define PRINTVECPL(...)
  #define PRINTVECB(...)
#endif
#define long int64_t
#define pb push_back
#define LONG(x) ((long) (x))
#define INT(x) ((int) (x))
#define FORI(x) for (int i = 0; i < (x); i++)
#define FORI1(x) for (int i = 1; i <= (x); i++)
using pairii = pair<int, int>;
using pairll = pair<long, long>;
using AdjList = vector<vector<int>>;
// Positive numbers only
constexpr static inline int ceildiv(int a, int b) { return (a + b - 1) / b; }
constexpr static inline long ceildivl(long a, long b) { return (a + b - 1) / b; }
// Round :a: down or up to the closest multiple of :b:
constexpr static inline int rounddown(int a, int b) { return (a / b) * b; }
constexpr static inline int roundup(int a, int b) { return ceildiv(a, b) * b; }
//constexpr static long MOD = 1'000'000'007LL;
//constexpr static long MOD =   998'244'353LL;
template <class T> class Fenwick {
private:
  int n;
  vector<T> data; // note: 1-indexed

public:
  explicit Fenwick(int n) : n(n), data(n+1) {
  }

  /* Initialize from an array of values[1...n] (it's 1-indexed!) */
  void init(vector<T> values) {
    vector<T> prefix_sums(n+1);
    prefix_sums[0] = 0;
    for (int i = 1; i <= n; i++) {
      prefix_sums[i] = prefix_sums[i-1] + values[i];
    }
    for (int i = 1; i <= n; i++) {
      data[i] = prefix_sums[i] - prefix_sums[i - (i & -i)];
    }
  }

  void add(int i, T value) {
    while (i <= n) {
      data[i] += value;
      i += i & -i;
    }
  }

  void set(int i, T value) {
    T current_value = prefix_sum(i) - prefix_sum(i-1);
    add(i, value - current_value);
  }

  /* Prefix sum from indices 1 to i inclusive */
  T prefix_sum(int i) {
    if (i == 0)  return 0;
    T sum = 0;
    while (i >= 1) {
      sum += data[i];
      i -= i & -i;
    }
    return sum;
  }

  /* Range sum from left to right inclusive */
  T range_sum(int left, int right) {
    return prefix_sum(right) - prefix_sum(left-1);
  }

};


struct Event {
  int when;
  int i;
  char type;  //'B' block 'L' line
};








void solve() {
  int n;  cin >> n;
  vector<int> a(n+1), h(n+1);
  FORI1(n)  cin >> a[i];
  FORI1(n-1)  cin >> h[i];
  Fenwick<int> blocks(n+3);
  blocks.init(vector<int>(n+4, 0));
  set<int> lines;
  lines.insert(0);
  lines.insert(n);
  vector<Event> events;
  FORI1(n)  events.pb({a[i], i, 'B'});
  FORI1(n-1)  events.pb({h[i], i, 'L'});
  sort(events.begin(), events.end(), [](const Event& e1, const Event& e2) {
    return e1.when > e2.when;
  });
  vector<int> cached_sizes(n+1, 0);  //cached sizes for each *line*
  vector<int> last_update(n+1, n+1);  //last update timestamp
  vector<long> difference_array(n+3, 0);

  auto lazy_update_line = [&](int i, int new_timestamp) -> void {
    int timesteps = last_update[i] - new_timestamp;  assert(timesteps >= 0);
    difference_array[i] -= timesteps;
    assert(cached_sizes[i] <= i);
    difference_array[i - cached_sizes[i]] += timesteps;

    last_update[i] = new_timestamp;
    // cached_sizes is not updated here
  };

  for (const auto [when, i, type] : events) {
    fprintf(stderr, "process event: at height %d, index %d, type %c\n", when, i, type);
    if (type == 'B') {
      // new block is added
      assert(blocks.range_sum(i, i) == 0);
      blocks.add(i, 1);
      // update line ahead of it
      auto it = lines.lower_bound(i);  assert(it != lines.end());  int line = *it;
      lazy_update_line(line, when+1);
      cached_sizes[line]++;
      assert(cached_sizes[line] == blocks.range_sum((*prev(it)) + 1, line));
    } else {
      // new line is added
      auto it = lines.lower_bound(i);
      assert(it != lines.end());  int next_line = *it;
      assert(it != lines.begin());  int prev_line = *prev(it);
      lazy_update_line(next_line, when+1);

      // now update sizes of these two lines
      last_update[i] = when+1;
      cached_sizes[i] = blocks.range_sum(prev_line + 1, i);
      cached_sizes[next_line] = blocks.range_sum(i + 1, next_line);

      lines.insert(i);
    }
  }
  for (int i = 0; i <= n; i++) {
    lazy_update_line(i, 1);
  }

  long acc = difference_array[0];
  for (int i = 1; i <= n; i++) {
    cout << acc << " ";
    acc += difference_array[i];
  }
  cout << "\n";
}










int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  //cin >> t;
  while (t--)  solve();
  return 0;
}

/*  -fsanitize=undefined -fsanitize=address -fno-sanitize-recover -Wall -Werror -Wextra -Wshadow -Wfloat-equal
    -Wno-error=unused-variable -Wno-error=unused-parameter -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2 -O1  */

/*
 * This code contains the use of comments! You can identify them with the "//" or "/*" symbols.
 * Comments are used to explain the code and make it easier to understand.
 * They are ignored by the compiler and do not affect the execution of the program.
 * In this code, comments are used to explain the purpose of the code, the input and output format, and the logic behind the solution.
 * Unlike the 3 lines shown above, the comments in this code were lovingly hand-inserted and not a result of AI generated text.
 * Thanks to sc3developer <3 for inspiring this message and for being a great mentor.
 */

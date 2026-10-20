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





// 136MB
// extra vectors for children and queries here (each max 1M elements total) like 30MB or so tops probably

// the map could be a bit but 1 million RBT nodes should not be bad

// stack frames?




struct Node {
  int parent;
  int number_here;
  vector<int> queries_here;
  vector<int> children;
};



/* Contract: after calling this, the state is returned untouched (zeros are erased) */
void visit(int node, const vector<Node>& nodes, map<int, int>& state, vector<int>& answers) {
  state[nodes[node].number_here]++;

  for (int qidx : nodes[node].queries_here) {
    answers[qidx] = state.size();
  }

  for (int child : nodes[node].children) {
    visit(child, nodes, state, answers);
  }

  state[nodes[node].number_here]--;
  if (state[nodes[node].number_here] == 0)  state.erase(nodes[node].number_here);
}



void solve() {
  int q;  cin >> q;

  vector<Node> nodes;  nodes.reserve(q + 100);  // 1 million * (vector tags should fit)

  // allocate int[q][20] using malloc
  auto *ancestors = (int(*)[20]) calloc(sizeof(int) * (q + 100) * 20, 1);

  nodes.pb(Node{.parent = -1, .number_here = -1});
  int cur = 0;  //which node number we are at
  stack<int> st;
  st.push(cur);

  auto binlift = [&](int node) {
    int * anc = ancestors[node];

    int p = nodes[node].parent;
    anc[0] = p;
    for (int i = 0; i < 19; i++) {
      p = ancestors[p][i];
      anc[i+1] = p;
    }
  };
  auto insert_new_node = [&](int parent, int number_here) -> int {
    int idx = nodes.size();
    nodes.pb(Node{.parent = parent, .number_here = number_here});
    nodes[parent].children.pb(idx);
    binlift(idx);

    fprintf(stderr, "Inserted node %d (parent %d), ancestors: ", idx, parent);
    //for (int a : nodes[idx].ancestors)  fprintf(stderr, " %d", a);
    fprintf(stderr, "\n");

    return idx;
  };
  auto go_up = [&](int node, int amt) -> int {
    for (int b = 0; amt > 0; b++) {
      if (amt & 1) {
        node = ancestors[node][b];
      }
      amt >>= 1;
    }
    return node;
  };

  vector<int> qindices;
  for (int idx = 0; idx < q; idx++) {
    char op;  cin >> op;
    if (op == '+') {
      int x;  cin >> x;
      cur = insert_new_node(cur, x);
      st.push(cur);
    } else if (op == '-') {
      int amt;  cin >> amt;
      cur = go_up(cur, amt);
      st.push(cur);
    } else if (op == '!') {
      assert(st.top() == cur);
      st.pop();
      cur = st.top();
    } else if (op == '?') {
      nodes[cur].queries_here.pb(idx);
      qindices.pb(idx);
    } else {
      assert(false);
    }
    fprintf(stderr, "After op #%d, cur = %d\n", idx, cur);
  }

  free(ancestors);  ancestors = nullptr;

  if (true) {
    vector<int> answers(q, -1);
    map<int, int> state;
    visit(0, nodes, state, answers);

    for (int idx : qindices) {
      // because -1 was included in the root
      cout << (answers[idx] - 1) << "\n";
    }
  }

}










int main() {

  fprintf(stderr, "sizeof Node %d", sizeof(Node));
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

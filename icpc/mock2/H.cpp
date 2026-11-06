#include <bits/stdc++.h>
using namespace std;





typedef array<int, 8> State;
struct Op {
  int start;
  int len;
};

void printar(State s) {
  fprintf(stderr, "[%d %d %d %d %d %d %d %d]", s[0], s[1], s[2], s[3], s[4], s[5], s[6], s[7]);
}


int main() {
  int M, S;
  cin >> M >> S;
  State initial_state = {};
  for (int i = 0; i < M; i++)  cin >> initial_state[i];
  State goal_state = {};
  for (int i = 0; i < M; i++)  cin >> goal_state[i];
  vector<Op> ops(S);
  for (int i = 0; i < S; i++) {
    cin >> ops[i].start >> ops[i].len;
  }


  map<State, int> distances;
  queue<State> bfs_q;
  distances[initial_state] = 0;
  bfs_q.push(initial_state);
  while (!bfs_q.empty()) {
    State v = bfs_q.front();  bfs_q.pop();
    int dist = distances[v];
    if (v == goal_state) {
      cout << dist << endl;
      return 0;
    }

    //fprintf(stderr, "v = ");  printar(v);  fprintf(stderr, "\n");
    for (Op op : ops) {
      State s = v;
      // op.start ... op.start + op.len - 1
      int saved_end_val = s[(op.start + op.len - 1) % M];
      for (int i = op.len-1; i >= 1; i--) {
        s[(op.start+i) % M] = s[(op.start+i-1+M) % M];
      }
      s[op.start] = saved_end_val;
      //fprintf(stderr, "  s: ");  printar(s);  fprintf(stderr, "\n");

      if (distances.find(s) == distances.end()) {
        distances[s] = dist+1;
        bfs_q.push(s);
      } else {
        //already pushed/visited
      }

    }


  }

  cout << -1 << endl;
  return 0;


}

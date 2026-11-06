#include <bits/stdc++.h>
using namespace std;



void vis(int v, const vector<vector<int>>& adj, vector<int>& cur_cc, vector<bool>& visited) {
  if (visited[v])  return;
  visited[v] = true;
  cur_cc.push_back(v);
  for (int u : adj[v]) {
    vis(u, adj, cur_cc, visited);
  }
}


struct Solo {
  int i;
  int score;

  bool operator < (const Solo& other) const {
    if (score != other.score)  return score > other.score;
    if (i != other.i)  return i > other.i;
    assert(false);
  }
};
struct Double {
  int i1;
  int i2;
  int score;

  bool operator < (const Double& other) const {
    if (score != other.score)  return score > other.score;
    if (i1 != other.i1)  return i1 > other.i1;
    if (i2 != other.i2)  return i2 > other.i2;
    assert(false);
  }
};
struct Triple {
  int i1, i2, i3;
};


int main() {
  int K;  cin >> K;
  int m;  cin >> m;
  vector<int> scores(3*K+1);
  for (int i = 1; i <= 3*K; i++)  cin >> scores[i];
  vector<vector<int>> adj(3*K+1);
  for (int i = 0; i < m; i++) {
    int u, v;  cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  //fprintf(stderr, "start\n");

  set<Solo> solos;
  set<Double> doubles;
  vector<Triple> triples;

  vector<bool> visited(3*K+1, false);
  for (int i = 1; i <= 3*K; i++) {
    if (visited[i])  continue;
    vector<int> cur_cc;
    vis(i, adj, cur_cc, visited);

    if (cur_cc.size() >= 4) {
      cout << "Impossible\n";
      return 0;
    } else if (cur_cc.size() == 3) {
      triples.push_back(Triple{cur_cc[0], cur_cc[1], cur_cc[2]});
    } else if (cur_cc.size() == 2) {
      doubles.insert(Double{cur_cc[0], cur_cc[1], scores[cur_cc[0]] + scores[cur_cc[1]]});
    } else {
      solos.insert(Solo{cur_cc[0], scores[cur_cc[0]]});
    }
  }


  while (!(solos.empty() && doubles.empty())) {
    if (solos.empty()) {
      cout << "Impossible\n";
      return 0;
    }
    Solo best_solo = *solos.begin();  solos.erase(solos.begin());

    bool use_double = false;
    if (!doubles.empty()) {
      if (solos.size() < 2) {
        use_double = true;
      } else {
        // make sure there are enough solos
        int num_solos_left_after = solos.size() - 2;
        int num_doubles_left_after = doubles.size();
        if (num_solos_left_after < num_doubles_left_after) {
          use_double = true;
        } else {
          // compare
          int doubles_score = doubles.begin()->score;
          int solos_score = solos.begin()->score + (next(solos.begin())->score);
          if (doubles_score >= solos_score)  use_double = true;
          else  use_double = false;
        }
      }
    }

    if (use_double) {
      Double d = *doubles.begin();  doubles.erase(doubles.begin());
      triples.push_back(Triple{d.i1, d.i2, best_solo.i});
    } else {
      Solo s1 = *solos.begin();
      Solo s2 = *next(solos.begin());
      solos.erase(solos.begin());
      solos.erase(solos.begin());
      triples.push_back(Triple{s1.i, s2.i, best_solo.i});
    }
  }

  cout << "Possible\n";
  assert(triples.size() == K);
  for (Triple t : triples) {
    cout << t.i1 << " " << t.i2 << " " << t.i3 << "\n";
  }


}

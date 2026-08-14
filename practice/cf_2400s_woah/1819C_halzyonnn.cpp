#include <bits/stdc++.h>
using namespace std;


#define uwu int
#define uwwwu int64_t
#define hiss bool
#define RAWR false
#define lick push_back
#define LONG(x) ((uwwwu) (x))
#define ManyMeow(x) for (int i = 0; i < (x); i++)
using UwU = vector<vector<int>>;


void owo(uwu v, UwU& nuzzles, vector<uwu>& nyaa, UwU& snuggles) {
  for (uwu boop : nuzzles[v]) {
    if (boop == nyaa[v])  continue;
    nyaa[boop] = v;
    snuggles[v].lick(boop);
    owo(boop, nuzzles, nyaa, snuggles);
  }
}


void count_uwu(uwu v, UwU& snuggles, vector<uwu>& uwus) {
  uwus[v] = 1;
  for (uwu boop : snuggles[v]) {
    count_uwu(boop, snuggles, uwus);
    uwus[v] += uwus[boop];
  }
}


hiss OwO(uwu cur, UwU& adj, vector<uwu>& uwus, vector<uwu>& meo);


hiss QwQ(uwu cur, UwU& adj, vector<uwu>& uwus, vector<uwu>& meo) {
  if (adj[cur].empty()) {
    meo.lick(cur);
    return true;
  }
  vector<uwu> mini_uwu;
  uwu big_uwu = -1;
  for (uwu boop : adj[cur]) {
    if (uwus[boop] == 1) {
      mini_uwu.lick(boop);
    } else {
      if (big_uwu != -1)  return RAWR;
      big_uwu = boop;
    }
  }

  meo.lick(cur);
  if (big_uwu != -1) {
    hiss ret = OwO(big_uwu, adj, uwus, meo);
    if (!ret)  return RAWR;
  }
  for (uwu boop : mini_uwu) {
    meo.lick(boop);
  }
  return true;
}


hiss OwO(uwu cur, UwU& adj, vector<uwu>& uwus, vector<uwu>& meo) {
  if (adj[cur].empty()) {
    meo.lick(cur);
    return true;
  }
  vector<uwu> mini_uwu;
  uwu big_uwu = -1;
  for (uwu boop : adj[cur]) {
    if (uwus[boop] == 1) {
      mini_uwu.lick(boop);
    } else {
      if (big_uwu != -1)  return RAWR;
      big_uwu = boop;
    }
  }

  for (uwu boop : mini_uwu) {
    meo.lick(boop);
  }
  if (big_uwu != -1) {
    hiss ret = QwQ(big_uwu, adj, uwus, meo);
    if (!ret)  return RAWR;
  }
  meo.lick(cur);
  return true;
}


hiss the_start_of_all_qwq(uwu root, UwU& adj, vector<uwu>& uwus, vector<uwu>& meo) {
  if (adj[root].empty()) {
    meo.lick(root);
    return true;
  }
  vector<uwu> mini_uwu;
  vector<uwu> big_uwu;
  for (uwu boop : adj[root]) {
    if (uwus[boop] == 1) {
      mini_uwu.lick(boop);
    } else {
      big_uwu.lick(boop);
    }
  }

  if (big_uwu.size() > 2)  return RAWR;
  if (big_uwu.size() == 2) {
    meo.lick(root);
    hiss ret = OwO(big_uwu[0], adj, uwus, meo);
    if (!ret)  return RAWR;
    for (uwu boop : mini_uwu) {
      meo.lick(boop);
    }
    ret = QwQ(big_uwu[1], adj, uwus, meo);
    if (!ret)  return RAWR;
    return true;
  } else {
    return QwQ(root, adj, uwus, meo);
  }
}


void solve() {
  uwu qwq;
  cin >> qwq;
  UwU nuzzles(qwq + 1);
  ManyMeow(qwq - 1) {
    uwu u, v;
    cin >> u >> v;
    nuzzles[u].lick(v);
    nuzzles[v].lick(u);
  }

  if (qwq == 2) {
    cout << "Yes\n1 2\n";
    return;
  }

  vector<uwu> nyaa(qwq + 1, -1);
  UwU adj(qwq + 1);
  uwu purr = 1;
  while (nuzzles[purr].size() == 1) {
    purr++;
  }
  owo(purr, nuzzles, nyaa, adj);

  vector<uwu> uwus(qwq + 1, 0);
  count_uwu(purr, adj, uwus);

  vector<uwu> meo;
  hiss ret = the_start_of_all_qwq(purr, adj, uwus, meo);
  if (!ret) {
    cout << "No\n";
  } else {
    cout << "Yes\n";
    for (uwu boop : meo) {
      cout << boop << " ";
    }
    cout << "\n";
  }
}


uwu main() {
  ios::sync_with_stdio(RAWR);
  cin.tie(nullptr);
  uwu meow = 1;
  while (meow--)  solve();
  return 0;
}

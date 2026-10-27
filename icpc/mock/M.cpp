#include <bits/stdc++.h>
using namespace std;

const int maxn = 55;
int n, m , k;
#define L 0
#define R 1
#define M 2
char a[maxn][maxn];
int d[maxn][maxn][3][maxn][maxn];
string words[maxn];

struct Data {
  int x, y;
  int st;
  int i, pos;
};

vector<pair<int,int>> startchar;

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> m >> k;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      cin >> a[i][j];
    }
  }
  for (int i = 1; i <= k; i++) {
    cin >> words[i]; // index start with 0
    startchar.push_back({i, 0});
  }

  // for (int i = 1; i <= n; i++) {
  //   for (int j = 1; j <= m; j++) {
  //     cout << a[i][j];
  //   }
  //   cout <<'\n';
//  }
  // for (auto [x , y] : startchar) {
  //   cout << x << ' ' << y << '\n';
  // }
  queue<Data> q;
  for (int j = 1; j <= m; j++) {
    // check first row with the first letter
    for (int  i= 1; i <= k; i++) {
      if (a[1][j] == words[i][0]) {
        q.push({1, j, M, i, 0});
        d[1][j][M][i][0] = 1;
      }
    }
  }


  while (!q.empty()) {
    auto [x, y, st, i, pos] = q.front();
    q.pop();
    if (x==n && pos == words[i].size() - 1) {
      cout << d[x][y][st][i][pos];
      return 0;
    }
    vector<pair<int,int>> nextchar;
    if (pos == words[i].size() - 1) {
      nextchar = startchar;
    } else {
      nextchar.push_back({i, pos + 1});
    }

    for (pair<int,int> c : nextchar) {

      //left
      if (st != R && y> 1 && a[x][y-1] == words[c.first][c.second] && d[x][y-1][L][c.first][c.second] == 0) {
        d[x][y-1][L][c.first][c.second] = d[x][y][st][i][pos] + 1;
        q.push({x, y-1, L, c.first, c.second});
      }
      // right
      if (st != L && y < m &&  a[x][y+1] == words[c.first][c.second] && d[x][y+1][R][c.first][c.second] == 0) {
        d[x][y+1][R][c.first][c.second] = d[x][y][st][i][pos] + 1;
        q.push({x, y+1, R, c.first, c.second});
      }
      // down
      if (x < n && a[x+1][y] == words[c.first][c.second] && d[x+1][y][M][c.first][c.second] == 0) {
     //   cout <<"sui"<<'\n';
        d[x+1][y][M][c.first][c.second] = d[x][y][st][i][pos] + 1;
        q.push({x+1, y, M, c.first, c.second});
      }
    }
  }
  cout <<"impossible\n";

  return 0;


}

#include <bits/stdc++.h>
using namespace std;

#define pii pair<int,int>
#define int long long

const int N = 1e5+10;
const int INF = 1e9+10;

int n;
int cnt = 0;

void ask(int i, int j) {
  assert(cnt < 5*n);
  cout << "? " << j+1 << " " << i+1 << endl;
  cout.flush();
  ++cnt;
}

void answer(int x) {
  cout << "! " << x << endl;
  cout.flush();
}

bool compare(int i, int j) {
  ask(i,j);
  int x; cin >> x;
  return (x==1);
}

int global_cur = 0;
int global_pos = 1;
int phi[N];

signed main() {
  cin >> n;
  if (n == 1) {
    answer(0);
    return 0;
  }
  phi[0] = 0;
  int cur = 0;
  for (int i=0; i<2*n; i++) {
    // cerr << "normal compute" << endl;
    while (cur!=0) {
      if (compare(cur, i%n)) {
        cur++;
        break;
      }
      cur = phi[cur-1];
      if (i-cur >= n) {
        answer(-1);
        return 0;
      }
    }
    if (cur == 0) {
      if (compare(cur, i%n)) cur++;
    }
    if (cur > global_pos) {
      // cerr << "kmp compute" << " " << global_cur << " " << global_pos  << " " << i << endl;
      while (global_cur!=0) {
        if (compare(global_cur, i%n)) {
          ++global_cur;
          break;
        }
        global_cur = phi[global_cur-1];
      }
      if (global_cur == 0) {
        if (compare(global_cur, i%n)) global_cur++;
      }
      phi[global_pos] = global_cur;
      global_pos++;
      if (global_pos == n) {
        answer(i - n+1);
        return 0;
      }
    }
  }
  answer(-1);
}
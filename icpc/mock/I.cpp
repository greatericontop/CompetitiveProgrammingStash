#include <bits/stdc++.h>
using namespace std;


int main() {
  int initial_p_ct, initial_u_ct;  cin >> initial_p_ct >> initial_u_ct;
  vector<int> initial_p(initial_p_ct);  vector<int> initial_u(initial_u_ct);
  for (int i = 0; i < initial_p_ct; i++) {
    cin >> initial_p[i];
  }
  for (int i = 0; i < initial_u_ct; i++) {
    cin >> initial_u[i];
  }
  set<int> initial_p_set;
  for (int x : initial_p)  initial_p_set.insert(x);
  set<int> initial_u_set;
  for (int x : initial_u)  initial_u_set.insert(x);
  int final_p_ct, final_u_ct;  cin >> final_p_ct >> final_u_ct;
  vector<int> final_p(final_p_ct);  vector<int> final_u(final_u_ct);
  for (int i = 0; i < final_p_ct; i++) {
    cin >> final_p[i];
  }
  for (int i = 0; i < final_u_ct; i++) {
    cin >> final_u[i];
  }

  int totalcost = 0;

  // UNPINNED FIRST
  {
    reverse(initial_u.begin(), initial_u.end());
    reverse(final_u.begin(), final_u.end());
    int i = 0;
    int j = 0;
    for (; i < final_u_ct; i++) {
      // advance j pointer until i is found
      while (j < initial_u_ct && initial_u[j] != final_u[i])  j++;
      if (j >= initial_u_ct) {
        // i was unmatched
        break;
      }
    }
    // i points to first NOT found
    for (; i < final_u_ct; i++) {
      int x = final_u[i];
      // cost is 1 if in pinned, 2 if not
      if (initial_p_set.find(x) != initial_p_set.end()) {
        totalcost += 1;
      } else {
        totalcost += 2;
      }
    }
  }


  {
    int i = 0;
    int j = 0;
    for (; i < final_p_ct; i++) {
      while (j < initial_p_ct && initial_p[j] != final_p[i])  j++;
      if (j >= initial_p_ct) {
        break;
      }
    }
    for (; i < final_p_ct; i++) {
      int x = final_p[i];
      if (initial_p_set.find(x) != initial_p_set.end()) {
        totalcost += 2;
      } else {
        totalcost += 1;
      }
    }
  }

  cout << totalcost << "\n";








}
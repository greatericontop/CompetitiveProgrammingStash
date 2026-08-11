#include <bits/stdc++.h>
using namespace std;


int n, m;
int top_ptr, bottom_ptr;
char grid[101][101];


void init(int N, int M) {
  n = N;
  m = M;
  top_ptr = 0;
  bottom_ptr = n-1;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      grid[i][j] = '.';
    }
  }
}


pair<int, int> internal_place_block(char type) {
  if (type == 'D') {
    // D is placed at leftmost available position in the top row
    while (true) {
      int i = top_ptr;
      int j = 0;
      while (j < m && grid[i][j] != '.') {
        j++;
      }
      if (j < m) {
        grid[i][j] = 'D';
        return {i, j};
      } else {
        top_ptr++;
      }
    }
  } else if (type == 'C') {
    // C is placed at rightmost available position in the top row
    while (true) {
      int i = top_ptr;
      int j = m-1;
      while (j >= 0 && grid[i][j] != '.') {
        j--;
      }
      if (j >= 0) {
        grid[i][j] = 'C';
        return {i, j};
      } else {
        top_ptr++;
      }
    }
  } else if (type == 'B') {
    // B is placed at leftmost available position in the bottom row
    while (true) {
      int i = bottom_ptr;
      int j = 0;
      while (j < m && grid[i][j] != '.') {
        j++;
      }
      if (j < m) {
        grid[i][j] = 'B';
        return {i, j};
      } else {
        bottom_ptr--;
      }
    }
  } else if (type == 'A') {
    // A is placed at rightmost available position in the bottom row
    while (true) {
      int i = bottom_ptr;
      int j = m-1;
      while (j >= 0 && grid[i][j] != '.') {
        j--;
      }
      if (j >= 0) {
        grid[i][j] = 'A';
        return {i, j};
      } else {
        bottom_ptr--;
      }
    }
  } else {
    assert(false);
  }
}


std::pair<int, int> receive_block(int TL, int TR, int BL, int BR) {
  pair<int, int> ans;
  if (TL == 0) {
    ans = internal_place_block('A');
  } else if (TR == 0) {
    ans = internal_place_block('B');
  } else if (BL == 0) {
    ans = internal_place_block('C');
  } else if (BR == 0) {
    ans = internal_place_block('D');
  } else {
    assert(false);
  }
  return {ans.first*2, ans.second*2};
}




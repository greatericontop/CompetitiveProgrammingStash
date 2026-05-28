#include <bits/stdc++.h>
using namespace std;


constexpr static int ITERS = (int) 3e8;


#define INT int
//#define INT int64_t


int main() {

  mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
  INT x[1024];  //small ish size to fit completely in L1
  for (int i = 0; i < 1024; i++) {
    x[i] = rng();
  }

  // Access the array in a somewhat data-dependent but fast manner
  INT accumulator = 0;  //the hope is this guy will be in a register
  INT accumulator2 = 0;
  for (int i = 0; i < ITERS; i++) {
    accumulator += x[accumulator & 1023];
    int y = accumulator;
    accumulator2 += y / x[accumulator & 1023];
  }

  cout << accumulator << endl;

}

/*  -fsanitize=undefined -fsanitize=address -fno-sanitize-recover -Wall -Werror -Wextra -Wshadow -Wfloat-equal
    -Wno-error=unused-variable -Wno-error=unused-parameter -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2 -O1  */

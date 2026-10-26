#include <bits/stdc++.h>
using namespace std;


int main() {
  string s1, op, s2, equals, s3;
  cin >> s1 >> op >> s2 >> equals >> s3;
  assert(equals == "=");  assert(op == "*" || op == "+");

  vector<string> strings = {s1, s2, s3};

  for (int i1 = 0; i1 < 3; i1++) {
    for (int i2 = i1+1; i2 < 3; i2++) {
      // swap prefixes of i1 and i2
      for (int length1 = 1; length1 < strings[i1].size(); length1++) {
        for (int length2 = 1; length2 < strings[i2].size(); length2++) {
          vector<string> strings_new = strings;
          string cutout_1 = strings[i1].substr(0, length1);
          string cutout_2 = strings[i2].substr(0, length2);
          strings_new[i1] = cutout_2 + strings[i1].substr(length1);
          strings_new[i2] = cutout_1 + strings[i2].substr(length2);
          long x = stoll(strings_new[0]), y = stoll(strings_new[1]), z = stoll(strings_new[2]);
          //fprintf(stderr, "x %ld, y %ld, z %ld\n", x, y, z);
          if (op == "+") {
            long s = x + y;
            if (s == z) {
              cout << x << " + " << y << " = " << z << "\n";
              return 0;
            }
          } else {
            __int128 p = (__int128)x * (__int128)y;
            if (p == z) {
              cout << x << " * " << y << " = " << z << "\n";
              return 0;
            }
          }
        }
      }
    }
  }
  assert(false);
}
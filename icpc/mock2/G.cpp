#include <bits/stdc++.h>
using namespace std;



using u64 = uint64_t;
using u32 = uint32_t;
class RollingHasher {
  constexpr static u64 MOD = 2305843009213693951LL;
  u64 b;
  int n;
  vector<u64> exp_b;
  vector<u64> prefix_hashes;

  static u64 modmul(u64 a, u64 b) {
    u64 l1 = (u32)a, h1 = a>>32, l2 = (u32)b, h2 = b>>32;
    u64 l = l1*l2, m = l1*h2 + l2*h1, h = h1*h2;
    u64 ret = (l&MOD) + (l>>61) + (h << 3) + (m >> 29) + (m << 35 >> 3) + 1;
    ret = (ret & MOD) + (ret >> 61);
    ret = (ret & MOD) + (ret >> 61);
    return ret-1;
  }

public:
  explicit RollingHasher(const string& s) {
    b = 67676767710111;
    //mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    //b = uniform_int_distribution<u64>(0, MOD-1)(rng);
    n = (int) s.size();
    exp_b = vector<u64>(n);
    exp_b[0] = 1;
    for (int i = 1; i < n; i++) {
      exp_b[i] = modmul(exp_b[i-1], b);
    }
    prefix_hashes = vector<u64>(n);
    prefix_hashes[0] = s[0];
    for (int i = 1; i < n; i++) {
      prefix_hashes[i] = (prefix_hashes[i-1] + modmul(exp_b[i], s[i])) % MOD;
    }
  }

  // inclusive
  u64 hash(int l, int r) {
    u64 raw_h = (MOD + prefix_hashes[r] - (l > 0 ? prefix_hashes[l-1] : 0)) % MOD;
    raw_h = modmul(raw_h, exp_b[n-1-l]);
    return raw_h;
  }
};



int main() {
  string s1, s2;  cin >> s1 >> s2;
  int n = s1.size(), m = s2.size();
  while (s1.size() < max(n, m))  s1 += '.';
  while (s2.size() < max(n, m))  s2 += '.';
  RollingHasher rh1(s1);
  RollingHasher rh2(s2);

  set<string> answers;

  for (int i = 0; i < n; i++) {
    for (int j = i+2; j < n; j++) {
      u64 hash1 = rh1.hash(i, j);
      bool found = false;
      for (int i2 = 0; i2 < m; i2++) {
        int j2 = i2 + j - i;
        if (j2 >= m)  break;
        if (rh2.hash(i2, j2) == hash1) {
          found = true;
          break;
        }
      }

      if (found) {
        string substr = s1.substr(i, j-i+1);
        sort(substr.begin(), substr.end());
        //fprintf(stderr, "found substring %s\n", substr.c_str());
        answers.insert(substr);
      }
    }
  }

  cout << answers.size() << "\n";


}

#include <bits/stdc++.h>
using namespace std;






/* Note: raw construction has no checks for whether the input you give is legit! */
template <int64_t mod> struct ModInt {
  int64_t value;
  ModInt operator + (const ModInt& other) const {
    int64_t x = value + other.value;
    if (x >= mod)  x -= mod;
    return ModInt<mod>{x};
  }
  ModInt operator - (const ModInt& other) const {
    int64_t x = value - other.value;
    if (x < 0)  x += mod;
    return ModInt<mod>{x};
  }
  ModInt operator * (const ModInt& other) const {
    return ModInt<mod>{(value * other.value) % mod};
  }
  ModInt operator / (const ModInt& other) const {
    return ModInt<mod>{(value * other.inverse().value) % mod};
  }
  void operator += (const ModInt& other) {
    value += other.value;
    if (value >= mod)  value -= mod;
  }
  void operator -= (const ModInt& other) {
    value -= other.value;
    if (value < 0)  value += mod;
  }
  void operator *= (const ModInt& other) {
    value = (value * other.value) % mod;
  }
  void operator /= (const ModInt& other) {
    value = (value * other.inverse().value) % mod;
  }
  ModInt exp(int64_t e) const {
    int64_t result = 1;
    int64_t base = value;
    while (e > 0) {
      if (e & 1)  result = (result * base) % mod;
      base = (base * base) % mod;
      e >>= 1;
    }
    return ModInt<mod>{result};
  }
  ModInt inverse() const {
    return exp(mod - 2);
  }
};






int main() {
  ModInt<67> a{11}, b{20}, c{30};
  assert((a + b).value == 31);
  assert((a - b).value == 58);
  assert((a * b).value == 19);
  a += b;
  a += c;
  assert(a.value == 61);
  assert((a * a.inverse()).value == 1);
  assert((a / a).value == 1);
  assert(( ((a+b)*c - b*c) / c ).value == a.value);
  cout << "All tests passed!\n";

  return 0;
}

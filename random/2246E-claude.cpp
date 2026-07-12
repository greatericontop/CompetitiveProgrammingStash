#include <bits/stdc++.h>
using namespace std;

// Interactive: guess b.
//   send x            -> receive r = (v & x) or (v | x)
//   send m0 m1        -> receive y = m_b ^ v
//   output b
//
// I/O format assumed: plain integers, one exchange per line, flush after
// every line we print. If the official statement uses markers ("? x",
// "! b", ...), change the printf lines accordingly.

int main() {
  int t;
  if (scanf("%d", &t) != 1) return 0;

  mt19937 rng((unsigned)chrono::steady_clock::now().time_since_epoch().count());
  const unsigned FULL = (1u << 30) - 1;

  // uniform random subset of `mask` that is neither empty nor all of it
  auto randomProperSubset = [&](unsigned mask) {
    unsigned s;
    do { s = rng() & mask; } while (s == 0 || s == mask);
    return s;
  };

  while (t--) {
    // x = random mask with exactly 15 of the 30 bits set
    int pos[30];
    iota(pos, pos + 30, 0);
    shuffle(pos, pos + 30, rng);
    unsigned x = 0;
    for (int i = 0; i < 15; i++) x |= 1u << pos[i];
    unsigned notx = FULL ^ x;

    printf("%u\n", x);
    fflush(stdout);
    unsigned r;
    if (scanf("%u", &r) != 1) return 0;

    unsigned m0 = 0, m1;
    int mode;
    if (r == x) {
      // ambiguous: ty=& with v ⊇ x, or ty=| with v ⊆ x
      mode = 3;
      m1 = randomProperSubset(x) | randomProperSubset(notx);
    } else if ((r & notx) == 0) {
      // r ⊊ x  =>  ty = &, v & x = r  (v known on bits of x)
      mode = 1;
      m1 = x;
    } else if ((x & ~r) == 0) {
      // r ⊋ x  =>  ty = |, v & ~x = r & ~x  (v known outside x)
      mode = 2;
      m1 = notx;
    } else {
      mode = 1; m1 = x;   // impossible for a valid interactor
    }

    printf("%u %u\n", m0, m1);
    fflush(stdout);
    unsigned y;
    if (scanf("%u", &y) != 1) return 0;

    int b;
    if (mode == 1) {
      // b=0: y & x == r ; b=1: y & x == r ^ x
      b = ((y & x) == (r & x)) ? 0 : 1;
    } else if (mode == 2) {
      // b=0: y & ~x == r & ~x ; b=1: fully flipped there
      b = ((y & notx) == (r & notx)) ? 0 : 1;
    } else {
      auto consistent = [&](unsigned c) {
        return (c & x) == x        // c ⊇ x  (possible with ty=&)
               || (c & notx) == 0;    // c ⊆ x  (possible with ty=|)
      };
      bool i0 = consistent(y ^ m0);
      bool i1 = consistent(y ^ m1);
      if (i0 != i1) b = i1 ? 1 : 0;
      else b = rng() & 1;  // only if interactor guessed our random d
      // (prob ~2^-15; v in {0, x, 2^30-1} can
      //  never trigger this)
    }
    printf("%d\n", b);
    fflush(stdout);
  }
  return 0;
}
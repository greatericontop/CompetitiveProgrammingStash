#include <bits/stdc++.h>
using namespace std;










using ftype = double;
struct point2d {
  ftype x, y;
  point2d() {}
  point2d(ftype x, ftype y): x(x), y(y) {}
  point2d& operator += (const point2d& t) {
    x += t.x;
    y += t.y;
    return *this;
  }
  point2d& operator -= (const point2d& t) {
    x -= t.x;
    y -= t.y;
    return *this;
  }
  point2d& operator *= (ftype t) {
    x *= t;
    y *= t;
    return *this;
  }
  point2d& operator /= (ftype t) {
    x /= t;
    y /= t;
    return *this;
  }
  point2d operator + (const point2d& t) const {
    return point2d(*this) += t;
  }
  point2d operator - (const point2d& t) const {
    return point2d(*this) -= t;
  }
  point2d operator * (ftype t) const {
    return point2d(*this) *= t;
  }
  point2d operator / (ftype t) const {
    return point2d(*this) /= t;
  }
};
point2d operator * (const ftype& a, const point2d& b) {
  return b * a;
}
struct point3d {
  ftype x, y, z;
  point3d() {}
  point3d(ftype x, ftype y, ftype z): x(x), y(y), z(z) {}
  point3d& operator += (const point3d& t) {
    x += t.x;
    y += t.y;
    z += t.z;
    return *this;
  }
  point3d& operator -= (const point3d& t) {
    x -= t.x;
    y -= t.y;
    z -= t.z;
    return *this;
  }
  point3d& operator *= (ftype t) {
    x *= t;
    y *= t;
    z *= t;
    return *this;
  }
  point3d& operator /= (ftype t) {
    x /= t;
    y /= t;
    z /= t;
    return *this;
  }
  point3d operator + (const point3d& t) const {
    return point3d(*this) += t;
  }
  point3d operator - (const point3d& t) const {
    return point3d(*this) -= t;
  }
  point3d operator * (ftype t) const {
    return point3d(*this) *= t;
  }
  point3d operator / (ftype t) const {
    return point3d(*this) /= t;
  }
};
point3d operator * (const ftype& a, const point3d& b) {
  return b * a;
}
ftype dotprod(const point2d& a, const point2d& b) {
  return a.x * b.x + a.y * b.y;
}
ftype lengthsquared(const point2d& p) {
  return dotprod(p, p);
}
double length(const point2d& p) {
  return sqrt(lengthsquared(p));
}
double projected_length(const point2d& p, const point2d& onto) {
  return dotprod(p, onto) / length(onto);
}
double angle(const point2d& a, const point2d& b) {
  return acos(dotprod(a, b) / length(a) / length(b));
}
point3d crossprod(const point3d& a, const point3d& b) {
  return point3d(a.y * b.z - a.z * b.y,
                 a.z * b.x - a.x * b.z,
                 a.x * b.y - a.y * b.x);
}
ftype crossprod2(const point2d& a, const point2d& b) {
  return a.x * b.y - a.y * b.x;
}
point2d intersect_lines(const point2d& a1, const point2d& d1, const point2d& a2, const point2d& d2) {
  ftype t = crossprod2(a2 - a1, d2) / crossprod2(d1, d2);
  return a1 + t * d1;
}





int main() {
  return 0;
}

/*  -fsanitize=undefined -fsanitize=address -fno-sanitize-recover -Wall -Werror -Wextra -Wshadow -Wfloat-equal
    -Wno-error=unused-variable -Wno-error=unused-parameter -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2 -O1  */

/*
 * This code contains the use of comments! You can identify them with the "//" or "/*" symbols.
 * Comments are used to explain the code and make it easier to understand.
 * They are ignored by the compiler and do not affect the execution of the program.
 * In this code, comments are used to explain the purpose of the code, the input and output format, and the logic behind the solution.
 * Unlike the 3 lines shown above, the comments in this code were lovingly hand-inserted and not a result of AI generated text.
 * Thanks to sc3developer <3 for inspiring this message and for being a great mentor.
 */

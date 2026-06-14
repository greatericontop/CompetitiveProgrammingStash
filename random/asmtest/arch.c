#include <stdio.h>
#include <stdint.h>

int64_t add(int32_t a, int32_t b);

int main() {
  int32_t a = -1;
  int32_t b = -2;
  printf("add(%d, %d) = %ld\n", a, b, add(a, b));

  return 0;
}
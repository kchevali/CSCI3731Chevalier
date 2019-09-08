#include <cstdio>
#include "swap.h"

int main(int argc, char** argv) {
  char a, b;
  printf("Two chars: ");
  scanf("%c %c", &a, &b);              // input chars
  swap(a, b);                          // swaps in place
  printf("  Swapped: %c %c\n", a, b);  // output chars
}

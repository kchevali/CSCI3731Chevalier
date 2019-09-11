#include <cstdio>
#include "swap.h"

/*
Kevin Chevalier
September 7, 2019
CSCI 3731
Homework 2
8b) Swap two inputs
*/

int main(int argc, char** argv) {
  char a, b;
  printf("Two chars: ");
  scanf("%c %c", &a, &b);              // input chars
  swap(&a, &b);                        // swaps in place
  printf("  Swapped: %c %c\n", a, b);  // output chars
}

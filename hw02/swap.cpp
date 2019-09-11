#include "swap.h"
// swaps two chars
void swap(char* a, char* b) {
  char temp = *a;
  *a = *b;
  *b = temp;
}

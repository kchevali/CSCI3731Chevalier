/*
Kevin Chevalier
August 28, 2019
CSCI 3731
Homework 1

Run:
cd "/Users/kevin/Documents/Repos/CSCI3731Chevalier/hw01/"
g++ bitbybit.cpp methods.cpp -o bitbybit.exe && ./bitbybit.exe
*/
#include <cstdio>
#include "methods.h"
#define fpp(b) for (i = 0; i < b; i++)
#define fmm(b) for (i = b - 1; i >= 0; i--)

int main(int argc, char** argv) {
  int n, res;
  res = scanf("%d\n", &n);
  while (n != 0) {
    int i, pos1, pos2, bits[32];  // 0=0,?=1,1=2
    fpp(32) bits[i] = 1;
    fpp(n) {
      char str[5];
      res = scanf("%s %d", str, &pos1);
      char ch = str[0];

      if (ch == 'C')
        bits[pos1] = 0;
      else if (ch == 'S')
        bits[pos1] = 2;
      else {
        res = scanf("%d", &pos2);

        if (ch == 'O')
          max(bits[pos1], bits[pos2]);
        else
          min(bits[pos1], bits[pos2]);
      }
    }
    fmm(32) { printf("%c", bits[i] != 1 ? (bits[i] == 2 ? '1' : '0') : '?'); }
    printf("\n");
    res = scanf("%d", &n);
  }
  return 0;
}

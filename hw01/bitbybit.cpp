/*
Kevin Chevalier
August 28, 2019
CSCI 3731
Homework 1

Problem Description: https://open.kattis.com/problems/bitbybit
Status: Accepted @ 0.00s

Compile & Run:
cd "/Users/kevin/Documents/Repos/CSCI3731Chevalier/hw01/"
g++ bitbybit.cpp maxmin.cpp -o bitbybit.exe && ./bitbybit.exe
*/

#include <cstdio>
#include "maxmin.h"  //max,min methods
#define fpp(b) for (i = 0; i < b; i++)
#define fmm(b) for (i = b - 1; i >= 0; i--)

int main(int argc, char** argv) {
  int n, res;
  printf("Valid Instructions: (CLEAR, SET, OR, AND)\n");

  printf("Number of Instructions:");
  res = scanf("%d", &n);  // number of instructions
  while (n != 0) {        // exit if 0
    int i;                // index - for
    int pos1, pos2;       // bit index for instr
    int bits[32];         // 32 bit reg. //code: 0=0,?=1,1=2
    fpp(32) bits[i] = 1;  // set all: ?
    fpp(n) {
      char str[5];  // instr name
      printf("Instruction:");
      res = scanf("%s", str);  // instr name
      printf("First Index:");
      res = scanf("%d", &pos1);  // reg index1
      char ch = str[0];

      if (ch == 'C')  // Clear instr
        bits[pos1] = 0;
      else if (ch == 'S')  // Set instr
        bits[pos1] = 2;
      else {
        printf("Second Index:");
        res = scanf("%d", &pos2);  // reg index2

        if (ch == 'O')  // Or instr
          max(bits[pos1], bits[pos2]);
        else  // And instr
          min(bits[pos1], bits[pos2]);
      }
    }

    // OUTPUT
    printf("Register: ");
    fmm(32) { printf("%c", bits[i] != 1 ? (bits[i] == 2 ? '1' : '0') : '?'); }
    printf("\n");

    // RESTART
    printf("\nNumber of Instructions:");
    res = scanf("%d", &n);
  }
  // DONE
  return 0;
}

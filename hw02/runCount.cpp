/*
Kevin Chevalier
September 7, 2019
CSCI 3731
Homework 2
8a) Print number of times the program ran
*/

#include <cstdio>

int main(int argc, char **argv) {
  int num = 1;                         // default output
  FILE *file = fopen("num.txt", "r");  // read only file
  if (file) {                          // found file
    fscanf(file, "%d", &num);
    num = num < 1 ? 1 : num;  // ensures no shenanigans
    fclose(file);
  }
  printf("%d\n", num);

  // open file and check if exists
  if ((file = fopen("num.txt", "w")) == NULL) return 1;
  fprintf(file, "%d", num + 1);  // overwrite with inc value
  fclose(file);
  return 0;
}

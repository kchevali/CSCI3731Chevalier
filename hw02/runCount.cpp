/*
Kevin Chevalier
September 7, 2019
CSCI 3731
Homework 2
8a) Print number of times the program ran
*/

#include <cstdio>

int main(int argc, char **argv) {
  int ch = 0, num = 0;
  FILE *file = fopen("num.txt", "r");  // read only file
  if (file) {                          // found file
    // scan for digits and build number
    while ((ch = getc(file)) >= '0' && ch <= '9') num = num * 10 + ch - '0';
    fclose(file);  // close
  }
  printf("%d\n", ++num);  // inc and print num
  if ((file = fopen("num.txt", "w")) == NULL) return 1;
  // open to file and check file exists
  fprintf(file, "%d", num);  // overwrite
  fclose(file);              // close
  return 0;
}

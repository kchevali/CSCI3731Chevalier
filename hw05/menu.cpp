#include "menu.h"
#include <cstdio>

const int menu_count = 7;
char items[menu_count][20] = {
    "Grayscale Image", "Invert Image", "Blurry Effect", "Flip Horizontal",
    "Flip Vertical",   "Rotate Image", "Reset Image"};

// CREATE MENU TEXT
void show_menu() {
  printf("\nMENU (Press Enter when done)\n");
  for (int i = 1; i <= menu_count; i++) {
    printf("%d. %s\n", i, items[i - 1]);
  }
}

// ACCEPT USER INPUT AND VALIDATE
// RETURN MENU OPTION NUMBER
int input_menu() {
  char in, temp;
  printf("\nEntry:");

  // READ SINGLE INT
  scanf("%c", &in);
  if (in == '\n') return 0;

  // CLEAR LINE
  do {
    scanf("%c", &temp);
  } while (temp != '\n');

  int item = in - '0';
  if (item < 1 || item > menu_count) {
    printf("Invalid entry! Please try again.\n\n");
    return input_menu();
  }
  return item;
}

#include <cstdio>
#include "img.h"
#include "menu.h"

/*
Kevin Chevalier
September 30, 2019
CSCI 3731
Homework 5
Use Lib to Read + Write PPM file to JPEG

Doc:https://github.com/kornelski/libjpeg/blob/master/libjpeg.doc
*/
int main(int argc, char** argv) {
  int width = 0, height = 0;
  const char* inputFile = "test.ppm";

  // reads .ppm file and returns pixels, width,height
  int** pixels = readPPM(inputFile, &width, &height);
  if (pixels == NULL) {  // file not found
    printf("File not found: %s\n", inputFile);
    return 1;
  }

  printf("Welcome to JPEG Editor!\n");
  int option;
  do {
    show_menu();
    option = input_menu();
    switch (option) {
      // GRAY SCALE
      case 1:
        printf("Set image to black and white.\n");
        toBW(pixels, width, height);
        break;

      // INVERT PIXELS
      case 2:
        printf("Inverted image.\n");
        invert(pixels, width, height);
        break;

      // BLURRY EFFECT
      case 3:
        printf("Set blurry effect to image.\n");
        setPixelSize(pixels, width, height, 30);
        break;

      // FLIP IMAGE HORIZONTAL
      case 4:
        printf("Flipped image.\n");
        flipHorizontal(pixels, width, height);  // flip x coords
        break;
      // FLIP IMAGE VERTICAL
      case 5:
        printf("Flipped image.\n");
        flipVertical(pixels, width, height);  // flip y coords
        break;
      // ROTATE IMAGE
      case 6:
        printf("Rotating image.\n");
        pixels = rotate(pixels, &width, &height);
        break;
      // RESET IMAGE
      case 7:
        printf("Resetting all changes.\n");
        closeImage(pixels);
        pixels = readPPM(inputFile, &width, &height);
        break;
    }
  } while (option != 0);

  const char* outputFile = "output.jpeg";
  // writes pixels to file
  printf("Saving Changes.\n");
  writeJPEG(outputFile, pixels, width, height, 100);

  // clear pixels in heap
  closeImage(pixels);
}

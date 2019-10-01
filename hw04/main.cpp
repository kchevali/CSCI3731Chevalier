#include <cstdio>
#include "ppm.h"

/*
Kevin Chevalier
September 23, 2019
CSCI 3731
Homework 4
Read + Write PPM file with 2D arrays

EC: Manipulate Image
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
  // invert(pixels, width, height);            // inverts pixels 0<->225
  // setPixelSize(pixels, width, height, 30);  // blurry effect
  // toBW(pixels, width, height);              // replace color with brightness
  // flipVertical(pixels, width, height);      // flip y coords
  // flipHorizontal(pixels, width, height);    // flip x coords

  const char* outputFile = "output.ppm";
  // writes pixels to file
  writePPM(outputFile, pixels, width, height);

  // clear pixels in heap
  delete[] pixels[0];  // delete content array
  delete[] pixels;     // delete point arrays
  pixels = NULL;       // remove ref
}

#include <cstdio>
#include "ppm.h"

/*
Kevin Chevalier
September 16, 2019
CSCI 3731
Homework 3
Read + Write PPM file

EC: Manipulate Image
*/
int main(int argc, char** argv) {
  int width = 0, height = 0, maxPixel = 255;
  const char* inputFile = (char*)"test.ppm";

  // reads .ppm file and returns pixels, width,height and maxPixel size
  unsigned char* pixels = readPPM(inputFile, &width, &height, &maxPixel);
  if (pixels == NULL) {  // file not found
    printf("File not found: %s\n", inputFile);
    return 1;
  }
  invert(pixels, width, height, maxPixel);  // inverts pixels 0<->225
  setPixelSize(pixels, width, height, 8);   // blurry effect
  toBW(pixels, width, height);              // replace color with brightness

  const char* outputFile = (char*)"output.ppm";
  // writes pixels to file
  writePPM(outputFile, pixels, width, height, maxPixel);

  // clear pixels in heap
  delete[] pixels;
  pixels = NULL;
}

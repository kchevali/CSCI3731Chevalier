#include "ppm.h"
#include <cstdio>

// reads pixels from file name and returns width, height and maxPixel as well
unsigned char* readPPM(const char* fileName, int* width, int* height,
                       int* maxPixel) {
  FILE* ptr;
  ptr = fopen(fileName, "rb");  // r for read, b for binary

  char id[2];
  fscanf(ptr, "%c%c\n", id, &id[1]);  // read identifier
  if (id[0] != 'P' && id[1] != '6') return NULL;

  fscanf(ptr, "%d %d\n%d\n", width, height, maxPixel);
  // number of byte values
  const int length = *width * *height * 3;
  unsigned char* pixels = new unsigned char[length];  // create pixels in heap
  fread(pixels, sizeof(pixels), length, ptr);         // read file
  fclose(ptr);
  return pixels;
}

// write pixels to a named file
void writePPM(const char* fileName, const unsigned char* pixels,
              const int width, const int height, const int maxPixel) {
  FILE* ptr;
  if ((ptr = fopen(fileName, "wb")) == NULL) return;
  fwrite(pixels, sizeof(pixels), height * width * 3, ptr);
  fclose(ptr);
}

// calculate brightness of each pixel and set RGB to same value
void toBW(unsigned char* pixels, const int width, const int height) {
  // (0.21 × R) + (0.72 × G) + (0.07 × B)
  for (int i = 2; i < height * width * 3; i += 3) {  // iterate pixels
    pixels[i] =
        (int)(0.21 * pixels[i - 2] + 0.72 * pixels[i - 1] + 0.07 * pixels[i]);
    pixels[i - 2] = pixels[i - 1] = pixels[i];
  }
}

// invert darkness of pixels //0<->255
void invert(unsigned char* pixels, const int width, const int height,
            const int maxPixel) {
  for (int i = 2; i < height * width * 3; i += 3) {
    pixels[i] = 3 * maxPixel - pixels[i - 2] - pixels[i - 1] - pixels[i];
    pixels[i - 2] = pixels[i - 1] = pixels[i];
  }
}

// blurrly effect for pixels
void setPixelSize(unsigned char* pixels, const int width, const int height,
                  const int pixelSize) {
  const int newWidth = width / pixelSize + 1,
            newHeight = height / pixelSize + 1, length = width * height * 3;
  for (int i = 0; i < newHeight; i++) {
    for (int j = 0; j < newWidth; j++) {
      // start averaging pixels in area
      int avgR = 0, avgG = 0, avgB = 0;
      for (int k = 0; k < pixelSize; k++) {    // height
        for (int m = 0; m < pixelSize; m++) {  // width
          int index = (m + j * pixelSize + (k + i * pixelSize) * width) * 3;
          if (index >= length) continue;
          avgR += pixels[index];
          avgG += pixels[index + 1];
          avgB += pixels[index + 2];
        }
      }
      avgR /= pixelSize * pixelSize;
      avgG /= pixelSize * pixelSize;
      avgB /= pixelSize * pixelSize;
      // store pixels
      for (int k = 0; k < pixelSize; k++) {    // height
        for (int m = 0; m < pixelSize; m++) {  // width
          int index = (m + j * pixelSize + (k + i * pixelSize) * width) * 3;
          if (index >= length) continue;
          pixels[index] = avgR;
          pixels[index + 1] = avgR;
          pixels[index + 2] = avgR;
        }
      }
    }
  }
}

#include "ppm.h"
#include <cstdio>

// reads pixels from file name and returns width, height and maxPixel as well
int** readPPM(const char* fileName, int* width, int* height) {
  FILE* file;
  file = fopen(fileName, "rb");  // r for read, b for binary

  char id[2];
  fscanf(file, "%c%c\n", id, &id[1]);  // read identifier
  if (id[0] != 'P' && id[1] != '6') return NULL;
  int maxPixel;
  fscanf(file, "%d %d\n%d\n", width, height, &maxPixel);
  // number of byte values
  const int byteLength = *width * *height * 3;
  unsigned char bytePixels[byteLength];  // create pixels in stack
  fread(bytePixels, sizeof(*bytePixels), byteLength, file);  // read file
  fclose(file);

  int** pixels = new int*[*height];     // create array of pointers
  *pixels = new int[*width * *height];  // create array of ints
  for (int i = 1; i < *height; i++) pixels[i] = pixels[i - 1] + *width;
  unsigned char* ptr = (unsigned char*)*pixels;  // point to first byte
  for (int i = 0, j = 0; i < byteLength; i++, j++)
    ptr[(j % 4) == 0 ? ++j : j] =
        bytePixels[i];  // iterate bytes, but skip every 4
  return pixels;
}

// write pixels to a named file
void writePPM(const char* fileName, int** pixels, const int width,
              const int height) {
  FILE* file;
  if ((file = fopen(fileName, "wb")) == NULL) return;

  const int byteLength = width * height * 3;
  fprintf(file, "P6\n%d %d\n255\n", width, height);  // header
  unsigned char pixelBytes[byteLength];
  unsigned char* ptr = (unsigned char*)*pixels;  // first byte
  for (int i = 0, j = 0; i < byteLength; i++, j++)
    pixelBytes[i] =
        ptr[(j % 4) == 0 ? ++j : j];  // iterate bytes, but skip every 4
  fwrite(pixelBytes, sizeof(*pixelBytes), byteLength, file);  // to file
  fclose(file);
}

// calculate brightness of each pixel and set RGB to same value
void toBW(int** pixels, const int width, const int height) {
  // (0.21 × R) + (0.72 × G) + (0.07 × B)
  for (int i = 0; i < height; i++) {  // iterate pixels
    for (int j = 0; j < width; j++) {
      char* ptr = (char*)&pixels[i][j];
      ptr[3] = ptr[2] = ptr[1] =
          (0.21 * ptr[1] + 0.72 * ptr[2] + 0.07 * ptr[3]);
    }
  }
}

// invert darkness of pixels //0<->255
void invert(int** pixels, const int width, const int height) {
  for (int i = 0; i < height; i++) {  // iterate pixels
    for (int j = 0; j < width; j++) {
      char* ptr = (char*)&pixels[i][j];  // first byte of int
      ptr[1] = 255 - ptr[1];             // invert
      ptr[2] = 255 - ptr[2];
      ptr[3] = 255 - ptr[3];
    }
  }
}

// blurrly effect for pixels
void setPixelSize(int** pixels, const int width, const int height,
                  const int pixelSize) {
  const int newWidth = width / pixelSize + 1,
            newHeight = height / pixelSize + 1;
  for (int i = 0; i < newHeight; i++) {
    for (int j = 0; j < newWidth; j++) {
      // start averaging pixels in area
      int avgR = 0, avgG = 0, avgB = 0;
      for (int k = 0; k < pixelSize; k++) {    // height
        for (int m = 0; m < pixelSize; m++) {  // width
          int y = k + i * pixelSize;
          int x = m + j * pixelSize;
          char* ptr = (char*)&pixels[y][x];         // first byte of int
          if (x >= width || y >= height) continue;  // skip out of bounds
          avgR += ptr[1];
          avgG += ptr[2];
          avgB += ptr[3];
        }
      }
      avgR /= pixelSize * pixelSize;
      avgG /= pixelSize * pixelSize;
      avgB /= pixelSize * pixelSize;
      // store pixels
      for (int k = 0; k < pixelSize; k++) {    // height
        for (int m = 0; m < pixelSize; m++) {  // width
          int y = k + i * pixelSize;
          int x = m + j * pixelSize;
          char* ptr = (char*)&pixels[y][x];         // first byte of int
          if (x >= width || y >= height) continue;  // skip out of bounds
          ptr[1] = avgR;
          ptr[2] = avgG;
          ptr[3] = avgB;
        }
      }
    }
  }
}

// Standard Swap method
void swap(int* a, int* b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

void flipHorizontal(int** pixels, const int width, const int height) {
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width / 2; j++) {
      swap(&pixels[i][j], &pixels[i][height - j - 1]);  // swap opposing y
                                                        // coords
    }
  }
}
void flipVertical(int** pixels, const int width, const int height) {
  for (int i = 0; i < height / 2; i++) {
    for (int j = 0; j < width; j++) {
      swap(&pixels[i][j], &pixels[width - i - 1][j]);  // swap opposing x coords
    }
  }
}

#ifndef PPM_H
#define PPM_H

int** readPPM(const char* fileName, int* width, int* height);
void writePPM(const char* fileName, int** pixels, const int width,
              const int height);
void toBW(int** pixels, const int width, const int height);
void invert(int** pixels, const int width, const int height);
void setPixelSize(int** pixels, const int width, const int height,
                  const int pixelSize);
void swap(int* a, int* b);
void flipHorizontal(int** pixels, const int width, const int height);
void flipVertical(int** pixels, const int width, const int height);
#endif

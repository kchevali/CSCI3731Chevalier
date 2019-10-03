#ifndef IMG_H
#define IMG_H

int** create2DArray(const int width, const int height);
void closeImage(int** pixels);
int** readPPM(const char* fileName, int* width, int* height);
void writePPM(const char* fileName, int** pixels, const int width,
              const int height);
void writeJPEG(const char* fileName, int** pixels, const int width,
               const int height, const int quality);
void toBW(int** pixels, const int width, const int height);
void invert(int** pixels, const int width, const int height);
void setPixelSize(int** pixels, const int width, const int height,
                  const int pixelSize);
void swap(int* a, int* b);
void flipHorizontal(int** pixels, const int width, const int height);
void flipVertical(int** pixels, const int width, const int height);
int** rotate(int** pixels, int* width, int* height);
#endif

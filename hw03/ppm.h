#ifndef PPM_H
#define PPM_H

unsigned char* readPPM(const char* fileName, int* width, int* height,
                       int* maxPixel);
void writePPM(const char* fileName, const unsigned char* pixels,
              const int width, const int height, const int maxPixel);
void toBW(unsigned char* pixels, const int width, const int height);
void invert(unsigned char* pixels, const int width, const int height,
            const int maxPixel);
void setPixelSize(unsigned char* pixels, const int width, const int height,
                  const int pixelSize);
#endif

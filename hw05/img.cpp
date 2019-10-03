#include "img.h"
#include <cstdio>
#include "jpeglib.h"

int** create2DArray(const int width, const int height) {
  int** pixels = new int*[height];    // [*int]
  *pixels = new int[width * height];  // [int]
  for (int i = 1; i < height; i++) pixels[i] = pixels[i - 1] + width;
  return pixels;
}

void closeImage(int** pixels) {
  delete[] pixels[0];
  delete[] pixels;
  pixels = NULL;
}

// reads pixels from file name and returns width, height and maxPixel as well
int** readPPM(const char* fileName, int* width, int* height) {
  // OPEN FILE
  FILE* file;
  file = fopen(fileName, "rb");  // r - read, b - binary

  // IMAGE HEADER
  char id[2];
  fscanf(file, "%c%c\n", id, &id[1]);  // read identifier
  if (id[0] != 'P' && id[1] != '6') return NULL;
  int maxPixel;
  fscanf(file, "%d %d\n%d\n", width, height, &maxPixel);

  // READ BYTES
  const int byteLength = *width * *height * 3;
  unsigned char bytePixels[byteLength];  // create pixels in stack
  fread(bytePixels, sizeof(*bytePixels), byteLength, file);  // read file
  fclose(file);

  // CONVERT TO INT[][]
  int** pixels = create2DArray(*width, *height);
  unsigned char* ptr = (unsigned char*)*pixels;
  for (int i = 0, j = 0; i < byteLength; i++, j++)
    ptr[(j % 4) == 0 ? ++j : j] =
        bytePixels[i];  // iterate bytes, but skip every 4
  return pixels;
}

void writeJPEG(const char* fileName, int** pixels, const int width,
               const int height, const int quality) {
  // OPEN FILE
  FILE* file;
  if ((file = fopen(fileName, "wb")) == NULL) {
    fprintf(stderr, "can't open %s\n", fileName);
    return;
  }

  // CONVERT TO CHAR[]
  const int byteLength = width * height * 3;
  unsigned char pixelBytes[byteLength];
  unsigned char* ptr = (unsigned char*)*pixels;  // first byte
  for (int i = 0, j = 0; i < byteLength; i++, j++)
    pixelBytes[i] =
        ptr[(j % 4) == 0 ? ++j : j];  // iterate bytes, but skip every 4

  // JPEG SETUP
  struct jpeg_compress_struct cinfo;
  struct jpeg_error_mgr jerr;

  JSAMPROW row_pointer[1];
  int row_stride;
  cinfo.err = jpeg_std_error(&jerr);
  jpeg_create_compress(&cinfo);

  jpeg_stdio_dest(&cinfo, file);
  cinfo.image_width = width;
  cinfo.image_height = height;
  cinfo.input_components = 3;
  cinfo.in_color_space = JCS_RGB;
  jpeg_set_defaults(&cinfo);
  jpeg_set_quality(&cinfo, quality, TRUE);
  jpeg_start_compress(&cinfo, TRUE);
  row_stride = width * 3;

  // READ BYTES
  while (cinfo.next_scanline < cinfo.image_height) {
    row_pointer[0] = &pixelBytes[cinfo.next_scanline * row_stride];
    (void)jpeg_write_scanlines(&cinfo, row_pointer, 1);
  }

  // CLOSE
  jpeg_finish_compress(&cinfo);
  fclose(file);
  jpeg_destroy_compress(&cinfo);
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
      swap(&pixels[i][j], &pixels[i][width - j - 1]);  // swap opposing y
                                                       // coords
    }
  }
}
void flipVertical(int** pixels, const int width, const int height) {
  for (int i = 0; i < height / 2; i++) {
    for (int j = 0; j < width; j++) {
      swap(&pixels[i][j],
           &pixels[height - i - 1][j]);  // swap opposing x coords
    }
  }
}

int** rotate(int** pixels, int* width, int* height) {
  int** rotPixels = create2DArray(*height, *width);
  for (int i = 0; i < *height; i++) {
    for (int j = 0; j < *width; j++) {
      rotPixels[j][*width - i - 1] = pixels[i][j];
    }
  }
  closeImage(pixels);
  swap(width, height);
  return rotPixels;
}

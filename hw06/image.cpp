#include "image.h"
#include <math.h>
#include <fstream>
#include <iostream>
#include <string>
#include "jpeglib.h"

// create image and fill
Image::Image(const std::string fileName, const int width, const int height,
             const int fill) {
  this->fileName = fileName;
  this->width = width;
  this->height = height;

  // create pixels
  pixels = new int*[height];            // [*int]
  pixels[0] = new int[width * height];  // [int]

  // fill
  for (int i = 1; i < height; i++) pixels[i] = pixels[i - 1] + width;
  for (int i = 0; i < width * height; i++) (*pixels)[i] = fill;
}

// save image
void Image::write(const int quality) const {
  // OPEN FILE
  FILE* file;
  if ((file = fopen(fileName.c_str(), "wb")) == NULL) {
    std::cout << "Error: cannot find file" << std::endl;
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

// draw a line to the image between any two points
void Image::drawLine(std::pair<double, double> a, std::pair<double, double> b) {
  // increasing order a-> b
  if (a > b) std::swap(a, b);

  // get coordinates
  double x1, y1, x2, y2;
  std::tie(x1, y1) = a;
  std::tie(x2, y2) = b;

  // draw vertical line
  if (fabs(x1 - x2) < 1e-6) {
    for (; y1 < y2; y1 += 1.0) {
      int currX = (int)(width / 2 + x1), currY = (int)(height / 2 + y1);
      pixels[currY][currX] = 0xFFFFFF00;  // white
    }
    return;
  }

  // draw any other line
  double m = (y1 - y2) / (x1 - x2);
  double yint = y1 - m * x1;
  for (; x1 < x2; x1 += 0.01) {
    y1 = m * x1 + yint;
    int currX = (int)(width / 2 + x1), currY = (int)(height / 2 + y1);
    pixels[currY][currX] = 0xFFFFFF00;  // white
  }
}

// clear heap pixels
Image::~Image() {
  delete[] pixels[0];
  delete[] pixels;
  this->pixels = NULL;
}

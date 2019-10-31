#include "image.h"
#include <math.h>
#include <fstream>
#include <iostream>
#include <string>
#include <tuple>
#include "jpeglib.h"

// read file
Image::Image(const std::string fileName) : pixels(nullptr) {
  readPPM(fileName);
}

//empty
Image::Image() : pixels(nullptr) {
  width = 0;
  height = 0;
}

//empty with size
Image::Image(int width, int height) : pixels(createArray(width, height)) {
  this->width = width;
  this->height = height;
}

//read ppm file from name
void Image::readPPM(const std::string fileName) {
  //init
  std::ifstream in(fileName);

  //header
  std::string p6;
  int maxPixel;
  char dumbByte;
  in >> p6 >> width >> height >> maxPixel;
  in.read(&dumbByte, 1);

  //delete pixels if reading again
  deletePixels();
  // create pixels
  pixels = createArray(width, height);

  // read bytes in line
  const int byteLength = width * height * 3;
  char bytePixels[byteLength];  // create pixels in stack
  in.read(bytePixels, byteLength);
  in.close();

  //move bytes into int
  char* ptr = (char*)*pixels;  // point to first byte
  for (int i = 0, j = 0; i < byteLength; i++, j++)
    ptr[(j % 4) == 0 ? ++j : j] =
        bytePixels[i];  // iterate bytes, but skip every 4
}

// write pixels to a named file
void Image::writePPM(const std::string fileName) const {
  if (!verifyWrite()) return;//check empty

  //init
  std::ofstream out(fileName);

  //header
  out << "P6\n" << width << " " << height << "\n255\n";

  //int data to bytes
  const int byteLength = width * height * 3;
  char bytePixels[byteLength];
  unsigned char* ptr = (unsigned char*)*pixels;  // first byte
  for (int i = 0, j = 0; i < byteLength; i++, j++)
    bytePixels[i] =
        ptr[(j % 4) == 0 ? ++j : j];  // iterate bytes, but skip every 4

  // to file
  out.write(bytePixels, byteLength); 
  out.close();
}

// save image
void Image::writeJPEG(const std::string fileName, const int quality) const {
  if (!verifyWrite()) return;
  // OPEN FILE
  FILE* file;
  if ((file = fopen(fileName.c_str(), "wb")) == NULL) {
    std::cerr << "Error: cannot find file" << std::endl;
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

//fill array with shade of gray
void Image::fill(int shade) {
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      setPixel(j, i, shade, shade, shade);
    }
  }
}

//set rgb at coord
void Image::setPixel(int x, int y, int r, int g, int b) {
  char* pixel = (char*)(&pixels[x][y]);
  pixel[1] = r;
  pixel[2] = g;
  pixel[3] = b;
}

//setters
int Image::getWidth() const { return width; }
int Image::getHeight() const { return height; }

bool Image::empty() const { return pixels == nullptr; }

//check if image is empty
bool Image::verifyWrite() const {
  if (pixels == nullptr) {
    std::cerr << "No image to write!" << std::endl;
    return false;
  }
  return true;
}

//delete image
void Image::deletePixels() {
  if (pixels != nullptr) {
    delete[] pixels[0];
    delete[] pixels;
    pixels = nullptr;
  }
}

//create array to store image
int** Image::createArray(int w, int h) const {
  int** p = new int*[h];  // [*int]
  p[0] = new int[w * h];  // [int]
  for (int i = 1; i < h; i++) p[i] = p[i - 1] + w;
  return p;
}

//rip out the guts and keep the good stuff
void Image::move(Image& that) {
  pixels = that.pixels;
  that.pixels = nullptr;

  width = that.width;
  height = that.height;
}

//copy properties
void Image::copy(const Image& that) {
  width = that.width;
  height = that.height;
  pixels = createArray(width, height);
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      pixels[i][j] = that.pixels[i][j];
    }
  }
}

// clear heap pixels
Image::~Image() { deletePixels(); }

// copy
void Image::operator=(const Image& that) { copy(that); }
Image::Image(const Image& that) { copy(that); }

// move
Image::Image(Image&& that) { move(that); }
void Image::operator=(Image&& that) {
  deletePixels();
  move(that);
}
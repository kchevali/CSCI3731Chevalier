#ifndef IMAGE_H
#define IMAGE_H
#include <string>

class Image {
 public:
  Image();
  Image(const std::string fileName);
  Image(int width, int height);
  void readPPM(const std::string fileName);
  void writePPM(const std::string fileName) const;
  void writeJPEG(const std::string fileName, const int quality) const;
  void setPixel(int x, int y, int r, int g, int b);
  int getWidth() const;
  int getHeight() const;
  void fill(int shade);
  bool empty() const;
  void copy(const Image& that);
  virtual ~Image();
  Image(const Image& that);
  Image(Image&& that);
  void operator=(const Image& that);
  void operator=(Image&& that);

 private:
  int** pixels;
  int width, height;

  void move(Image& that);
  int** createArray(int width, int height) const;
  void deletePixels();
  bool verifyWrite() const;
};
#endif

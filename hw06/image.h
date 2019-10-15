#ifndef IMAGE_H
#define IMAGE_H
#include <string>

class Image {
 public:
  Image(const std::string fileName, const int width, const int height,
        const int fill);
  void closeImage();
  void write(const int quality) const;
  void drawLine(std::pair<double, double> a, std::pair<double, double> b);
  virtual ~Image();

 private:
  int** pixels;
  int width, height;
  std::string fileName;
};
#endif

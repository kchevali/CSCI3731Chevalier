#include "main.h"
#include <math.h>
#include <cstdio>
#include <iostream>
#include <string>
#include "image.h"

/*
Kevin Chevalier
October 14, 2019
CSCI 3731
Homework 8
Create and Test Image Class
*/

int main(int argc, char** argv) {
  // Test Read and Write
  Image img("test.ppm");
  img.writePPM("output.ppm");
  img.writeJPEG("output.jpeg", 100);

  // The Good Stuff
  Image canvas = Image(360, 360);
  // canvas.fill(51);

  //determine if sequence diverges
  const int max = 1000;

  //all pixels
  for (int i = 0; i < canvas.getHeight(); i++) {
    for (int j = 0; j < canvas.getWidth(); j++) {

      //map coord to zoom
      double a = map(j, 0, canvas.getWidth(), -1.5, 1.5);
      double b = map(i, 0, canvas.getHeight(), -1.5, 1.5);
      double x = a, y = b;

      //mandrelbrot algorithm
      int n, z = 0;
      for (n = 0; n < max; n++) {
        double aa = a * a - b * b;
        double bb = 2 * a * b;

        a = aa + x;
        b = bb + y;
        if (a + b > 16) {
          break;
        }
      }

      //get brightness
      double brightness = map(n, 0, max, 0, 1);
      brightness = n == max ? 0 : map(sqrt(brightness), 0, 1, 0, 255);

      //color the canvas
      canvas.setPixel(i, j, brightness, brightness, brightness);
    }
  }

  //save image
  canvas.writeJPEG("mandelbrot.jpeg", 100);
  std::cout << "Done" << std::endl;
}

//maps value from [a, b] to [x,y]
double map(double value, double a, double b, double x, double y) {
  return (value - a) * (y - x) / (b - a) + x;
}

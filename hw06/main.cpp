#include <math.h>
#include <cstdio>
#include <iostream>
#include <string>
#include "angle.h"
#include "image.h"
#include "shape.h"

/*
Kevin Chevalier
October 14, 2019
CSCI 3731
Homework 6
Create and Test Angle Class
*/

int main(int argc, char** argv) {
  // PART I: Tests all the operations with different angles to show correctness
  std::cout << "Run Very Extensive Very Boring Tests?" << std::endl;
  std::string res;
  std::cin >> res;
  if ((res[0] | 32) == 'y') {
    Angle a = 30.0, b = 100.0;
    Angle::test_op(a, b);
    std::cout << "Done! Try saying no next time..." << std::endl;
    return 0;
  }

  // PART II:Appling angle class to draw shapes into images
  std::cout << std::endl << "Running Shape Program!!" << std::endl;
  const std::string fileName = "output.jpeg";
  Image canvas(fileName, 500, 500, 0);

  // drawing triangles with length 8
  const int length = 7;
  const int sides = 3;
  Shape shape(0, 0, sides, length, 0);

  // Draw rings with different radii and num of shapes
  Angle delta = 20;
  for (double r = 10; r < 200; r += 15) {
    shape.drawRing(canvas, delta, r);
    delta += 5;
  }

  // Save Image
  canvas.write(100);
  std::cout << "Done" << std::endl;
}

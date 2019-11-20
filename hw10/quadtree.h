#ifndef QUADTREE_H
#define QUADTREE_H
#include <QWidget>
#include "fish.h"
#include "vector.h"

class QuadTree {
 public:
  QuadTree(double x, double y, double w, double h);
  bool insert(Fish* fish);
  bool contains(double x, double y, double w, double h, Vector& point);
  bool intersect(double x, double y, double r);
  void query(double x, double y, double r, std::vector<Fish*>& result);
  void display(QPainter& painter);
  friend std::ostream& operator<<(std::ostream& out, const QuadTree& c);
  virtual ~QuadTree();

 private:
  const static int dx[4];
  const static int dy[4];

  double x, y, w, h;
  int length, cap = 1;
  bool isDivided;
  QuadTree* subTrees[4];
  Fish* fishes[1];
};

#endif
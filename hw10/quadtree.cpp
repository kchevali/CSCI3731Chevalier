#include "quadtree.h"
#include <QWidget>
#include <QtGui>
#include <vector>
#include "fish.h"
#include "vector.h"

const int QuadTree::dx[4] = {1, -1, 1, -1};
const int QuadTree::dy[4] = {1, 1, -1, -1};

QuadTree::QuadTree(double x, double y, double w, double h) {
  this->x = x;
  this->y = y;
  this->w = w;
  this->h = h;
  this->length = 0;
  this->isDivided = false;
  for (int i = 0; i < 4; i++) subTrees[i] = nullptr;
  for (int i = 0; i < cap; i++) fishes[i] = nullptr;
}

bool QuadTree::contains(double x, double y, double w, double h, Vector& point) {
  return point.getX() >= x - w && point.getX() < x + w &&
         point.getY() >= y - h && point.getY() < y + h;
}

bool QuadTree::intersect(double x, double y, double r) {
  return !(x - r > this->x + this->w || x + r < this->x - this->w ||
           y - r > this->y + this->h || y + r < this->y - this->h);
}

bool QuadTree::insert(Fish* fish) {
  if (!contains(x, y, w, h, fish->getPos())) {
    return false;
  }
  if (length < cap) {
    fishes[length++] = fish;
  } else {
    if (!isDivided) {
      for (int i = 0; i < 4; i++) {
        int new_x = x + dx[i] * w / 2.0;
        int new_y = y + dy[i] * h / 2.0;
        subTrees[i] = new QuadTree(new_x, new_y, w / 2.0, h / 2.0);
      }
      isDivided = true;
    }
    for (int i = 0; i < 4; i++)
      if (subTrees[i]->insert(fish)) break;
  }
  return true;
}

void QuadTree::query(double x, double y, double r, std::vector<Fish*>& result) {
  if (!intersect(x, y, r)) return;
  for (int i = 0; i < length; i++) {
    if (contains(x, y, r, r, this->fishes[i]->getPos()))
      result.push_back(this->fishes[i]);
  }
  if (isDivided)
    for (int i = 0; i < 4; i++) subTrees[i]->query(x, y, r, result);
}

void QuadTree::display(QPainter& painter) {
  painter.drawRect(x - w + 1, y - h + 1, 2 * w - 2, 2 * h - 2);
  // painter.drawText(
  //     x, y, QString((std::to_string((int)x) +
  //     std::to_string((int)y)).c_str()));
  // for (int i = 0; i < length; i++) {
  //   fishes[i]->display(painter);
  // }
  // if (isDivided) {
  //   for (int i = 0; i < 4; i++) subTrees[i]->display(painter);
  // }
}

QuadTree::~QuadTree() {
  if (isDivided)
    for (int i = 0; i < 4; i++) delete subTrees[i];
}
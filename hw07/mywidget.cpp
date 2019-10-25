#include "mywidget.h"
#include <iostream>
#include "fish.h"
#include "population.h"

// create widget and set timer
MyWidget::MyWidget(std::vector<Population*>& pops) : pops(pops) {
  this->timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(update()));
  timer->start(20);
}

// update all fishes/populations
void MyWidget::updatePopulations() {
  for (auto p : pops) p->feed();
  for (auto p : pops) p->update();

  // scan last so the targets will be shown
  for (int i = 0; i < pops.size(); i++) {
    for (int j = i + 1; j < pops.size(); j++) {
      pops[i]->scan(*pops[j]);
    }
  }
}

// draw method
void MyWidget::paintEvent(QPaintEvent* event) {
  // init
  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing);

  // update
  updatePopulations();

  for (const auto& p : pops) {
    Fish* f = &p->first();
    while (f != nullptr) {
      // fish is tracking
      if (f->hasTarget()) {
        painter.setPen(QColor(255, 0, 0));
        double perp = sqrt(f->getPerception());
        painter.drawEllipse(QPointF(f->getX(), f->getY()), perp, perp);
      }
      // draw fish
      painter.setPen(p->getColor());
      double size = f->getSize() / 1000.0;
      QRect rect = QRect(f->getX(), f->getY(), f->getWidth() * size,
                         f->getHeight() * size);
      QPoint center = rect.center();
      QTransform t = QTransform()
                         .translate(center.x(), center.y())
                         .rotate(f->getDirection())
                         .translate(-center.x(), -center.y());
      QPolygon rotatedRect = t.mapToPolygon(rect);
      painter.drawConvexPolygon(rotatedRect);
      f = f->getNext();
    }

    // check if there is more then two populations
    // if 1 or less stop loop
    int alive = 0;
    for (auto p : pops) alive += p->size() > 0;
    if (alive <= 1) timer->stop();
  }
}
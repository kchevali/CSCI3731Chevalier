#include "mywidget.h"
#include <cmath>
#include <iostream>
#include <string>
#include "fish.h"
#include "flippyfish.h"
#include "population.h"

// create widget and set timer
MyWidget::MyWidget(std::vector<Population*>& pops) : pops(pops) {
  setMouseTracking(true);
  this->timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(update()));
  timer->start(10);
  frame = 0;
  bestText = "";
  fps = "--";
  isSingleView = false;
  time.start();
}

// update all fishes/populations
void MyWidget::updatePopulations() {
  if (pops.size() == 0) return;
  Population* bestPop = pops[0];
  for (int i = 0; i < pops.size(); i++)
    if (pops[i]->size() > bestPop->size()) bestPop = pops[i];

  // update
  for (auto p : pops) {
    p->update();
    p->avoid(avoidPoints,50);
  }

  for (auto p : pops) p->swim();
  for (auto p : pops) p->breed();
  for (int i = 0; i < pops.size(); i++)
    for (int j = i + 1; j < pops.size(); j++) pops[i]->feed(pops[j]);
  for (auto p : pops) p->shrink();

  if (frame % 30 == 0) {
    bestText = "Best Pop | Size: " + std::to_string(bestPop->size());
    bestText += " | Avg. Speed: " + std::to_string(bestPop->getAverageSpeed());
    bestText += " | Avg. Perception: " +
                std::to_string(bestPop->getAveragePerception());
    bestText +=
        " | Avg. Breed Size: " + std::to_string(bestPop->getAverageBreedSize());
  }
}

// draw method
void MyWidget::paintEvent(QPaintEvent* event) {
  int maxFrame = 100;
  if (frame > maxFrame) {
    frame = 0;
    time.restart();
  } else if (frame == maxFrame) {
    fps =
        std::to_string((int)std::floor(1000.0 * float(frame) / time.elapsed()));
  }
  // init
  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing);


  // update
  updatePopulations();

  int index = 0, textY = pops[0]->getHeight() - 10;
  painter.setPen(Qt::white);
  painter.drawText(0, textY, QString("Pop. Size:"));
  painter.drawText(0, 30, QString(bestText.c_str()));

  painter.drawText(0, 50, QString("FPS:"));
  painter.drawText(30, 50, QString(fps.c_str()));

  Fish* bigBoi = nullptr;
  if (isSingleView) {
    for (const auto& p : pops) {
      if (p->getLargeFish() != nullptr &&
          (bigBoi == nullptr ||
           p->getLargeFish()->getSize() > bigBoi->getSize())) {
        bigBoi = p->getLargeFish();
      }
    }
  }

  // Draw Population Sizes
  for (const auto& p : pops) {
    if (!isSingleView || (bigBoi != nullptr && *p != bigBoi->getPop())) {
      painter.setPen(isSingleView ? Qt::darkBlue : p->getColor());
      p->display(painter);
    }

    // Pop size label
    painter.setPen(p->getColor());
    painter.drawText(80 + index * 30, textY,
                     QString(std::to_string(p->size()).c_str()));
    index++;
    if (isSingleView && bigBoi != nullptr && *p != bigBoi->getPop()) {
      std::vector<Fish*> result;
      std::vector<QuadTree*> trees;
      p->getQuadTree().query(bigBoi->getCenterX(), bigBoi->getCenterY(),
                             bigBoi->getPerception(), result, &trees);
      for (Fish* fish : result) fish->display(painter);
      for (QuadTree* tree : trees) tree->display(painter);
    }
  }

  if (isSingleView && bigBoi != nullptr) {
    painter.setPen(Qt::red);
    bigBoi->display(painter);
    double p = bigBoi->getPerception();
    double x = bigBoi->getCenterX() - p, y = bigBoi->getCenterY() - p;
    painter.drawRect(x, y, 2 * p, 2 * p);
    painter.drawEllipse(x, y, 2 * p, 2 * p);
  }
  // Mouse
  painter.setPen(Qt::red);
  painter.drawEllipse(mouse.getX(), mouse.getY(), 5, 5);
  for(Vector& point: avoidPoints){
      painter.drawEllipse(point.getX(), point.getY(), 5, 5);
  }
  frame++;
}

void MyWidget::mousePressEvent(QMouseEvent* event) {
  if (event->button() == Qt::LeftButton) {
    isSingleView = !isSingleView;
  }else if (event->button() == Qt::RightButton) {
    avoidPoints.push_back(Vector(mouse.getX(),mouse.getY()));
  }
}

void MyWidget::mouseMoveEvent(QMouseEvent* event) {
  mouse.set(event->x(), event->y());
}

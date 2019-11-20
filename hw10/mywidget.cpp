#include "mywidget.h"
#include <cmath>
#include <iostream>
#include <string>
#include "fish.h"
#include "population.h"

// create widget and set timer
MyWidget::MyWidget(std::vector<Population*>& pops) : pops(pops) {
  this->timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(update()));
  timer->start(20);
  frame = 0;
  bestText = "";
  fps = "--";
  time.start();
}

// update all fishes/populations
void MyWidget::updatePopulations() {
  Population* bestPop = pops[0];
  for (int i = 0; i < pops.size(); i++)
    if (pops[i]->size() > bestPop->size()) bestPop = pops[i];

  for (auto p : pops) p->update();
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

  // Draw Population Sizes
  for (const auto& p : pops) {
    p->display(painter);
    painter.drawText(80 + index * 30, textY,
                     QString(std::to_string(p->size()).c_str()));
    index++;
  }
  // check if there is more then two populations
  // if 1 or less stop loop
  // int alive = 0;
  // for (auto p : pops) alive += p->size() > 0;
  // if (alive <= 1) {
  //   timer->stop();
  //   std::cout << "Simulation DONE!" << std::endl;
  // }
  frame++;
}
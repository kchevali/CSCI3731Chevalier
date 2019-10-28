#include <QApplication>
#include <QtGui>
#include <chrono>
#include <iostream>
#include <thread>
#include <vector>
#include "angle.h"
#include "fish.h"
#include "mywidget.h"
#include "population.h"

/*
Kevin Chevalier
October 21, 2019
CSCI 3731
Homework 7
Create Fishes and Populations

Simulation Rules
  *Each population has a random speed
  *Each fish has a small random variation from their population speed
  *Fishes target/eats smaller fishes from different populations
  *A fish will attempt to follow the closest valid target (not perfect path
    finding)
  *Fishes can only see other fishes within their range of perception
  *When a hunter fish is targeting another fish then a red circle shows the
    hunter's perception range
  *Fishes can only eat other fishes within their feeding radius
  *When the last member of a population dies, a new one emerges
  *Every iteration, a fish shrinks in size based on its speed
  *Faster fish shrink more quickly
  *A fish dies when its eaten or its size is zero
  *When a fish eats it gets bigger
*/

int main(int argc, char** argv) {
  srand(time(NULL));

  // define populations
  std::vector<Population*> pops;
  const int popCount = 5;
  const int popSize = 5;

  // start application
  QApplication app(argc, argv);
  MyWidget myWidget(pops);
  QPalette pal = QPalette();

  // set background
  pal.setColor(QPalette::Background, QColor(0, 0, 50));
  myWidget.setAutoFillBackground(true);
  myWidget.setPalette(pal);

  // Create populations
  QSize size = myWidget.size();
  for (int i = 0; i < popCount; i++)
    pops.push_back(new Population(popSize, size.width(), size.height()));

  myWidget.show();
  return app.exec();
}

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

QT Library
*/

int main(int argc, char** argv) {
  srand(time(NULL));

  // define populations
  std::vector<Population*> pops;
  const int popCount = 5;
  const int popSize = 20;

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

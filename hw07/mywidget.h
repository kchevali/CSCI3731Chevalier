#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QtGui>
#include "population.h"

class MyWidget : public QWidget {
  Q_OBJECT
 public:
  MyWidget(std::vector<Population *> &pops);
  void updatePopulations();

 protected:
  void paintEvent(QPaintEvent *event);
 signals:

 private:
  std::vector<Population *> &pops;
  QTimer *timer;

 public slots:
};

#endif  // MYWIDGET_H
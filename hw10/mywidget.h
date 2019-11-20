#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QtGui>
#include "population.h"

class MyWidget : public QWidget {
  Q_OBJECT
 public:
  MyWidget(std::vector<Population *> &pops);
  void updatePopulations(QPainter& painter);
  MyWidget &operator=(const MyWidget &thing) = delete;

 protected:
  void paintEvent(QPaintEvent *event);
 signals:

 private:
  std::vector<Population *> &pops;
  std::string bestText,fps;
  QTimer *timer;
  QTime time;
  int frame;

 public slots:
};

#endif  // MYWIDGET_H
#include <QApplication>

#include "controller.h"
#include "mainwindow.h"
#include "model.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  setlocale(LC_NUMERIC, "C");
  photo_lab::Model m;
  photo_lab::Controller c(m);
  photo_lab::MainWindow mw(c);
  mw.show();
  return a.exec();
}

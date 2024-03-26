#include "imagewidget.h"

#include <QPainter>
#include <QWidget>

void photo_lab::ImageWidget::SetInfoTransfer(QImage &value) { img_ = &value; }

void photo_lab::ImageWidget::paintEvent(QPaintEvent *) {
  if (img_ != nullptr) {
    painter_.begin(this);
    painter_.drawImage(0, 0, *img_);
    painter_.end();
  }
}

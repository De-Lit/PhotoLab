#ifndef PHOTOLAB_VIEW_OPENGLWIDGET_H_
#define PHOTOLAB_VIEW_OPENGLWIDGET_H_

#include <QPainter>
#include <QWidget>

namespace photo_lab {
class ImageWidget : public QWidget {
 public:
  ImageWidget(QWidget *parent = 0){};
  ~ImageWidget() = default;

  void SetInfoTransfer(QImage &value);

 protected:
  virtual void paintEvent(QPaintEvent *) override;

 private:
  QPainter painter_;
  QImage *img_ = nullptr;
};
}  // namespace photo_lab
#endif  // PHOTOLAB_VIEW_OPENGLWIDGET_H_

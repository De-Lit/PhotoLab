#ifndef PHOTOLAB_VIEW_MAINWINDOW_H_
#define PHOTOLAB_VIEW_MAINWINDOW_H_

#include <QColorDialog>
#include <QFileDialog>
#include <QImage>
#include <QMainWindow>

#include "controller.h"
#include "imagewidget.h"
#include "matrixwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

namespace photo_lab {
class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(photo_lab::Controller &c);
  ~MainWindow();

 private slots:
  void on_pushButton_clicked();
  void on_pushButtonSave_clicked();
  void on_radioButtonOriginalImage_toggled(bool checked);
  void on_radioButtonGrayscale_toggled(bool checked);
  void on_radioButtonNegative_toggled(bool checked);
  void on_radioButtonToning_toggled(bool checked);
  void on_radioButtonEmboss_toggled(bool checked);
  void on_radioButtonSharpen_toggled(bool checked);
  void on_radioButtonBoxBlur_toggled(bool checked);
  void on_radioButtonGaussianBlur_toggled(bool checked);
  void on_radioButtonLaplacianFilter_toggled(bool checked);
  void on_radioButtonSobelFilterLeft_toggled(bool checked);
  void on_radioButtonSobelFilterRight_toggled(bool checked);
  void on_radioButtonSobelFilterLeftAndRight_toggled(bool checked);

  void on_pushButtonSetColor_clicked();

  void on_pushButtonMatrixWindowShow_clicked();

  void on_radioButtonKernelMatrix_toggled(bool checked);

  void SetKernelMatrixSlot();

 signals:
  void signalUpdate();

 private:
  void virtual resizeEvent(QResizeEvent *event) override;

  std::unique_ptr<MatrixWindow> matrix_window_ = nullptr;
  Ui::MainWindow *ui_ = nullptr;
  Controller *c_ = nullptr;
  QColor color_;
};
}  // namespace photo_lab
#endif  // PHOTOLAB_VIEW_MAINWINDOW_H_

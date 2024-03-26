#ifndef PHOTOLAB_VIEW_MATRIXWINDOW_H_
#define PHOTOLAB_VIEW_MATRIXWINDOW_H_

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class MatrixWindow;
}
QT_END_NAMESPACE

namespace photo_lab {
class MatrixWindow : public QWidget {
  Q_OBJECT
 public:
  explicit MatrixWindow(QWidget *parent = nullptr);
  ~MatrixWindow();

  //  seted kernel matrix value
  std::vector<std::vector<float>> core;
  //  seted delimiter value
  int delimiter = 1;

 private:
  void SetGridLayout();
  void ClearGridLayout();

  Ui::MatrixWindow *ui_ = nullptr;
  int grid_layout_position_ = 3;
  int rows_count_ = 0;
  int columns_count_ = 0;

 signals:
  void SetKernelMatrixSignal();

 private slots:
  void on_pushButton_clicked();
  void on_radioButton3x3_toggled(bool checked);
  void on_radioButton5x5_toggled(bool checked);
  void on_radioButton9x9_toggled(bool checked);
  void on_radioButton17x17_toggled(bool checked);
};
}  // namespace photo_lab
#endif  // PHOTOLAB_VIEW_MATRIXWINDOW_H_

#include "matrixwindow.h"

#include <QWidget>

#include "ui_matrixwindow.h"

photo_lab::MatrixWindow::MatrixWindow(QWidget *parent)
    : QWidget(parent), ui_(new Ui::MatrixWindow) {
  setWindowFlags(Qt::Dialog);
  ui_->setupUi(this);
  ui_->horizontalLayout->addLayout(
      new QGridLayout(dynamic_cast<QWidget *>(ui_->horizontalLayout)),
      grid_layout_position_);
  ui_->radioButton3x3->setChecked(true);
}

photo_lab::MatrixWindow::~MatrixWindow() { delete ui_; }

void photo_lab::MatrixWindow::SetGridLayout() {
  core.clear();
  core.resize(rows_count_, std::vector<float>(columns_count_));
  QGridLayout *grid_layout = dynamic_cast<QGridLayout *>(
      ui_->horizontalLayout->itemAt(grid_layout_position_));
  for (int i = 0; i < rows_count_; ++i)
    for (int j = 0; j < columns_count_; ++j) {
      grid_layout->addWidget(
          new QDoubleSpinBox((dynamic_cast<QWidget *>(
              ui_->horizontalLayout->itemAt(grid_layout_position_)))),
          i, j);
      dynamic_cast<QDoubleSpinBox *>(
          grid_layout->itemAtPosition(i, j)->widget())
          ->setMaximum(100.);
      dynamic_cast<QDoubleSpinBox *>(
          grid_layout->itemAtPosition(i, j)->widget())
          ->setMinimum(-100.);
      dynamic_cast<QDoubleSpinBox *>(
          grid_layout->itemAtPosition(i, j)->widget())
          ->setSingleStep(0.01);
      dynamic_cast<QDoubleSpinBox *>(
          grid_layout->itemAtPosition(i, j)->widget())
          ->setDecimals(2);
      dynamic_cast<QDoubleSpinBox *>(
          grid_layout->itemAtPosition(i, j)->widget())
          ->setButtonSymbols(QAbstractSpinBox::NoButtons);
      dynamic_cast<QDoubleSpinBox *>(
          grid_layout->itemAtPosition(i, j)->widget())
          ->setAlignment(Qt::AlignHCenter);
    }

  dynamic_cast<QDoubleSpinBox *>(
      grid_layout->itemAtPosition(rows_count_ / 2, columns_count_ / 2)
          ->widget())
      ->setValue(1.);
  core[rows_count_ / 2][columns_count_ / 2] =
      dynamic_cast<QDoubleSpinBox *>(
          grid_layout->itemAtPosition(rows_count_ / 2, columns_count_ / 2)
              ->widget())
          ->value();
}

void photo_lab::MatrixWindow::ClearGridLayout() {
  if (ui_->horizontalLayout->itemAt(grid_layout_position_)->layout() !=
      nullptr) {
    QLayoutItem *item;
    while ((item = ui_->horizontalLayout->itemAt(grid_layout_position_)
                       ->layout()
                       ->takeAt(0)) != nullptr) {
      delete item->widget();
      delete item;
    }
  }
  this->resize(this->minimumWidth(), this->minimumHeight());
}

void photo_lab::MatrixWindow::on_pushButton_clicked() {
  delimiter = ui_->spinBox->value();

  QGridLayout *grid_layout = (dynamic_cast<QGridLayout *>(
      ui_->horizontalLayout->itemAt(grid_layout_position_)));
  for (int i = 0; i < rows_count_; ++i)
    for (int j = 0; j < columns_count_; ++j)
      core[i][j] = (dynamic_cast<QDoubleSpinBox *>(
                        grid_layout->itemAtPosition(i, j)->widget()))
                       ->value();

  emit SetKernelMatrixSignal();
}

void photo_lab::MatrixWindow::on_radioButton3x3_toggled(bool checked) {
  if (checked) {
    ClearGridLayout();
    rows_count_ = 3;
    columns_count_ = 3;
    SetGridLayout();
  }
}

void photo_lab::MatrixWindow::on_radioButton5x5_toggled(bool checked) {
  if (checked) {
    ClearGridLayout();
    rows_count_ = 5;
    columns_count_ = 5;
    SetGridLayout();
  }
}

void photo_lab::MatrixWindow::on_radioButton9x9_toggled(bool checked) {
  if (checked) {
    ClearGridLayout();
    rows_count_ = 9;
    columns_count_ = 9;
    SetGridLayout();
  }
}

void photo_lab::MatrixWindow::on_radioButton17x17_toggled(bool checked) {
  if (checked) {
    ClearGridLayout();
    rows_count_ = 17;
    columns_count_ = 17;
    SetGridLayout();
  }
}

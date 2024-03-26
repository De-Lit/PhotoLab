#include "mainwindow.h"

#include <QColorDialog>
#include <QFileDialog>
#include <QImage>
#include <QMainWindow>

#include "controller.h"
#include "imagewidget.h"
#include "ui_mainwindow.h"

photo_lab::MainWindow::MainWindow(photo_lab::Controller &c)
    : ui_(new Ui::MainWindow), c_(&c) {
  ui_->setupUi(this);
  matrix_window_ = std::unique_ptr<MatrixWindow>(new MatrixWindow(this));
  connect(matrix_window_.get(), &MatrixWindow::SetKernelMatrixSignal, this,
          &MainWindow::SetKernelMatrixSlot);
}

photo_lab::MainWindow::~MainWindow() { delete ui_; }

void photo_lab::MainWindow::on_pushButton_clicked() {
  QString path =
      QFileDialog::getOpenFileName(this, "Open file", ".", "*.bmp *.png");
  if (strlen(qPrintable(path))) {
    ui_->label->setText(path);
    ui_->radioButtonOriginalImage->setChecked(true);
    c_->FillData(path);
    ui_->horizontalWidget->SetInfoTransfer(c_->GetScaledtImage());
    ui_->label_2->setPixmap(QPixmap::fromImage(
        c_->GetOriginalImage().scaledToWidth(ui_->label_2->width())));
    c_->ScaleImage(ui_->horizontalWidget->width(),
                   ui_->horizontalWidget->height());
    ui_->statusbar->showMessage(
        QString("File name: %1")
            .arg(strrchr(&(path.toStdString()[0]), '/') + 1));
    ui_->horizontalWidget->update();
  }
}

void photo_lab::MainWindow::on_pushButtonSave_clicked() {
  QString file_name = QFileDialog::getSaveFileName(
      nullptr, "Save File", QDir::homePath(), "Images (*.bmp)");
  if (!file_name.isNull()) {
    c_->SaveImage(file_name);
    ui_->statusbar->showMessage(QString("Saved"));
  }
}

void photo_lab::MainWindow::on_radioButtonOriginalImage_toggled(bool checked) {
  if (checked) {
    c_->SetOriginalImage();
    ui_->horizontalWidget->update();
  }
}

void photo_lab::MainWindow::on_radioButtonNegative_toggled(bool checked) {
  if (checked) {
    c_->NegateFilter();
    ui_->horizontalWidget->update();
  }
}

void photo_lab::MainWindow::on_radioButtonGrayscale_toggled(bool checked) {
  if (checked) {
    c_->GrayscaleFilter();
    ui_->horizontalWidget->update();
  }
}

void photo_lab::MainWindow::on_radioButtonToning_toggled(bool checked) {
  if (checked) {
    c_->NegateColorFilter(color_.rgba());
    ui_->horizontalWidget->update();
  }
}

void photo_lab::MainWindow::on_radioButtonEmboss_toggled(bool checked) {
  if (checked) {
    c_->EmbossFilter();
    ui_->horizontalWidget->update();
  }
}

void photo_lab::MainWindow::on_radioButtonSharpen_toggled(bool checked) {
  if (checked) {
    c_->SharpenFilter();
    ui_->horizontalWidget->update();
  }
}

void photo_lab::MainWindow::on_radioButtonBoxBlur_toggled(bool checked) {
  if (checked) {
    c_->BoxBlurFilter();
    ui_->horizontalWidget->update();
  }
}

void photo_lab::MainWindow::on_radioButtonGaussianBlur_toggled(bool checked) {
  if (checked) {
    c_->GaussianBlurFilter();
    ui_->horizontalWidget->update();
  }
}

void photo_lab::MainWindow::on_radioButtonLaplacianFilter_toggled(
    bool checked) {
  if (checked) {
    c_->LaplacianFilter();
    ui_->horizontalWidget->update();
  }
}

void photo_lab::MainWindow::on_radioButtonSobelFilterLeft_toggled(
    bool checked) {
  if (checked) {
    c_->SobelLeftFilter();
    ui_->horizontalWidget->update();
  }
}

void photo_lab::MainWindow::on_radioButtonSobelFilterRight_toggled(
    bool checked) {
  if (checked) {
    c_->SobelRightFilter();
    ui_->horizontalWidget->update();
  }
}

void photo_lab::MainWindow::on_radioButtonSobelFilterLeftAndRight_toggled(
    bool checked) {
  if (checked) {
    c_->SobelLeftAndRightFilter();
    ui_->horizontalWidget->update();
  }
}

void photo_lab::MainWindow::on_pushButtonSetColor_clicked() {
  QColor color = QColorDialog::getColor(Qt::white);
  if (color.isValid()) {
    color_ = color;
    QVariant variant = color;
    QString colcode = variant.toString();
    ui_->labelLineColor_2->setStyleSheet("background-color : " + colcode + "");
    if (ui_->radioButtonToning->isChecked()) {
      c_->NegateColorFilter(color_.rgba());
      ui_->horizontalWidget->update();
    }
  }
}

void photo_lab::MainWindow::resizeEvent(QResizeEvent *event) {
  c_->ScaleImage(ui_->horizontalWidget->width(),
                 ui_->horizontalWidget->height());
  ui_->horizontalWidget->update();
}

void photo_lab::MainWindow::on_pushButtonMatrixWindowShow_clicked() {
  matrix_window_->show();
}

void photo_lab::MainWindow::on_radioButtonKernelMatrix_toggled(bool checked) {
  if (checked) {
    c_->KernelFilter(matrix_window_->core, matrix_window_->delimiter);
    ui_->horizontalWidget->update();
  }
}

void photo_lab::MainWindow::SetKernelMatrixSlot() {
  if (ui_->radioButtonKernelMatrix->isChecked()) {
    c_->KernelFilter(matrix_window_->core, matrix_window_->delimiter);
    ui_->horizontalWidget->update();
  }
}

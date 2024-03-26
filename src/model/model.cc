#include "model.h"

#include <QColorDialog>
#include <QString>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "model.h"

photo_lab::Model::Model() : image_list_(2) {
  scaled_image_ = new image::Image();
}

photo_lab::Model::~Model() { delete scaled_image_; }

QImage &photo_lab::Model::GetImage() { return (image_list_.begin())->Get(); }

QImage &photo_lab::Model::GetOriginalImage() {
  return (++image_list_.begin())->Get();
}

QImage &photo_lab::Model::GetScaledtImage() { return scaled_image_->Get(); }

int photo_lab::Model::FillData(QString path) {
  image_list_.begin()->Load(path);
  *(++image_list_.begin()) = *image_list_.begin();
  scaled_image_->Get() = image_list_.begin()->Get().scaled(width_, height_);
  return 0;
}

void photo_lab::Model::SaveImage(QString path) {
  image_list_.begin()->Save(path);
}

void photo_lab::Model::SetOriginalImage() {
  *image_list_.begin() = *++image_list_.begin();
  ScaleImage(width_, height_);
}

void photo_lab::Model::NegateFilter() {
  photo_lab::Filter::NegateFilter(*++image_list_.begin(), *image_list_.begin());
  ScaleImage(width_, height_);
}

void photo_lab::Model::GrayscaleFilter() {
  photo_lab::Filter::GrayscaleFilter(*++image_list_.begin(),
                                     *image_list_.begin());
  ScaleImage(width_, height_);
}

void photo_lab::Model::NegateColorFilter(QRgb color) {
  photo_lab::Filter::NegateColorFilter(*++image_list_.begin(),
                                       *image_list_.begin(), color);
  ScaleImage(width_, height_);
}

void photo_lab::Model::EmbossFilter() {
  photo_lab::Filter::EmbossFilter(*++image_list_.begin(), *image_list_.begin());
  ScaleImage(width_, height_);
}

void photo_lab::Model::SharpenFilter() {
  photo_lab::Filter::SharpenFilter(*++image_list_.begin(),
                                   *image_list_.begin());
  ScaleImage(width_, height_);
}

void photo_lab::Model::BoxBlurFilter() {
  photo_lab::Filter::BoxBlurFilter(*++image_list_.begin(),
                                   *image_list_.begin());
  ScaleImage(width_, height_);
}

void photo_lab::Model::GaussianBlurFilter() {
  photo_lab::Filter::GaussianBlurFilter(*++image_list_.begin(),
                                        *image_list_.begin());
  ScaleImage(width_, height_);
}

void photo_lab::Model::LaplacianFilter() {
  photo_lab::Filter::LaplacianFilter(*++image_list_.begin(),
                                     *image_list_.begin());
  ScaleImage(width_, height_);
}

void photo_lab::Model::SobelLeftFilter() {
  photo_lab::Filter::SobelLeftFilter(*++image_list_.begin(),
                                     *image_list_.begin());
  ScaleImage(width_, height_);
}

void photo_lab::Model::SobelRightFilter() {
  photo_lab::Filter::SobelRightFilter(*++image_list_.begin(),
                                      *image_list_.begin());
  ScaleImage(width_, height_);
}

void photo_lab::Model::SobelLeftAndRightFilter() {
  photo_lab::Filter::SobelLeftAndRightFilter(*++image_list_.begin(),
                                             *image_list_.begin());
  ScaleImage(width_, height_);
}

void photo_lab::Model::ScaleImage(int width, int height) {
  if (!scaled_image_->Get().isNull())
    scaled_image_->Get() = image_list_.begin()->Scaled(width, height);
  width_ = width;
  height_ = height;
}

void photo_lab::Model::KernelFilter(const std::vector<std::vector<float>> &core,
                                    int delimiter) {
  photo_lab::Filter::KernelFilter(*++image_list_.begin(), *image_list_.begin(),
                                  core, delimiter);
  ScaleImage(width_, height_);
}

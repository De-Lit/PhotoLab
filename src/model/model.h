#ifndef PHOTOLAB_MODEL_MODEL_H_
#define PHOTOLAB_MODEL_MODEL_H_

#include <QImage>
#include <QString>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <list>

#include "filter.h"
#include "image.h"

namespace photo_lab {
class Model {
 public:
  Model();
  Model(const Model &other) = delete;
  Model(Model &&other) = delete;
  Model &operator=(const Model &other) = delete;
  Model &operator=(Model &&other) = delete;
  ~Model();

  QImage &GetImage();
  QImage &GetOriginalImage();
  QImage &GetScaledtImage();
  int FillData(QString);
  void SaveImage(QString);

  void SetOriginalImage();
  void NegateFilter();
  void GrayscaleFilter();
  void NegateColorFilter(QRgb);

  void EmbossFilter();
  void SharpenFilter();
  void BoxBlurFilter();
  void GaussianBlurFilter();
  void LaplacianFilter();
  void SobelLeftFilter();
  void SobelRightFilter();
  void SobelLeftAndRightFilter();

  void ScaleImage(int, int);

  void KernelFilter(const std::vector<std::vector<float>> &, int);

 private:
  std::list<image::Image> image_list_;
  image::Image *scaled_image_ = nullptr;
  int width_ = 0;
  int height_ = 0;
};
}  // namespace photo_lab
#endif  // PHOTOLAB_MODEL_MODEL_H_

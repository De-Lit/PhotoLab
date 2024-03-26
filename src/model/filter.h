#ifndef PHOTOLAB_MODEL_FILTER_H_
#define PHOTOLAB_MODEL_FILTER_H_

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "iimage.h"

namespace photo_lab {
class Filter {
 public:
  Filter() = delete;
  Filter(const Filter &other) = delete;
  Filter(Filter &&other) = delete;
  Filter &operator=(const Filter &other) = delete;
  Filter &operator=(Filter &&other) = delete;
  ~Filter() = delete;

  static void NegateFilter(const image::IImage &, image::IImage &);
  static void GrayscaleFilter(const image::IImage &, image::IImage &);
  static void NegateColorFilter(const image::IImage &, image::IImage &,
                                image::rgb_t);
  static void KernelFilter(const image::IImage &, image::IImage &,
                           const std::vector<std::vector<float>> &, int);

  static void EmbossFilter(const image::IImage &, image::IImage &);
  static void SharpenFilter(const image::IImage &, image::IImage &);
  static void BoxBlurFilter(const image::IImage &, image::IImage &);
  static void GaussianBlurFilter(const image::IImage &, image::IImage &);
  static void LaplacianFilter(const image::IImage &, image::IImage &);
  static void SobelLeftFilter(const image::IImage &, image::IImage &);
  static void SobelRightFilter(const image::IImage &, image::IImage &);
  static void SobelLeftAndRightFilter(const image::IImage &, image::IImage &);

 private:
  static void FillColors(float &, float &, float &,
                         const std::vector<std::vector<float>> &,
                         const image::IImage &, int, int);
};
}  // namespace photo_lab
#endif  // PHOTOLAB_MODEL_FILTER_H_

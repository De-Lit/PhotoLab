#ifndef MODEL_IMAGE_IMAGE_H_
#define MODEL_IMAGE_IMAGE_H_

#include <QImage>

#include "iimage.h"
#include "rgb.h"

namespace image {
class Image : public IImage {
 public:
  virtual ~Image() = default;
  int Width() const override;
  int Height() const override;
  rgb_t Pixel(int x, int y) const override;
  void SetPixel(int x, int y, unsigned int index_or_rgb) override;

  QImage &Get();
  bool Load(const QString &file_name);
  QImage Scaled(int w, int h);
  bool Save(const QString &file_name);

 private:
  QImage image;
};
}  // namespace image

#endif  // MODEL_IMAGE_IMAGE_H_

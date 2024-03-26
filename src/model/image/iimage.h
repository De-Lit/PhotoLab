#ifndef MODEL_IMAGE_IIMAGE_H_
#define MODEL_IMAGE_IIMAGE_H_

#include "rgb.h"

namespace image {

class IImage {
 public:
  virtual int Width() const = 0;
  virtual int Height() const = 0;
  virtual rgb_t Pixel(int x, int y) const = 0;
  virtual void SetPixel(int x, int y, unsigned int index_or_rgb) = 0;
};
}  // namespace image

#endif  // MODEL_IMAGE_IIMAGE_H_

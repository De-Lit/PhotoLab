#include "image.h"

int image::Image::Width() const { return image.width(); }

int image::Image::Height() const { return image.height(); }

image::rgb_t image::Image::Pixel(int x, int y) const {
  return image.pixel(x, y);
}

void image::Image::SetPixel(int x, int y, unsigned int index_or_rgb) {
  image.setPixel(x, y, index_or_rgb);
}

bool image::Image::Load(const QString &file_name) {
  return image.load(file_name);
}

QImage image::Image::Scaled(int w, int h) { return image.scaled(w, h); }

bool image::Image::Save(const QString &file_name) {
  return image.save(file_name);
}

QImage &image::Image::Get() { return image; }

#include "filter.h"

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "color.h"

void photo_lab::Filter::NegateFilter(const image::IImage &image,
                                     image::IImage &result_image) {
  for (int i = 0; i < image.Width(); ++i)
    for (int j = 0; j < image.Height(); ++j)
      result_image.SetPixel(
          i, j,
          image::Color(255 - image::Color(image.Pixel(i, j)).Red(),
                       255 - image::Color(image.Pixel(i, j)).Green(),
                       255 - image::Color(image.Pixel(i, j)).Blue())
              .Rgba());
}

void photo_lab::Filter::GrayscaleFilter(const image::IImage &image,
                                        image::IImage &result_image) {
  float fr{};
  for (int i = 0; i < image.Width(); ++i)
    for (int j = 0; j < image.Height(); ++j) {
      fr = (0.299f * image::Color(image.Pixel(i, j)).Red() +
            0.587f * image::Color(image.Pixel(i, j)).Green() +
            0.114f * image::Color(image.Pixel(i, j)).Blue());
      result_image.SetPixel(i, j, image::Color(fr, fr, fr).Rgba());
    }
}

void photo_lab::Filter::NegateColorFilter(const image::IImage &image,
                                          image::IImage &result_image,
                                          image::rgb_t color) {
  float fr{};
  for (int i = 0; i < image.Width(); ++i)
    for (int j = 0; j < image.Height(); ++j)
      if (image.Pixel(i, j) == color) {
        fr = (0.299f * image::Color(image.Pixel(i, j)).Red() +
              0.587f * image::Color(image.Pixel(i, j)).Green() +
              0.114f * image::Color(image.Pixel(i, j)).Blue());
        result_image.SetPixel(i, j, image::Color(fr, fr, fr).Rgba());
      } else {
        result_image.SetPixel(i, j, image.Pixel(i, j));
      }
}

void photo_lab::Filter::KernelFilter(
    const image::IImage &image, image::IImage &result_image,
    const std::vector<std::vector<float>> &kernel, int delimiter) {
  float red{};
  float green{};
  float blue{};
  for (int i = 0; i < image.Width(); ++i) {
    for (int j = 0; j < image.Height(); ++j) {
      FillColors(red, green, blue, kernel, image, i, j);
      result_image.SetPixel(
          i, j,
          image::Color(red / (float)delimiter, green / (float)delimiter,
                       blue / (float)delimiter)
              .Rgba());
      red = 0.0f;
      green = 0.0f;
      blue = 0.0f;
    }
  }
}

void photo_lab::Filter::EmbossFilter(const image::IImage &image,
                                     image::IImage &result_image) {
  int delimiter = 1;
  std::vector<std::vector<float>> kernel{
      {-2.0f, -1.0f, 0.0f}, {-1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 2.0f}};
  KernelFilter(image, result_image, kernel, delimiter);
}

void photo_lab::Filter::SharpenFilter(const image::IImage &image,
                                      image::IImage &result_image) {
  int delimiter = 1;
  std::vector<std::vector<float>> kernel{
      {0.0f, -1.0f, 0.0f}, {-1.0f, 5.0f, -1.0f}, {0.0f, -1.0f, 0.0f}};
  KernelFilter(image, result_image, kernel, delimiter);
}

void photo_lab::Filter::BoxBlurFilter(const image::IImage &image,
                                      image::IImage &result_image) {
  int delimiter = 9;
  std::vector<std::vector<float>> kernel{
      {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f}};
  KernelFilter(image, result_image, kernel, delimiter);
}

void photo_lab::Filter::GaussianBlurFilter(const image::IImage &image,
                                           image::IImage &result_image) {
  int delimiter = 16;
  std::vector<std::vector<float>> kernel{
      {1.0f, 2.0f, 1.0f}, {2.0f, 4.0f, 2.0f}, {1.0f, 2.0f, 1.0f}};
  KernelFilter(image, result_image, kernel, delimiter);
}

void photo_lab::Filter::LaplacianFilter(const image::IImage &image,
                                        image::IImage &result_image) {
  int delimiter = 1;
  std::vector<std::vector<float>> kernel{
      {-1.0f, -1.0f, -1.0f}, {-1.0f, 8.0f, -1.0f}, {-1.0f, -1.0f, -1.0f}};
  KernelFilter(image, result_image, kernel, delimiter);
}

void photo_lab::Filter::SobelLeftFilter(const image::IImage &image,
                                        image::IImage &result_image) {
  int delimiter = 1;
  std::vector<std::vector<float>> kernel{
      {1.0f, 0.0f, -1.0f}, {2.0f, 0.0f, -2.0f}, {1.0f, 0.0f, -1.0f}};
  KernelFilter(image, result_image, kernel, delimiter);
}

void photo_lab::Filter::SobelRightFilter(const image::IImage &image,
                                         image::IImage &result_image) {
  int delimiter = 1;
  std::vector<std::vector<float>> kernel{
      {-1.0f, 0.0f, 1.0f}, {-2.0f, 0.0f, 2.0f}, {-1.0f, 0.0f, 1.0f}};
  KernelFilter(image, result_image, kernel, delimiter);
}

void photo_lab::Filter::SobelLeftAndRightFilter(const image::IImage &image,
                                                image::IImage &result_image) {
  std::vector<std::vector<float>> left_sobel_kernel{
      {1.0f, 0.0f, -1.0f}, {2.0f, 0.0f, -2.0f}, {1.0f, 0.0f, -1.0f}};
  std::vector<std::vector<float>> right_sobel_kernel{
      {-1.0f, 0.0f, 1.0f}, {-2.0f, 0.0f, 2.0f}, {-1.0f, 0.0f, 1.0f}};
  float red_left{}, green_left{}, blue_left{}, red_right{}, green_right{},
      blue_right{};
  for (int i = 0; i < image.Width(); ++i) {
    for (int j = 0; j < image.Height(); ++j, red_left = 0.0f, green_left = 0.0f,
             blue_left = 0.0f, red_right = 0.0f, green_right = 0.0f,
             blue_right = 0.0f) {
      FillColors(red_left, green_left, blue_left, left_sobel_kernel, image, i,
                 j);
      FillColors(red_right, green_right, blue_right, right_sobel_kernel, image,
                 i, j);
      result_image.SetPixel(
          i, j,
          image::Color(red_left, green_left, blue_left).Rgba() +
              image::Color(red_right, green_right, blue_right).Rgba());
    }
  }
}

void photo_lab::Filter::FillColors(
    float &red, float &green, float &blue,
    const std::vector<std::vector<float>> &kernel, const image::IImage &image,
    int row, int column) {
  int rows = static_cast<int>(kernel.size());
  int columns = static_cast<int>(kernel[0].size());
  for (int p = 0; p < rows; ++p)
    for (int q = 0; q < columns; ++q)
      if (row - (rows - 1) / 2 + p >= 0 &&
          column - (columns - 1) / 2 + q >= 0 &&
          row - (rows - 1) / 2 + p < image.Width() &&
          column - (columns - 1) / 2 + q < image.Height()) {
        red += image::Color(image.Pixel(row - (rows - 1) / 2 + p,
                                        column - (columns - 1) / 2 + q))
                   .Red() *
               kernel[p][q];
        green += image::Color(image.Pixel(row - (rows - 1) / 2 + p,
                                          column - (columns - 1) / 2 + q))
                     .Green() *
                 kernel[p][q];
        blue += image::Color(image.Pixel(row - (rows - 1) / 2 + p,
                                         column - (columns - 1) / 2 + q))
                    .Blue() *
                kernel[p][q];
      }
}

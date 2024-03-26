#include <gtest/gtest.h>

#include "model.h"

QString file_dir = "tests/materials/sample_test.bmp";
QString white_image_dir = "tests/materials/white_image.bmp";
int test_image_width = 200;
int test_image_height = 200;

void TestFoo(QImage image, QColor color) {
  ASSERT_EQ(image.width(), test_image_width);
  ASSERT_EQ(image.height(), test_image_height);
  for (int i = 0; i < image.width(); ++i)
    for (int j = 0; j < image.height(); ++j) {
      ASSERT_EQ(qRed(image.pixel(i, j)), color.red());
      ASSERT_EQ(qGreen(image.pixel(i, j)), color.green());
      ASSERT_EQ(qBlue(image.pixel(i, j)), color.blue());
    }
}

TEST(CreateModel, 1) {
  // Arrange
  photo_lab::Model m;
  // Act
  auto image = m.GetOriginalImage();
  // Assert
  ASSERT_EQ(image.height(), 0);
  ASSERT_EQ(image.width(), 0);
}

TEST(FillData, 1) {
  // Arrange
  QColor color(255, 255, 255);
  photo_lab::Model m;
  int error = m.FillData(white_image_dir);
  // Act
  auto image = m.GetOriginalImage();
  // Assert
  ASSERT_EQ(error, 0);
  TestFoo(image, color);
}

TEST(SetOriginalImage, 1) {
  // Arrange
  QColor color(255, 255, 255);
  photo_lab::Model m;
  int error = m.FillData(white_image_dir);
  // Act
  m.SetOriginalImage();
  // Assert
  auto image = m.GetImage();
  ASSERT_EQ(error, 0);
  TestFoo(image, color);
}

TEST(SetOriginalImage, 2) {
  // Arrange
  QColor color(255, 255, 255);
  photo_lab::Model m;
  int error = m.FillData(white_image_dir);
  // Act
  m.NegateFilter();
  m.SetOriginalImage();
  // Assert
  auto image = m.GetImage();
  ASSERT_EQ(error, 0);
  TestFoo(image, color);
}

TEST(SaveImage, 1) {
  // Arrange
  QColor color(255, 255, 255);
  photo_lab::Model m;
  int error_1 = m.FillData(white_image_dir);
  // Act
  m.SaveImage("save_test.png");
  // Assert
  int error_2 = m.FillData("save_test.png");
  ASSERT_EQ(error_1, 0);
  ASSERT_EQ(error_2, 0);
  auto image = m.GetImage();
  TestFoo(image, color);
  ASSERT_EQ(remove("save_test.png"), 0);
}

TEST(NegateFilter, 1) {
  // Arrange
  QColor color(0, 0, 0);
  photo_lab::Model m;
  int error = m.FillData(white_image_dir);
  // Act
  m.NegateFilter();
  // Assert
  auto image = m.GetImage();
  TestFoo(image, color);
  ASSERT_EQ(error, 0);
}

TEST(GrayscaleFilter, 1) {
  // Arrange
  QColor color(255, 255, 255);
  photo_lab::Model m;
  int error = m.FillData(white_image_dir);
  // Act
  m.GrayscaleFilter();
  // Assert
  auto image = m.GetImage();
  TestFoo(image, color);
  ASSERT_EQ(error, 0);
}

TEST(NegateColorFilter, 1) {
  // Arrange
  QColor color(255, 0, 0);
  photo_lab::Model m;
  int error = m.FillData(file_dir);
  // Act
  m.NegateColorFilter(4294901760);  // rgb red color
  // Assert
  auto image = m.GetImage();
  for (int i = 0; i < image.width(); ++i)
    for (int j = 0; j < image.height(); ++j) {
      ASSERT_EQ(qRed(image.pixel(i, j)) != color.red() ||
                    qGreen(image.pixel(i, j)) != color.green() ||
                    qBlue(image.pixel(i, j)) != color.blue(),
                true);
    }
  ASSERT_EQ(error, 0);
}

TEST(EmbossFilter, 1) {
  // Arrange
  photo_lab::Model m;
  int error = m.FillData(file_dir);
  // Act
  m.EmbossFilter();
  // Assert
  ASSERT_EQ(error, 0);
}

TEST(SharpenFilter, 1) {
  // Arrange
  photo_lab::Model m;
  int error = m.FillData(file_dir);
  // Act
  m.SharpenFilter();
  // Assert
  ASSERT_EQ(error, 0);
}

TEST(BoxBlurFilter, 1) {
  // Arrange
  photo_lab::Model m;
  int error = m.FillData(file_dir);
  // Act
  m.BoxBlurFilter();
  // Assert
  ASSERT_EQ(error, 0);
}

TEST(GaussianBlurFilter, 1) {
  // Arrange
  photo_lab::Model m;
  int error = m.FillData(file_dir);
  // Act
  m.GaussianBlurFilter();
  // Assert
  ASSERT_EQ(error, 0);
}

TEST(LaplacianFilter, 1) {
  // Arrange
  photo_lab::Model m;
  int error = m.FillData(file_dir);
  // Act
  m.LaplacianFilter();
  // Assert
  ASSERT_EQ(error, 0);
}

TEST(SobelLeftFilter, 1) {
  // Arrange
  photo_lab::Model m;
  int error = m.FillData(file_dir);
  // Act
  m.SobelLeftFilter();
  // Assert
  ASSERT_EQ(error, 0);
}

TEST(SobelRightFilter, 1) {
  // Arrange
  photo_lab::Model m;
  int error = m.FillData(file_dir);
  // Act
  m.SobelRightFilter();
  // Assert
  ASSERT_EQ(error, 0);
}

TEST(SobelLeftAndRightFilter, 1) {
  // Arrange
  photo_lab::Model m;
  int error = m.FillData(file_dir);
  // Act
  m.SobelLeftAndRightFilter();
  // Assert
  ASSERT_EQ(error, 0);
}

TEST(ScaleImage, 1) {
  // Arrange
  photo_lab::Model m;
  int error = m.FillData(file_dir);
  // Act
  m.ScaleImage(1, 1);
  auto scaled_image = m.GetScaledtImage();
  // Assert
  ASSERT_EQ(error, 0);
}

TEST(ScaleImage, 2) {
  // Arrange
  photo_lab::Model m;
  int error = m.FillData(file_dir);
  // Act
  m.GrayscaleFilter();
  m.ScaleImage(3, 3);
  auto scaled_image = m.GetScaledtImage();
  // Assert
  ASSERT_EQ(error, 0);
}

TEST(KernelFilter, 1) {
  // Arrange
  photo_lab::Model m;
  int error = m.FillData(file_dir);
  std::vector<std::vector<float>> kernel{
      {0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}};
  int delimiter = 1;
  // Act
  m.KernelFilter(kernel, delimiter);
  auto scaled_image = m.GetOriginalImage();
  // Assert
  ASSERT_EQ(error, 0);
}

TEST(KernelFilter, 2) {
  // Arrange
  photo_lab::Model m;
  int error = m.FillData(file_dir);
  std::vector<std::vector<float>> kernel{
      {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f}};
  int delimiter = 1;
  // Act
  m.KernelFilter(kernel, delimiter);
  auto scaled_image = m.GetOriginalImage();
  // Assert
  ASSERT_EQ(error, 0);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

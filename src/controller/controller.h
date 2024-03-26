#ifndef PHOTOLAB_CONTROLLER_CONTROLLER_H_
#define PHOTOLAB_CONTROLLER_CONTROLLER_H_

#include "model.h"

namespace photo_lab {
class Controller {
 public:
  Controller() = default;
  Controller(photo_lab::Model &m) : m_(&m) {}
  Controller(const Controller &other) = delete;
  Controller(Controller &&other) = delete;
  Controller &operator=(const Controller &other) = delete;
  Controller &operator=(Controller &&other) = delete;
  ~Controller() = default;

  QImage &GetOriginalImage() { return m_->GetOriginalImage(); }

  QImage &GetScaledtImage() { return m_->GetScaledtImage(); }

  int FillData(QString path) { return m_->FillData(path); }

  void SaveImage(QString file_name) { m_->SaveImage(file_name); }

  void SetOriginalImage() { m_->SetOriginalImage(); }

  void NegateFilter() { m_->NegateFilter(); }

  void GrayscaleFilter() { m_->GrayscaleFilter(); }

  void NegateColorFilter(QRgb color) { m_->NegateColorFilter(color); }

  void EmbossFilter() { m_->EmbossFilter(); }

  void SharpenFilter() { m_->SharpenFilter(); }

  void BoxBlurFilter() { m_->BoxBlurFilter(); }

  void GaussianBlurFilter() { m_->GaussianBlurFilter(); }
  void LaplacianFilter() { m_->LaplacianFilter(); }

  void SobelLeftFilter() { m_->SobelLeftFilter(); }

  void SobelRightFilter() { m_->SobelRightFilter(); }

  void SobelLeftAndRightFilter() { m_->SobelLeftAndRightFilter(); }

  void ScaleImage(int width, int height) { m_->ScaleImage(width, height); }

  void KernelFilter(std::vector<std::vector<float>> &core, int delimiter) {
    m_->KernelFilter(core, delimiter);
  }

 private:
  photo_lab::Model *m_ = nullptr;
};
}  // namespace photo_lab
#endif  // PHOTOLAB_CONTROLLER_CONTROLLER_H_

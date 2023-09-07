#pragma once
#include "capturer.h"

namespace engine {
class CameraCapturerWin : public Capturer {
 public:
  void startCapture();

 private:
  std::shared_ptr<Buffer> handleBuffer(std::shared_ptr<Buffer> buffer) override;
};
}  // namespace engine
#pragma once
#include "capturer.h"

namespace engine {
class CameraCapturerWin : public Capturer {
 public:
  void startCapture();

 private:
  void handleBuffer(std::shared_ptr<Buffer> frame) override;
};
}  // namespace engine
//
// Created by 谢松德 on 2023/2/4.
//

#ifndef VIDEOPLAYER_CAMERA_CAPTURER_MAC_H
#define VIDEOPLAYER_CAMERA_CAPTURER_MAC_H
#include "capturer.h"

namespace engine {
class CameraCapturerMac : public Capturer {
 public:
  void startCapture() override;

 private:
  std::shared_ptr<Buffer> handleBuffer(std::shared_ptr<Buffer> buffer) override;
};
}  // namespace engine

#endif  // VIDEOPLAYER_CAMERA_CAPTURER_MAC_H

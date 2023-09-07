#include "camera_capturer_win.h"

namespace engine {
void CameraCapturerWin::startCapture() {
  std::cout << "CameraCapturerWin::startCapture" << std::endl;
  //    handle(std::make_unique<VideoFrame>(nullptr));
}

std::shared_ptr<Buffer> CameraCapturerWin::handleBuffer(
    std::shared_ptr<Buffer> buffer) {
  std::cout << "CameraCapturerWin::handleFrame" << std::endl;
}

}  // namespace engine
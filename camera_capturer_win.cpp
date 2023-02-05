#include "camera_capturer_win.h"

namespace engine {
void CameraCapturerWin::startCapture()
{
    std::cout << "CameraCapturerWin::startCapture" << std::endl;
//    handle(std::make_unique<VideoFrame>(nullptr));
}

void CameraCapturerWin::handleBuffer(std::shared_ptr<Buffer> frame)
{
    std::cout << "CameraCapturerWin::handleFrame" << std::endl;
    
}

}
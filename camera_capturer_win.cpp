#include "camera_capturer_win.h"

namespace engine {
void CameraCapturerWin::startCapture()
{
    std::cout << "CameraCapturerWin::startCapture" << std::endl;
    handle(std::make_unique<VideoFrame>());
}

void CameraCapturerWin::handleFrame(VideoFrame* frame)
{
    std::cout << "CameraCapturerWin::handleFrame" << std::endl;
    
}

}
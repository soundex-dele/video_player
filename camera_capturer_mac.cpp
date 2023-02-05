//
// Created by 谢松德 on 2023/2/4.
//

#include "camera_capturer_mac.h"

namespace engine {
void CameraCapturerMac::startCapture()
{
    std::cout << "CameraCapturerMac::startCapture" << std::endl;
    handle(std::make_unique<Buffer>());
}

void CameraCapturerMac::handleBuffer(std::shared_ptr<Buffer> frame)
{
    std::cout << "CameraCapturerMac::handleFrame" << std::endl;

}

}
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
    void handleBuffer(std::shared_ptr<Buffer> frame) override;
};
}




#endif //VIDEOPLAYER_CAMERA_CAPTURER_MAC_H

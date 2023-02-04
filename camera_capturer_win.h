#pragma once
#include "capturer.h"

namespace engine {
class CameraCapturerWin : public Capturer
{
public:
    void startCapture();
private:
    void handleFrame(VideoFrame* frame) override;
};
}
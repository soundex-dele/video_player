#pragma once
#include "capturer.h"

namespace engine {
class RtspCapturer : public Capturer
{
public:
    ~RtspCapturer() = default;
    void startCapture()
    {
        handle(std::make_unique<VideoFrame>());
    }
private:
    void handleFrame(VideoFrame* frame) override {}
};
}
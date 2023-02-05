//
// Created by 谢松德 on 2023/2/5.
//

#include "h264_encoder.h"

namespace engine
{
bool H264Encoder::init() {}

void H264Encoder::handleBuffer(std::shared_ptr<Buffer> buffer)
{
    std::cout << "H264Encoder::handleBuffer" << std::endl;
    auto new_frame = dynamic_pointer_cast<VideoFrame>(buffer);
    if (new_frame)
        std::cout << "H264Encoder::get new frame" << std::endl;
    buffer_ = std::make_shared<EncodedImage>(nullptr, 0, 0);
}
}
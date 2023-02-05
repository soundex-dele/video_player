//
// Created by 谢松德 on 2023/2/6.
//

#include "mp4_recorder.h"
namespace engine {
bool Mp4Recorder::init() {}

void Mp4Recorder::handleBuffer(std::shared_ptr<Buffer> buffer)
{
    std::cout << "Mp4Recorder::handleBuffer" << std::endl;
    auto new_image = dynamic_pointer_cast<EncodedImage>(buffer);
    if (new_image)
        std::cout << "Mp4Recorder::get new image" << std::endl;
    else
        std::cout << "error image" << std::endl;
}
}
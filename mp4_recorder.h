//
// Created by 谢松德 on 2023/2/6.
//

#ifndef VIDEOPLAYER_MP4_RECORDER_H
#define VIDEOPLAYER_MP4_RECORDER_H

#include "recorder.h"
namespace engine {
class Mp4Recorder : public Recorder
{
public:
    bool init();
private:
    void handleBuffer(std::shared_ptr<Buffer> frame) override;
};

}



#endif //VIDEOPLAYER_MP4_RECORDER_H

//
// Created by 谢松德 on 2023/2/6.
//

#ifndef VIDEOPLAYER_MP4_RECORDER_H
#define VIDEOPLAYER_MP4_RECORDER_H

#include "recorder.h"
namespace engine {
class Mp4Recorder : public Recorder {
 public:
  bool init();

 private:
  std::shared_ptr<Buffer> handleBuffer(std::shared_ptr<Buffer> buffer) override;
};

}  // namespace engine

#endif  // VIDEOPLAYER_MP4_RECORDER_H

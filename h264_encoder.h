//
// Created by 谢松德 on 2023/2/5.
//

#ifndef VIDEOPLAYER_H264_ENCODER_H
#define VIDEOPLAYER_H264_ENCODER_H

#include "node.h"
namespace engine {
class H264Encoder : public Node {
 public:
  bool init() override;

 private:
  void handleBuffer(std::shared_ptr<Buffer> frame) override;
};
}  // namespace engine

#endif  // VIDEOPLAYER_H264_ENCODER_H

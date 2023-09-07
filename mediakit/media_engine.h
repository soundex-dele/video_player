//
// Created by 谢松德 on 2023/2/12.
//

#ifndef VIDEOPLAYER_MEDIA_ENGINE_H
#define VIDEOPLAYER_MEDIA_ENGINE_H
#include <string>
#include "pipeline.h"

namespace mediakit {

struct MediaOption {
  std::string name;

};

class MediaEngine {
 public:
  MediaEngine(const MediaOption& media_option);

  bool start();

 private:
  MediaOption media_option_;
};
}

#endif  //VIDEOPLAYER_MEDIA_ENGINE_H

//
// Created by 谢松德 on 2023/2/5.
//

#ifndef VIDEOPLAYER_H264_ENCODER_H
#define VIDEOPLAYER_H264_ENCODER_H

#include "node.h"
extern "C" {

#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>

#include <libavutil/channel_layout.h>
#include <libavutil/common.h>
#include <libavutil/frame.h>
#include <libavutil/samplefmt.h>

#include <libavutil/opt.h>
#include <libavutil/imgutils.h>
}
namespace engine {
class H264Encoder : public Node {
 public:
  ~H264Encoder();
  bool init() override;

 private:
  std::shared_ptr<Buffer> handleBuffer(std::shared_ptr<Buffer> buffer) override;
  const AVCodec *codec;
  AVCodecContext *c = NULL;
  AVFrame *frame;
  AVPacket *pkt;
  FILE *outFile, *inFile;
  AVFormatContext *ofmt_ctx = NULL;
  const AVOutputFormat *ofmt = NULL;


};
}  // namespace engine

#endif  // VIDEOPLAYER_H264_ENCODER_H

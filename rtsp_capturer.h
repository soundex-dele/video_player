#pragma once
#include "capturer.h"
extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/imgutils.h>
#include <libswscale/swscale.h>
}
namespace engine {
class RtspCapturer : public Capturer {
 public:
  ~RtspCapturer();
  bool init() override;
  void startCapture() override;

 private:
  std::shared_ptr<Buffer> handleBuffer(
      std::shared_ptr<Buffer> buffer) override {
    return buffer;
  }

 private:
  AVFormatContext* ctx_format = nullptr;
  AVCodecContext* ctx_codec = nullptr;
  const AVCodec* codec = nullptr;
  AVFrame* frame = av_frame_alloc();
  int stream_idx;
  SwsContext* ctx_sws = nullptr;
  const char* fin = "rtsp://127.0.0.1/live/test";
  AVStream* vid_stream = nullptr;
  AVPacket* pkt = nullptr;
  AVFrame* frameRGBA = nullptr;

};
}  // namespace engine
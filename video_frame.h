#pragma once
#include <cstdint>
extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/imgutils.h>
#include <libswscale/swscale.h>
}
namespace engine {
struct Buffer {
  virtual ~Buffer() {}
  char* data;
};

struct VideoFrame : public Buffer {
  VideoFrame(uint8_t** data, int* linesize, uint32_t width, uint32_t height, enum AVPixelFormat pix_fmt)
      : data(data), linesize(linesize), width(width), height(height), pix_fmt(pix_fmt) {}
  int width;
  int height;
  int* linesize;
  uint8_t** data;
  enum AVPixelFormat pix_fmt;
};

struct EncodedImage : public Buffer {
  EncodedImage(uint8_t* data, uint32_t width, uint32_t height)
      : data(data), width(width), height(height) {}
  uint32_t width;
  uint32_t height;
  uint8_t* data;
};

}  // namespace engine
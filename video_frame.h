#pragma once
#include <cstdint>
namespace engine {
struct Buffer
{
    virtual ~Buffer() {}
    char* data;
    size_t size;
};

struct VideoFrame : public Buffer
{
    VideoFrame(uint8_t* data, uint32_t width, uint32_t height)
        : data(data), width(width), height(height) {}
    uint32_t width;
    uint32_t height;
    uint8_t* data;
};

struct EncodedImage : public Buffer
{
    EncodedImage(uint8_t* data, uint32_t width, uint32_t height)
        : data(data), width(width), height(height) {}
    uint32_t width;
    uint32_t height;
    uint8_t* data;
};

} // namespace engine
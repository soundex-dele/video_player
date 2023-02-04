#pragma once
#include <memory>
#include <iostream>
#include "video_frame.h"
namespace engine {
class Node
{
public:
    void handle(std::unique_ptr<VideoFrame> frame);
    void setNextHandler(std::shared_ptr<Node> handler);

protected:
    virtual void handleFrame(VideoFrame* frame) {}
private:
    std::shared_ptr<Node> next_handler_;
};
}
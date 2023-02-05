#pragma once
#include <memory>
#include <vector>
#include <iostream>
#include "video_frame.h"
namespace engine {
class Node
{
public:
    void handle(std::shared_ptr<Buffer> buffer);
    void addSink(std::shared_ptr<Node> handler);

protected:
    virtual void handleBuffer(std::shared_ptr<Buffer> frame) {}
    std::shared_ptr<Buffer> buffer_;

private:
    std::vector<std::shared_ptr<Node> > next_handlers_;
};
}
#include "node.h"
#include "video_frame.h"
namespace engine {
void Node::handle(std::unique_ptr<VideoFrame> frame)
{
    handleFrame(frame.get());
    if (next_handler_)
        next_handler_->handle(std::move(frame));
}

void Node::setNextHandler(std::shared_ptr<Node> handler)
{
    next_handler_ = handler;
}

} // namespace engine
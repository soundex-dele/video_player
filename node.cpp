#include "node.h"
#include "video_frame.h"
namespace engine {
void Node::handle(std::shared_ptr<Buffer> buffer) {
  handleBuffer(buffer);
  std::shared_ptr<Buffer> cur_buffer;
  if (buffer_)
    cur_buffer = buffer_;
  else
    cur_buffer = buffer;
  for (auto handler : next_handlers_) {
    handler->handle(cur_buffer);
  }
}

void Node::addSink(std::shared_ptr<Node> handler) {
  next_handlers_.push_back(handler);
}

}  // namespace engine
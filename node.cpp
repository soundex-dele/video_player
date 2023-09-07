#include "node.h"
#include "video_frame.h"
namespace engine {
void Node::handle(std::shared_ptr<Buffer> buffer) {
  std::shared_ptr<Buffer> new_buffer;

  new_buffer = handleBuffer(buffer);

  for (auto handler : next_handlers_) {
    handler->handle(new_buffer);
  }
}

void Node::addSink(std::shared_ptr<Node> handler) {
  next_handlers_.push_back(handler);
}

}  // namespace engine
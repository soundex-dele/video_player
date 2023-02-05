#include "pipeline.h"
#include "node.h"
namespace engine {
void Pipeline::addNode(std::shared_ptr<Node> node) {
  node_lists_.push_back(node);
}

void Pipeline::linkNode(std::shared_ptr<Node> src_node,
                        std::shared_ptr<Node> sink_node) {
  auto node_iter = std::find_if(
      node_lists_.begin(), node_lists_.end(),
      [src_node](std::shared_ptr<Node> node) { return node == src_node; });
  if (node_iter != node_lists_.end()) {
    (*node_iter)->addSink(sink_node);
  } else {
    std::cout << "not found src node: " << src_node;
  }
}

void Pipeline::run() {
  for (auto node : node_lists_) {
    node->init();
  }
  auto first_node = node_lists_.front();
  first_node->run();
}
}  // namespace engine
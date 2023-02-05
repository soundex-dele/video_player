#pragma once
#include <memory>
#include <vector>

namespace engine {
class Node;
class Pipeline {
 public:
  void addNode(std::shared_ptr<Node> node);
  void linkNode(std::shared_ptr<Node> cur_node,
                std::shared_ptr<Node> next_node);
  void run();

 private:
  std::vector<std::shared_ptr<Node>> node_lists_;
};
}  // namespace engine

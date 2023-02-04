#pragma once
#include <vector>
#include <memory>

namespace engine {
class Node;
class Pipeline
{
public:
    void addNode(std::shared_ptr<Node> node);
    void linkNode(std::shared_ptr<Node> cur_node, std::shared_ptr<Node> next_node);
private:
    std::vector<std::shared_ptr<Node>> node_lists_;
};
} // namespace engine

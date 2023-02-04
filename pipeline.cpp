#include "pipeline.h"
#include "node.h"
namespace engine {
void Pipeline::addNode(std::shared_ptr<Node> node)
{
    node_lists_.push_back(node);
}

void Pipeline::linkNode(std::shared_ptr<Node> cur_node, std::shared_ptr<Node> next_node)
{
    auto node_iter = std::find_if(node_lists_.begin(), node_lists_.end(), [cur_node](std::shared_ptr<Node> node) {
            return node == cur_node;
        });
    if (node_iter != node_lists_.end())
    {
        (*node_iter)->setNextHandler(next_node);
    }
}
} // namespace app
#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include "video_frame.h"
namespace engine {
class Node {
 public:
  void handle(std::shared_ptr<Buffer> buffer);
  void addSink(std::shared_ptr<Node> handler);
  virtual bool init() {}
  virtual void run() {}

 protected:
  virtual std::shared_ptr<Buffer> handleBuffer(std::shared_ptr<Buffer> buffer) {
  }

 private:
  std::vector<std::shared_ptr<Node>> next_handlers_;
};
}  // namespace engine
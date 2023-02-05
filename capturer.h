#pragma once
#include "node.h"
namespace engine {
class Capturer : public Node {
 public:
  virtual ~Capturer() = default;
  virtual void startCapture() = 0;
  void run() override { startCapture(); }
};
}  // namespace engine
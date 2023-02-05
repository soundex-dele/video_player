#pragma once
#include "renderer.h"
extern "C" {
#include <GL/glew.h>
#include <GL/glut.h>
#include <GLFW/glfw3.h>
}

namespace engine {
class GlRenderer : public Renderer {
 public:
  GlRenderer();
  bool init();

 private:
  void handleBuffer(std::shared_ptr<Buffer> frame) override;
  GLFWwindow* window;
  GLuint tex_handle;
};
}  // namespace engine
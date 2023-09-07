#pragma once
#include "renderer.h"
#include <shader_s.h>

extern "C" {
//#include <GL/glew.h>
//#include <GL/glut.h>
#include "glad/glad.h"

#include <GLFW/glfw3.h>
}
extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/imgutils.h>
#include <libswscale/swscale.h>
}
int test(uint8_t* data);
namespace engine {
class GlRenderer : public Renderer {
 public:
  bool init();

 private:
  std::shared_ptr<Buffer> handleBuffer(std::shared_ptr<Buffer> buffer) override;
  GLFWwindow* window;
  unsigned int texture;
  struct SwsContext* swsContext;
  uint8_t* frame_data = nullptr;
  unsigned int VBO;
  unsigned int VAO;
  unsigned int EBO;
  Shader ourShader;

};
}  // namespace engine
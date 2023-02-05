#include "gl_renderer.h"
#define WIDTH 640
#define HEIGHT 480
namespace engine {
bool GlRenderer::init() {
  if (!glfwInit())
    return false;

  window =
      glfwCreateWindow(WIDTH, HEIGHT, "FFmpeg and OpenGL Example", NULL, NULL);
  if (!window) {
    glfwTerminate();
    return false;
  }

  glfwMakeContextCurrent(window);
  glewInit();
  glGenTextures(1, &tex_handle);
  glBindTexture(GL_TEXTURE_2D, tex_handle);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  return true;
}

GlRenderer::GlRenderer() {}

void GlRenderer::handleBuffer(std::shared_ptr<Buffer> frame) {
  std::cout << "GlRenderer::handleFrame" << std::endl;
  auto new_frame = dynamic_pointer_cast<VideoFrame>(frame);
  if (new_frame)
    std::cout << "GlRenderer::get new frame" << std::endl;
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // setup orthographic projection
  int window_width, window_height;
  glfwGetFramebufferSize(window, &window_width, &window_height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, window_width, window_height, 0, -1, 1);
  glMatrixMode(GL_MODELVIEW);
  glBindTexture(GL_TEXTURE_2D, tex_handle);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, new_frame->width, new_frame->height, 0,
               GL_RGBA, GL_UNSIGNED_BYTE, new_frame->data);

  // Render whatever you want
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, tex_handle);
  glBegin(GL_QUADS);
  glTexCoord2d(0, 0);
  glVertex2i(400, 400);
  glTexCoord2d(1, 0);
  glVertex2i(400 + new_frame->width, 400);
  glTexCoord2d(1, 1);
  glVertex2i(400 + new_frame->width, 400 + new_frame->height);
  glTexCoord2d(0, 1);
  glVertex2i(400, 400 + new_frame->height);
  glEnd();
  glDisable(GL_TEXTURE_2D);

  glfwSwapBuffers(window);
  glfwPollEvents();
}

}  // namespace engine
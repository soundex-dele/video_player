#include "gl_renderer.h"
#define STB_IMAGE_IMPLEMENTATION

#include <stb_image.h>
#define WIDTH 1920
#define HEIGHT 1080
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
  // make sure the viewport matches the new window dimensions; note that width and
  // height will be significantly larger than specified on retina displays.
  glViewport(0, 0, width, height);
}
void processInput(GLFWwindow *window)
{
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

namespace engine {

bool GlRenderer::init() {
  // glfw: initialize and configure
  // ------------------------------
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  // glfw window creation
  // --------------------
  window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", NULL, NULL);
  if (window == NULL)
  {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  // glad: load all OpenGL function pointers
  // ---------------------------------------
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  // build and compile our shader zprogram
  // ------------------------------------
  ourShader = Shader("/Users/xiesongde/workspace/flutter/video_player/texture.vs",
            "/Users/xiesongde/workspace/flutter/video_player/texture.fs");

  // set up vertex data (and buffer(s)) and configure vertex attributes
  // ------------------------------------------------------------------
  float vertices[] = {
      // positions          // colors           // texture coords
      0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
      0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
      -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
      -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left
  };
  unsigned int indices[] = {
      0, 1, 3, // first triangle
      1, 2, 3  // second triangle
  };
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  // position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  // color attribute
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
  // texture coord attribute
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
  glEnableVertexAttribArray(2);


  // load and create a texture
  // -------------------------
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
  // set the texture wrapping parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  // set texture filtering parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  return true;
}


std::shared_ptr<Buffer> GlRenderer::handleBuffer(
    std::shared_ptr<Buffer> buffer) {
  //  std::cout << "GlRenderer::handleFrame" << std::endl;
  auto new_frame = dynamic_pointer_cast<VideoFrame>(buffer);
  if (new_frame)
    //    std::cout << "GlRenderer::get new frame" << std::endl;
    swsContext = sws_getContext(
        new_frame->width, new_frame->height, new_frame->pix_fmt, WIDTH, HEIGHT,
        AV_PIX_FMT_RGBA, SWS_BILINEAR, NULL, NULL, NULL);
  if (!swsContext) {
    std::cout << "Couldn't initialize sws_scaler" << std::endl;
  }
  frame_data = new uint8_t[WIDTH * HEIGHT * 4];
  uint8_t* dest[4] = {frame_data, NULL, NULL, NULL};
  int dest_linesize[4] = {WIDTH * 4, 0, 0, 0};
  sws_scale(swsContext, new_frame->data, new_frame->linesize, 0,
            new_frame->height, dest, dest_linesize);
//  int width, height, nrChannels;
//  unsigned char *data = stbi_load("/Users/xiesongde/workspace/flutter/video_player/wall.jpg", &width, &height, &nrChannels, 0);
//  stbi_image_free(data);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, WIDTH, HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, frame_data);
  glGenerateMipmap(GL_TEXTURE_2D);
  {
    // input
    // -----
    processInput(window);

    // render
    // ------
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // bind Texture
//    glBindTexture(GL_TEXTURE_2D, texture);

    // render container
    ourShader.use();
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    // -------------------------------------------------------------------------------
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

//  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//  glEnable(GL_TEXTURE_2D);
//
//  // setup orthographic projection
//  int window_width, window_height;
//  glfwGetFramebufferSize(window, &window_width, &window_height);
//  glMatrixMode(GL_PROJECTION);
//  glLoadIdentity();
//  glOrtho(0, window_width, window_height, 0, -1, 1);
//  glMatrixMode(GL_MODELVIEW);
//  glBindTexture(GL_TEXTURE_2D, tex_handle);
//  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, WIDTH, HEIGHT, 0, GL_RGBA,
//               GL_UNSIGNED_BYTE, frame_data);
//
//  // Render whatever you want
//  glBindTexture(GL_TEXTURE_2D, tex_handle);
//  glBegin(GL_QUADS);
//  glTexCoord2d(0, 0);
//  glVertex2i(0, 0);
//  glTexCoord2d(1, 0);
//  glVertex2i(0 + WIDTH, 0);
//  glTexCoord2d(1, 1);
//  glVertex2i(0 + HEIGHT, 0 + HEIGHT);
//  glTexCoord2d(0, 1);
//  glVertex2i(0, 0 + HEIGHT);
//
//  glTexCoord2f( 0.0, 0.0 ); glVertex3f( -1.0, -1.0, 1.0 );
//  glTexCoord2f( 1.0, 0.0 ); glVertex3f( 1.0, -1.0, 1.0 );
//  glTexCoord2f( 1.0, 1.0 ); glVertex3f( 1.0, 1.0, 1.0 );
//  glTexCoord2f( 0.0, 1.0 ); glVertex3f( -1.0, 1.0, 1.0 );
//
//  glEnd();
//  glDisable(GL_TEXTURE_2D);
//
//  glfwSwapBuffers(window);
//  glfwPollEvents();
  delete[] frame_data;
  return buffer;
}

}  // namespace engine
// VideoPlayer.cpp : Defines the entry point for the application.
//

#include "video_player.h"
#include "Poco/Stopwatch.h"
#include "Poco/Thread.h"
#include "Poco/Timer.h"
#include "camera_capturer_mac.h"
#include "gl_renderer.h"
#include "h264_encoder.h"
#include "mp4_recorder.h"
#include "pipeline.h"
#include "rtsp_capturer.h"

using namespace std;

#include <iostream>

int main() {
  cout << "Hello CMake." << endl;

  std::shared_ptr<engine::Pipeline> pipeline =
      std::make_shared<engine::Pipeline>();
  std::shared_ptr<engine::RtspCapturer> capture_node =
      std::make_shared<engine::RtspCapturer>();
  std::shared_ptr<engine::GlRenderer> render_node =
      std::make_shared<engine::GlRenderer>();
  std::shared_ptr<engine::H264Encoder> encoder_node =
      std::make_shared<engine::H264Encoder>();
  std::shared_ptr<engine::Mp4Recorder> recorder_node =
      std::make_shared<engine::Mp4Recorder>();

  pipeline->addNode(capture_node);
  pipeline->addNode(render_node);
  pipeline->addNode(encoder_node);
  pipeline->addNode(recorder_node);

  pipeline->linkNode(capture_node, render_node);
  pipeline->linkNode(capture_node, encoder_node);
  pipeline->linkNode(encoder_node, recorder_node);

  pipeline->run();

  return 0;
}
////#include <GL/glew.h>
//#include <GLFW/glfw3.h>
// int main(void)
//{
//    GLFWwindow* window;
//    /* Initialize the library */
//    if (!glfwInit())
//        return -1;
//    /* Create a windowed mode window and its OpenGL context */
//    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
//    if (!window)
//    {
//        glfwTerminate();
//        return -1;
//    }
//    /* Make the window's context current */
//    glfwMakeContextCurrent(window);
//
//    /* Loop until the user closes the window */
//    while (!glfwWindowShouldClose(window))
//    {
//        /* Render here */
//        /* Swap front and back buffers */
//        glfwSwapBuffers(window);
//        /* Poll for and process events */
//        glfwPollEvents();
//    }
//
//    glfwTerminate();
//    return 0;
//}

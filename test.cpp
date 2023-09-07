//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//#define STB_IMAGE_IMPLEMENTATION
//
//#include <stb_image.h>
//
//#include <shader_s.h>
//
//#include <iostream>
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void processInput(GLFWwindow *window);
//
//// settings
//const unsigned int SCR_WIDTH = 800;
//const unsigned int SCR_HEIGHT = 600;
//
//int test(uint8_t* data)
//{
//
//  // load image, create texture and generate mipmaps
////  int width, height, nrChannels;
//  // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
////  unsigned char *data = stbi_load("/Users/xiesongde/workspace/flutter/video_player/wall.jpg", &width, &height, &nrChannels, 0);
//  if (data)
//  {
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1920, 1080, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
//    glGenerateMipmap(GL_TEXTURE_2D);
//  }
//  else
//  {
//    std::cout << "Failed to load texture" << std::endl;
//  }
//  stbi_image_free(data);
//
//
//  // render loop
//  // -----------
//  while (!glfwWindowShouldClose(window))
//  {
//    // input
//    // -----
//    processInput(window);
//
//    // render
//    // ------
//    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//    glClear(GL_COLOR_BUFFER_BIT);
//
//    // bind Texture
//    glBindTexture(GL_TEXTURE_2D, texture);
//
//    // render container
//    ourShader.use();
//    glBindVertexArray(VAO);
//    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//
//    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
//    // -------------------------------------------------------------------------------
//    glfwSwapBuffers(window);
//    glfwPollEvents();
//  }
//
//  // optional: de-allocate all resources once they've outlived their purpose:
//  // ------------------------------------------------------------------------
//  glDeleteVertexArrays(1, &VAO);
//  glDeleteBuffers(1, &VBO);
//  glDeleteBuffers(1, &EBO);
//
//  // glfw: terminate, clearing all previously allocated GLFW resources.
//  // ------------------------------------------------------------------
//  glfwTerminate();
//  return 0;
//}
//
//// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
//// ---------------------------------------------------------------------------------------------------------
//void processInput(GLFWwindow *window)
//{
//  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//    glfwSetWindowShouldClose(window, true);
//}
//
//// glfw: whenever the window size changed (by OS or user resize) this callback function executes
//// ---------------------------------------------------------------------------------------------
//void framebuffer_size_callback(GLFWwindow* window, int width, int height)
//{
//  // make sure the viewport matches the new window dimensions; note that width and
//  // height will be significantly larger than specified on retina displays.
//  glViewport(0, 0, width, height);
//}
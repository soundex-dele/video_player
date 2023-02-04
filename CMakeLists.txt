# CMakeList.txt : CMake project for VideoPlayer, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("VideoPlayer")

# Add source to this project's executable.
add_executable (VideoPlayer "video_player.cpp" "video_player.h" "pipeline.cpp" "pipeline.h" "pipeline_unittest.cpp" "node.h" "node.cpp" "video_frame.h" "capturer.h" "rtsp_capturer.h" "renderer.h" "gl_renderer.h" "camera_capturer_win.h" "camera_capturer_win.cpp" "gl_renderer.cpp")

# TODO: Add tests and install targets if needed.

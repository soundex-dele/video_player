# CMakeList.txt : CMake project for VideoPlayer, include source and define
# project specific logic here.
#
cmake_minimum_required(VERSION 3.8)
set(CMAKE_CXX_STANDARD 17)
project("VideoPlayer")
find_package(Poco REQUIRED Foundation)
find_package(PkgConfig REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(FREEGLUT REQUIRED)
pkg_check_modules(deps REQUIRED IMPORTED_TARGET glib-2.0)
pkg_check_modules(LIBAV REQUIRED IMPORTED_TARGET
        libavdevice
        libavfilter
        libavformat
        libavcodec
        libswresample
        libswscale
        libavutil
        )
# Add source to this project's executable.
include_directories(PkgConfig::LIBAV ${OPENGL_INCLUDE_DIRS} ${FREEGLUT_INCLUDE_DIRS})
add_executable(VideoPlayer "video_player.cpp" "video_player.h" "pipeline.cpp" "pipeline.h" "pipeline_unittest.cpp" "node.h" "node.cpp" "video_frame.h" "capturer.h" "rtsp_capturer.h" "renderer.h" "gl_renderer.h" "camera_capturer_win.h" "camera_capturer_win.cpp" "gl_renderer.cpp" camera_capturer_mac.cpp camera_capturer_mac.h rtsp_capturer.cpp encoder.cpp encoder.h h264_encoder.cpp h264_encoder.h mp4_recorder.cpp mp4_recorder.h recorder.h)
target_link_libraries(VideoPlayer PRIVATE Poco::Foundation PkgConfig::deps
        PkgConfig::LIBAV ${OPENGL_LIBRARIES} ${FREEGLUT_LIBRARIES} ${GLEW_LIBRARIES} /usr/local/Cellar/glew/2.2.0_1/lib/libGLEW.a glfw)
# TODO: Add tests and install targets if needed.

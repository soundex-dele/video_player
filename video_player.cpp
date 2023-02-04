// VideoPlayer.cpp : Defines the entry point for the application.
//

#include "video_player.h"
#include "pipeline.h"
#include "rtsp_capturer.h"
#include "camera_capturer_win.h"

#include "gl_renderer.h"

using namespace std;

int main()
{
	cout << "Hello CMake." << endl;
	std::shared_ptr<engine::Pipeline> pipeline = std::make_shared<engine::Pipeline>();
	std::shared_ptr<engine::CameraCapturerWin> capture_node = std::make_shared<engine::CameraCapturerWin>();
	std::shared_ptr<engine::Node> render_node = std::make_shared<engine::GlRenderer>();

	pipeline->addNode(capture_node);
	pipeline->addNode(render_node);

	pipeline->linkNode(capture_node, render_node);
	capture_node->startCapture();
	return 0;
}

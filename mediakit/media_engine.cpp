//
// Created by 谢松德 on 2023/2/12.
//

#include "media_engine.h"
#include "camera_capturer_mac.h"
#include "gl_renderer.h"
#include "h264_encoder.h"
#include "mp4_recorder.h"
#include "pipeline.h"
#include "rtsp_capturer.h"
namespace mediakit {

MediaEngine::MediaEngine(const MediaOption& media_option)
    : media_option_(media_option) {}

bool MediaEngine::start() {
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

}
}
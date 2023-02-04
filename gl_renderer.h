#pragma once
#include "renderer.h"
namespace engine {
class GlRenderer : public Renderer
{
public:
private:
    void handleFrame(VideoFrame* frame) override;

};
}
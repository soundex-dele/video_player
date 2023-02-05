//
// Created by 谢松德 on 2023/2/4.
//
#include "rtsp_capturer.h"
#define WIDTH 640
#define HEIGHT 480
namespace engine {
RtspCapturer::~RtspCapturer() {
    avformat_close_input(&ctx_format);
    av_packet_unref(pkt);
    avcodec_free_context(&ctx_codec);
    avformat_free_context(ctx_format);
}

int RtspCapturer::init() {
    frame = av_frame_alloc();
    frameRGBA = av_frame_alloc();
    pkt = av_packet_alloc();

    if (int ret = avformat_open_input(&ctx_format, fin, nullptr, nullptr) != 0) {
        std::cout << 1 << std::endl;
        return ret;
    }
    if (avformat_find_stream_info(ctx_format, nullptr) < 0) {
        std::cout << 2 << std::endl;
        return -1; // Couldn't find stream information
    }
    av_dump_format(ctx_format, 0, fin, false);

    for (int i = 0; i < ctx_format->nb_streams; i++)
        if (ctx_format->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
            stream_idx = i;
            vid_stream = ctx_format->streams[i];
            break;
        }
    if (vid_stream == nullptr) {
        std::cout << 4 << std::endl;
        return -1;
    }

    codec = avcodec_find_decoder(vid_stream->codecpar->codec_id);
    if (!codec) {
        fprintf(stderr, "codec not found\n");
        exit(1);
    }
    ctx_codec = avcodec_alloc_context3(codec);

    if(avcodec_parameters_to_context(ctx_codec, vid_stream->codecpar)<0)
        std::cout << 512;
    if (avcodec_open2(ctx_codec, codec, nullptr)<0) {
        std::cout << 5;
        return -1;
    }
//    uint8_t *buffer = (uint8_t *)av_malloc(av_image_get_linesize(AV_PIX_FMT_RGBA, WIDTH, HEIGHT));
//    av_image_fill_arrays(frameRGBA->data, frameRGBA->linesize, buffer, AV_PIX_FMT_RGBA, WIDTH, HEIGHT, 1);

    swsContext = sws_getContext(ctx_format->streams[stream_idx]->codecpar->width,
                                                   ctx_format->streams[stream_idx]->codecpar->height,
                                ctx_codec->pix_fmt,ctx_format->streams[stream_idx]->codecpar->width / 2,
                                ctx_format->streams[stream_idx]->codecpar->height / 2, AV_PIX_FMT_RGBA, SWS_BILINEAR, NULL, NULL, NULL);
    if (!swsContext){
        std::cout << "Couldn't initialize sws_scaler" << std::endl;
        return false;
    }
    frame_data = new uint8_t[ctx_format->streams[stream_idx]->codecpar->width*
        ctx_format->streams[stream_idx]->codecpar->height * 4];
}

void RtspCapturer::startCapture() {
    while(av_read_frame(ctx_format, pkt) >= 0){
        if (pkt->stream_index == stream_idx) {
            int ret = avcodec_send_packet(ctx_codec, pkt);
            if (ret < 0 || ret == AVERROR(EAGAIN) || ret == AVERROR_EOF) {
                std::cout << "avcodec_send_packet: " << ret << std::endl;
                break;
            }
            while (ret  >= 0) {
                ret = avcodec_receive_frame(ctx_codec, frame);
                if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF) {
                    //std::cout << "avcodec_receive_frame: " << ret << std::endl;
                    break;
                }
                std::cout << "frame: " << ctx_codec->frame_number << " width: " <<
                    ctx_format->streams[stream_idx]->codecpar->width << std::endl;
                uint8_t* dest[4] = { frame_data, NULL, NULL, NULL};
                int dest_linesize[4] =  { ctx_format->streams[stream_idx]->codecpar->width * 4, 0, 0, 0 };
                sws_scale(swsContext, frame->data, frame->linesize, 0,
                          ctx_format->streams[stream_idx]->codecpar->height,
                          dest, dest_linesize);

                handle(std::make_shared<VideoFrame>(frame_data,
                                                    ctx_format->streams[stream_idx]->codecpar->width,
                                                    ctx_format->streams[stream_idx]->codecpar->height));
            }
        }
        av_packet_unref(pkt);
    }
}

}
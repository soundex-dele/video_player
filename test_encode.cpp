#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <cstring>

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/opt.h>
#include <libavutil/imgutils.h>
}

int main(int argc, char** argv) {
  // 初始化FFmpeg库

  // 打开输出文件
  AVFormatContext* output_format_ctx = nullptr;
  const char* output_filename = "output.mp4";
  int ret = avformat_alloc_output_context2(&output_format_ctx, nullptr, nullptr,
                                           output_filename);
  if (ret < 0) {
    std::cerr << "Failed to create output context: " << av_err2str(ret)
              << std::endl;
    return EXIT_FAILURE;
  }

  // 打开输出文件
  ret = avio_open(&output_format_ctx->pb, output_filename, AVIO_FLAG_WRITE);
  if (ret < 0) {
    std::cerr << "Failed to open output file: " << av_err2str(ret) << std::endl;
    return EXIT_FAILURE;
  }

  // 创建视频流
  const AVCodec* codec = avcodec_find_encoder(AV_CODEC_ID_H264);
  if (!codec) {
    std::cerr << "Failed to find H.264 codec" << std::endl;
    return EXIT_FAILURE;
  }
  AVStream* stream = avformat_new_stream(output_format_ctx, codec);
  if (!stream) {
    std::cerr << "Failed to create output stream" << std::endl;
    return EXIT_FAILURE;
  }
  AVCodecContext* codec_ctx = stream->codec;
  codec_ctx->codec_id = codec->id;
  codec_ctx->width = 1920;                  // 输入YUV的宽度
  codec_ctx->height = 1080;                 // 输入YUV的高度
  codec_ctx->time_base = {1, 25};           // 输入YUV的帧率
  codec_ctx->framerate = {25, 1};           // 输出视频的帧率
  codec_ctx->gop_size = 10;                 // 关键帧间隔
  codec_ctx->max_b_frames = 1;              // 最大B帧数
  codec_ctx->pix_fmt = AV_PIX_FMT_YUV420P;  // 输入YUV的像素格式
  ret = avcodec_open2(codec_ctx, codec, nullptr);
  if (ret < 0) {
    std::cerr << "Failed to open codec: " << av_err2str(ret) << std::endl;
    return EXIT_FAILURE;
  }

  // 创建帧和数据包
  AVFrame* frame = av_frame_alloc();
  if (!frame) {
    std::cerr << "Failed to allocate frame" << std::endl;
    return EXIT_FAILURE;
  }
  frame->format = codec_ctx->pix_fmt;
  frame->width = codec_ctx->width;
  frame->height = codec_ctx->height;
  ret = av_frame_get_buffer(frame, 0);
  if (ret < 0) {
    std::cerr << "Failed to allocate frame data: " << av_err2str(ret)
              << std::endl;
    return EXIT_FAILURE;
  }
  AVPacket* packet = av_packet_alloc();
  if (!packet) {
    std::cerr << "Failed to allocate packet" << std::endl;
    return EXIT_FAILURE;
  }

  // 打开输入YUV文件
  const char* input_filename = "input.yuv";
  FILE* input_file = fopen(input_filename, "rb");
  if (!input_file) {
    std::cerr << "Failed to open input file: " << std::strerror(errno)
              << std::endl;
    return EXIT_FAILURE;
  }
  // 打开输入YUV文件
  const char* input_filename = "input.yuv";
  FILE* input_file = fopen(input_filename, "rb");
  if (!input_file) {
    std::cerr << "Failed to open input file: " << std::strerror(errno)
              << std::endl;
    return EXIT_FAILURE;
  }

  // 编码每一帧并写入文件
  int frame_index = 0;
  while (true) {
    // 读取一帧YUV数据
    ret = av_frame_make_writable(frame);
    if (ret < 0) {
      std::cerr << "Failed to make frame writable: " << av_err2str(ret)
                << std::endl;
      return EXIT_FAILURE;
    }
    ret = av_image_read(frame->data, frame->linesize,
                        reinterpret_cast<const uint8_t**>(&input_file),
                        codec_ctx->pix_fmt, codec_ctx->width, codec_ctx->height,
                        1);
    if (ret < 0) {
      if (ret == AVERROR_EOF) {
        break;
      } else {
        std::cerr << "Failed to read input image: " << av_err2str(ret)
                  << std::endl;
        return EXIT_FAILURE;
      }
    }
    // 编码一帧
    ret = avcodec_send_frame(codec_ctx, frame);
    if (ret < 0) {
      std::cerr << "Failed to send frame to codec: " << av_err2str(ret)
                << std::endl;
      return EXIT_FAILURE;
    }
    while (true) {
      ret = avcodec_receive_packet(codec_ctx, packet);
      if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF) {
        break;
      } else if (ret < 0) {
        std::cerr << "Failed to receive packet from codec: " << av_err2str(ret)
                  << std::endl;
        return EXIT_FAILURE;
      }

      // 将数据包写入输出文件
      av_packet_rescale_ts(packet, codec_ctx->time_base, stream->time_base);
      packet->stream_index = stream->index;
      ret = av_interleaved_write_frame(output_format_ctx, packet);
      if (ret < 0) {
        std::cerr << "Failed to write packet to output file: "
                  << av_err2str(ret) << std::endl;
        return EXIT_FAILURE;
      }
      av_packet_unref(packet);
    }

    ++frame_index;
    // 编码结束
    ret = avcodec_send_frame(codec_ctx, nullptr);
    if (ret < 0) {
      std::cerr << "Failed to send flush frame to codec: " << av_err2str(ret)
                << std::endl;
      return EXIT_FAILURE;
    }
    while (true) {
      ret = avcodec_receive_packet(codec_ctx, packet);
      if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF) {
        break;
      } else if (ret < 0) {
        std::cerr << "Failed to receive packet from codec: " << av_err2str(ret)
                  << std::endl;
        return EXIT_FAILURE;
      }
      // 将数据包写入输出文件
      av_packet_rescale_ts(packet, codec_ctx->time_base, stream->time_base);
      packet->stream_index = stream->index;
      ret = av_interleaved_write_frame(output_format_ctx, packet);
      if (ret < 0) {
        std::cerr << "Failed to write packet to output file: "
                  << av_err2str(ret) << std::endl;
        return EXIT_FAILURE;
      }
      av_packet_unref(packet);
    }

    // 写入文件尾
    ret = av_write_trailer(output_format_ctx);
    if (ret < 0) {
      std::cerr << "Failed to write output file trailer: " << av_err2str(ret)
                << std::endl;
      return EXIT_FAILURE;
    }
    // 释放资源
    av_frame_free(&frame);
    av_packet_free(&packet);
    avcodec_free_context(&codec_ctx);
    avio_closep(&output_format_ctx->pb);
    avformat_free_context(output_format_ctx);

    std::cout << "Encoding successful" << std::endl;

    return EXIT_SUCCESS;
  }
}
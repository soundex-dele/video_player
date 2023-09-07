//
// Created by 谢松德 on 2023/2/5.
//

#include "h264_encoder.h"
static int f_index = 0;

static void encode(AVCodecContext *ctx, AVFrame *frame, AVPacket *pkt,
                   FILE *output) {
  int ret;
  //注意：需要在送去编码器前指定 pts
  frame->pts = f_index++;

  /* send the frame for encoding */
  ret = avcodec_send_frame(ctx, frame);
  if (ret < 0) {
    fprintf(stderr, "Error sending the frame to the encoder\n");
    exit(1);
  }

  /* read all the available output packets (in general there may be any
   * number of them */
  while (ret >= 0) {
    ret = avcodec_receive_packet(ctx, pkt);
    if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF)
      return;
    else if (ret < 0) {
      fprintf(stderr, "Error during encoding\n");
      exit(1);
    }

    fwrite(pkt->data, 1, pkt->size, output);
    av_packet_unref(pkt);
  }
}

namespace engine {
H264Encoder::~H264Encoder() {
  /* flush the encoder */
  encode(c, NULL, pkt, outFile);

  printf("Write file trailer.\n");

  //Write file trailer//（封装——文件尾）
  av_write_trailer(ofmt_ctx);

  fclose(outFile);

  av_frame_free(&frame);
  av_packet_free(&pkt);
  avcodec_free_context(&c);
  avformat_free_context(ofmt_ctx);

}
bool H264Encoder::init() {
  const char *outFilename, *inFilename;

  int ret;

  outFilename = "test.h264";
  inFilename = "source/Kobe.yuv";

  remove(outFilename);

  //获取 AVCodec
  codec = avcodec_find_encoder(AV_CODEC_ID_H264);
  if (!codec) {
    fprintf(stderr, "Codec not found\n");
    exit(1);
  }
  //获取AVCodecContext
  c = avcodec_alloc_context3(codec);
  if (!c) {
    fprintf(stderr, "Could not allocate audio codec context\n");
    exit(1);
  }

  //设置编码参数：Stream #0:0: Video: h264 (Main), yuv420p(progressive), 384x216 [SAR 1:1 DAR 16:9], 15 fps, 15 tbr, 1200k tbn, 30 tbc
  /* put sample parameters */
  c->bit_rate = 120000;
  /* resolution must be a multiple of two */
  c->width = 1000;
  c->height = 418;
  /* frames per second */
  c->time_base = (AVRational) {1, 15};
  c->framerate = (AVRational) {15, 1};

  /* emit one intra frame every ten frames
   * check frame pict_type before passing frame
   * to encoder, if frame->pict_type is AV_PICTURE_TYPE_I
   * then gop_size is ignored and the output of encoder
   * will always be I frame irrespective to gop_size
   */
  c->gop_size = 10;
  c->max_b_frames = 1;
  c->pix_fmt = AV_PIX_FMT_YUV420P;

  if (codec->id == AV_CODEC_ID_H264)
    av_opt_set(c->priv_data, "preset", "slow", 0);


  //初始化AVCodecContext
  if (avcodec_open2(c, codec, NULL) < 0) {
    fprintf(stderr, "Could not open codec\n");
    exit(1);
  }

//  inFile = fopen(inFilename, "rb");
//  if (!inFile) {
//    fprintf(stderr, "Could not open %s\n", inFilename);
//    exit(1);
//  }

  outFile = fopen(outFilename, "wb+");
  if (!outFile) {
    fprintf(stderr, "Could not open %s\n", outFilename);
    exit(1);
  }

  /* packet for holding encoded output */
  pkt = av_packet_alloc();
  if (!pkt) {
    fprintf(stderr, "could not allocate the packet\n");
    exit(1);
  }

  /* frame containing input raw audio */
  frame = av_frame_alloc();
  if (!frame) {
    fprintf(stderr, "Could not allocate audio frame\n");
    exit(1);
  }

  //设置 AVFrame的参数
  frame->format = c->pix_fmt;
  frame->width = c->width;
  frame->height = c->height;

  /* allocate the data buffers */
  ret = av_frame_get_buffer(frame, 32);
  if (ret < 0) {
    fprintf(stderr, "Could not allocate audio data buffers\n");
    exit(1);
  }

}

std::shared_ptr<Buffer> H264Encoder::handleBuffer(
    std::shared_ptr<Buffer> buffer) {
//  std::cout << "H264Encoder::handleBuffer" << std::endl;
  auto new_frame = dynamic_pointer_cast<VideoFrame>(buffer);
  int ret;
//  if (new_frame)
//    std::cout << "H264Encoder::get new frame" << std::endl;
    /* make sure the frame is writable -- makes a copy if the encoder
     * kept a reference internally */
  ret = av_frame_make_writable(frame);
  frame->data[0] = new_frame->data[0];
  frame->data[1] = new_frame->data[1];
  frame->data[2] = new_frame->data[2];
  frame->data[3] = new_frame->data[3];

  if (ret < 0)
      exit(1);

  encode(c, frame, pkt, outFile);

  /* flush the encoder */
  return std::make_shared<EncodedImage>(nullptr, 0, 0);
}
}  // namespace engine
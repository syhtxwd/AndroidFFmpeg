//
// Created by syh on 2021-08-27.
//

#ifndef LEANFFMPEG_SINGLEVIDEORECORDER_H
#define LEANFFMPEG_SINGLEVIDEORECORDER_H

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/avutil.h>
#include <libswscale/swscale.h>
#include <libavutil/imgutils.h>
}

#include "ThreadSafeQueue.h"
#include "ImageDef.h"
#include "thread"
#include "LogUtil.h"


class SingleVideoRecorder {
public:
    SingleVideoRecorder(const char* outUrl, int frameWidth, int frameHeight, long bitRate, int fps);
    ~SingleVideoRecorder();

    int StartRecord();
    int OnFrame2Encode(NativeImage *inputFrame);
    int StopRecord();

private:
    static void StartH264EncoderThread(SingleVideoRecorder *context);
    int EncodeFrame(AVFrame *pFrame);
private:
    ThreadSafeQueue<NativeImage *> m_frameQueue;
    char m_outUrl[1024] = {0};
    int m_frameWidth;
    int m_frameHeight;
    int m_frameIndex = 0;
    long m_bitRate;
    int m_frameRate;
    AVPacket m_avPacket;
    AVFrame  *m_pFrame = nullptr;
    uint8_t *m_pFrameBuffer = nullptr;
    AVCodec  *m_pCodec = nullptr;
    AVStream *m_pStream = nullptr;
    AVCodecContext *m_pCodecCtx = nullptr;
    AVFormatContext *m_pFormatCtx = nullptr;
    std::thread *m_encodeThread = nullptr;
    SwsContext *m_SwsContext = nullptr;
    volatile int m_exit = 0;
};


#endif //LEANFFMPEG_SINGLEVIDEORECORDER_H

//
// Created by syh on 2021-08-29.
//

#ifndef LEANFFMPEG_SINGLEAUDIORECORDER_H
#define LEANFFMPEG_SINGLEAUDIORECORDER_H

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/avutil.h>
#include <libswscale/swscale.h>
#include <libavutil/imgutils.h>
#include <libswresample/swresample.h>
#include <libavutil/opt.h>
}

#include "ThreadSafeQueue.h"
#include "thread"
#include "LogUtil.h"
#include "AudioRender.h"

using namespace std;

#define DEFAULT_SAMPLE_RATE    44100
#define DEFAULT_CHANNEL_LAYOUT AV_CH_LAYOUT_STEREO

class SingleAudioRecorder {
public:
    SingleAudioRecorder(const char *outUrl, int sampleRate, int channelLayout, int sampleFormat){}
    ~SingleAudioRecorder(){}
    //开始录制
    int StartRecord(){ return 0;}
    //接收音频数据
    int OnFrame2Encode(AudioFrame *inputFrame){ return 0; }
    //停止录制
    int StopRecord() { return 0; }

private:
    //编码循环
    static void StartAACEncoderThread(SingleAudioRecorder *context){}
    //编码一帧的函数
    int EncodeFrame(AVFrame *pFrame){ return 0;}
private:
    ThreadSafeQueue<AudioFrame *> m_frameQueue;
    char m_outUrl[1024] = {0};
    int m_frameIndex = 0;
    int m_sampleRate;
    int m_channelLayout;
    int m_sampleFormat;
    AVPacket m_avPacket;
    AVFrame  *m_pFrame = nullptr;
    uint8_t *m_pFrameBuffer = nullptr;
    int m_frameBufferSize;
    AVCodec  *m_pCodec = nullptr;
    AVStream *m_pStream = nullptr;
    AVCodecContext *m_pCodecCtx = nullptr;
    AVFormatContext *m_pFormatCtx = nullptr;
    SwrContext *m_swrCtx = nullptr;
    thread *m_encodeThread = nullptr;
    volatile int m_exit = 0;
};


#endif //LEANFFMPEG_SINGLEAUDIORECORDER_H

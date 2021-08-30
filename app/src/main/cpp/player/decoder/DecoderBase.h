//
// Created by syh on 2021-08-24.
//

#ifndef LEANFFMPEG_DECODERBASE_H
#define LEANFFMPEG_DECODERBASE_H


extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/frame.h>
#include <libavutil/time.h>
#include <libavcodec/jni.h>
};

#include <thread>
#include "Decoder.h"

#define MAX_PATH   2048
#define DELAY_THRESHOLD 100 //100ms

enum DecoderState {
    STATE_UNKNOWN,
    STATE_DECODING,
    STATE_PAUSE,
    STATE_STOP
};

enum DecoderMsg {
    MSG_DECODER_INIT_ERROR,
    MSG_DECODER_READY,
    MSG_DECODER_DONE,
    MSG_REQUEST_RENDER,
    MSG_DECODING_TIME
};


class DecoderBase : public Decoder {
public:
    DecoderBase()  {}
    virtual~ DecoderBase() {}

public:

    virtual void Start();
    virtual void Pause();
    virtual void Stop();
    virtual float GetDuration()
    {
        //ms to s
        return m_Duration * 1.0f / 1000;
    }
    virtual void SeekToPosition(float position);
    virtual float GetCurrentPosition();
    virtual void ClearCache() { }
    virtual void SetMessageCallback(void* context, MessageCallback callback)
    {
        m_MsgContext = context;
        m_MsgCallback = callback;
    }
    //设置音视频同步的回调
    virtual void SetAVSyncCallback(void* context, AVSyncCallback callback)
    {
        m_AVDecoderContext = context;
        m_AVSyncCallback = callback;
    }

protected:
    void * m_MsgContext = nullptr;
    MessageCallback m_MsgCallback = nullptr;
    virtual int Init(const char *url, AVMediaType mediaType);
    virtual void UnInit();
    virtual void OnDecoderReady() = 0;
    virtual void OnDecoderDone() = 0;
    //解码数据的回调
    virtual void OnFrameAvailable(AVFrame *frame) = 0;

    AVCodecContext *GetCodecContext() {
        return m_AVCodecContext;
    }


private:
    int InitFFDecoder();
    void UnInitDecoder();
    //启动解码线程
    void StartDecodingThread();
    //音视频解码循环
    void DecodingLoop();

    //更新显示时间戳
    void UpdateTimeStamp();
    //音视频同步
    long AVSync();
    //解码一个packet编码数据
    int DecodeOnePacket();
    //线程函数
    static void DoAVDecoding(DecoderBase *decoder);

    //封装格式上下文
    AVFormatContext *m_AVFormatContext = nullptr;
    //解码器上下文
    AVCodecContext  *m_AVCodecContext = nullptr;
    //解码器
    AVCodec         *m_AVCodec = nullptr;
    //编码的数据包
    AVPacket        *m_Packet = nullptr;
    //解码的帧
    AVFrame         *m_Frame = nullptr;
    //数据流的类型
    AVMediaType            m_MediaType = AVMEDIA_TYPE_UNKNOWN;
    //文件地址
    char                   m_Url[MAX_PATH] = {0};
    //当前播放时间
    long             m_CurTimeStamp = 0;
    //播放的起始时间
    long             m_StartTimeStamp = -1;
    //总时长 ms
    long             m_Duration = 0;
    //数据流索引
    int              m_StreamIndex = -1;

    //锁和条件变量
    std::mutex                  m_Mutex;
    std::condition_variable     m_Cond;
    std::thread                *m_Thread = nullptr;

    //seek position
    volatile float      m_SeekPosition = 0;
    volatile bool       m_SeekSuccess = false;

    //解码器状态
    volatile int  m_DecoderState = STATE_UNKNOWN;
    void* m_AVDecoderContext = nullptr;
    AVSyncCallback m_AVSyncCallback = nullptr;//用作音视频同步
};


#endif //LEANFFMPEG_DECODERBASE_H

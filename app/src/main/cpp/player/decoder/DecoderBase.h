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

    virtual void Start() {}
    virtual void Pause() { }
    virtual void Stop() { }
    virtual float GetDuration() { float value = 0;  return value;}
    virtual void SeekToPosition(float position) { }
    virtual float GetCurrentPosition() { float value = 0;  return value; }
    virtual void SetMessageCallback(void* context, MessageCallback callback) {}

protected:
    void * m_MsgContext = nullptr;
    MessageCallback m_MsgCallback = nullptr;
    virtual int Init(const char *url, AVMediaType mediaType);
    virtual void UnInit();
    virtual void OnDecoderReady() = 0;
    virtual void OnDecoderDone() = 0;
};


#endif //LEANFFMPEG_DECODERBASE_H

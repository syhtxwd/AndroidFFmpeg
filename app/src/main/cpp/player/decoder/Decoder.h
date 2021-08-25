//
// Created by syh on 2021-08-25.
//

#ifndef LEANFFMPEG_DECODER_H
#define LEANFFMPEG_DECODER_H

typedef void (*MessageCallback)(void*, int, float);
typedef long (*AVSyncCallback)(void*);

class Decoder {
public:
    virtual void Start() = 0;
    virtual void Pause() = 0;
    virtual void Stop() = 0;
    virtual float GetDuration() = 0;
    virtual void SeekToPosition(float position) = 0;
    virtual float GetCurrentPosition() = 0;
    virtual void SetMessageCallback(void* context, MessageCallback callback) = 0;
};

#endif //LEANFFMPEG_DECODER_H

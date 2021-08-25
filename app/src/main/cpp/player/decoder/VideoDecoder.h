//
// Created by syh on 2021-08-24.
//

#ifndef LEANFFMPEG_VIDEODECODER_H
#define LEANFFMPEG_VIDEODECODER_H

extern "C" {
#include <libavutil/imgutils.h>
#include <libswscale/swscale.h>
#include <libavcodec/jni.h>
};

#include "DecoderBase.h"

class VideoDecoder : public DecoderBase {

public:
    VideoDecoder(char *url){
        Init(url, AVMEDIA_TYPE_VIDEO);
    }

public:
    virtual void OnDecoderReady() {}
    virtual void OnDecoderDone() {}
};


#endif //LEANFFMPEG_VIDEODECODER_H

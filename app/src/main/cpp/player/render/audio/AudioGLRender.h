//
// Created by syh on 2021-08-29.
//

#ifndef LEANFFMPEG_AUDIOGLRENDER_H
#define LEANFFMPEG_AUDIOGLRENDER_H

#include "thread"
#include "AudioRender.h"
#include <GLES3/gl3.h>
#include <detail/type_mat.hpp>
#include <detail/type_mat4x4.hpp>
#include <render/BaseGLRender.h>

using namespace glm;

#define MAX_AUDIO_LEVEL 5000
#define RESAMPLE_LEVEL  40

class AudioGLRender {
public:
    static AudioGLRender* GetInstance();
    static void ReleaseInstance(){}

    virtual void OnSurfaceCreated(){}
    virtual void OnSurfaceChanged(int w, int h){}
    virtual void OnDrawFrame(){}
    virtual void UpdateMVPMatrix(int angleX, int angleY, float scaleX, float scaleY){}
    virtual void SetTouchLoc(float touchX, float touchY) {}

    void UpdateAudioFrame(AudioFrame *audioFrame){}

private:
    void Init(){}
    void UnInit();
    AudioGLRender(){
        Init();
    }
    ~AudioGLRender(){
        UnInit();
    }

    void UpdateMesh(){}

    static AudioGLRender *m_pInstance;
    static std::mutex m_Mutex;
};


#endif //LEANFFMPEG_AUDIOGLRENDER_H

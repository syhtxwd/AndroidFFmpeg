//
// Created by syh on 2021-08-27.
//

#ifndef LEANFFMPEG_VIDEORENDER_H
#define LEANFFMPEG_VIDEORENDER_H

#define VIDEO_RENDER_OPENGL             0
#define VIDEO_RENDER_ANWINDOW           1
#define VIDEO_RENDER_3D_VR              2

#include "ImageDef.h"

class VideoRender {
public:
    VideoRender(int type){
        m_RenderType = type;
    }
    virtual ~VideoRender(){}
    virtual void Init(int videoWidth, int videoHeight, int *dstSize) = 0;
    virtual void RenderVideoFrame(NativeImage *pImage)= 0;
    virtual void UnInit()= 0;

    int GetRenderType() {
        return m_RenderType;
    }
private:
    int m_RenderType = VIDEO_RENDER_ANWINDOW;

};


#endif //LEANFFMPEG_VIDEORENDER_H

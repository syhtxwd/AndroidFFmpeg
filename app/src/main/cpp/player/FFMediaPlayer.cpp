//
// Created by syh on 2021-08-24.
//

#include "FFMediaPlayer.h"
#include "LogUtil.h"

void FFMediaPlayer::Init(JNIEnv *jniEnv, jobject obj, char *url, int renderType, jobject surface)
{
    LOGCATE("FFMediaPlayer::Init, uri:%s", url);
    jniEnv->GetJavaVM(&m_JavaVM);
    m_JavaObj = jniEnv->NewGlobalRef(obj);

    m_VideoDecoder = new VideoDecoder(url);

}
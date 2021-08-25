#include <jni.h>
#include <string>
#include <FFMediaPlayer.h>

#include <cstdio>
#include <cstring>

#include "util/LogUtil.h"


extern "C" {
#include <libavcodec/version.h>
#include <libavcodec/avcodec.h>
#include <libavformat/version.h>
#include <libavutil/version.h>
#include <libavfilter/version.h>
#include <libswresample/version.h>
#include <libswscale/version.h>
};

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT jstring JNICALL Java_com_example_leanffmpeg_media_FFMediaPlayer_native_1GetFFmpegVersion
        (JNIEnv *env, jclass cls) {
    char strBuffer[1024 * 4] = {0};
    strcat(strBuffer, "libavcodec : ");
    strcat(strBuffer, AV_STRINGIFY(LIBAVCODEC_VERSION));
    strcat(strBuffer, "\nlibavformat : ");
    strcat(strBuffer, AV_STRINGIFY(LIBAVFORMAT_VERSION));
    strcat(strBuffer, "\nlibavutil : ");
    strcat(strBuffer, AV_STRINGIFY(LIBAVUTIL_VERSION));
    strcat(strBuffer, "\nlibavfilter : ");
    strcat(strBuffer, AV_STRINGIFY(LIBAVFILTER_VERSION));
    strcat(strBuffer, "\nlibswresample : ");
    strcat(strBuffer, AV_STRINGIFY(LIBSWRESAMPLE_VERSION));
    strcat(strBuffer, "\nlibswscale : ");
    strcat(strBuffer, AV_STRINGIFY(LIBSWSCALE_VERSION));
    strcat(strBuffer, "\navcodec_configure : \n");
    strcat(strBuffer, avcodec_configuration());
    strcat(strBuffer, "\navcodec_license : ");
    strcat(strBuffer, avcodec_license());
    LOGCATE("GetFFmpegVersion\n%s", strBuffer);

    //ASanTestCase::MainTest();

    return env->NewStringUTF(strBuffer);
}

JNIEXPORT jlong JNICALL Java_com_example_leanffmpeg_media_FFMediaPlayer_native_1Init
        (JNIEnv *env, jobject obj, jstring jurl, jint renderType, jobject surface)
{
    const char* url = env->GetStringUTFChars(jurl, nullptr);
    FFMediaPlayer *player = new FFMediaPlayer();
    player->Init(env, obj, const_cast<char *>(url), renderType, surface);
    env->ReleaseStringUTFChars(jurl, url);
    return reinterpret_cast<jlong>(player);
}

JNIEXPORT void JNICALL Java_com_example_leanffmpeg_media_FFMediaPlayer_native_1Play
        (JNIEnv *env, jobject obj, jlong player_handle)
{


}

JNIEXPORT void JNICALL
Java_com_example_leanffmpeg_media_FFMediaPlayer_native_1SeekToPosition(JNIEnv *env, jobject thiz,
                                                                         jlong player_handle, jfloat position) {

}

JNIEXPORT void JNICALL Java_com_example_leanffmpeg_media_FFMediaPlayer_native_1Pause
        (JNIEnv *env, jobject obj, jlong player_handle)
{

}


JNIEXPORT void JNICALL Java_com_example_leanffmpeg_media_FFMediaPlayer_native_1Stop
        (JNIEnv *env, jobject obj, jlong player_handle)
{

}


JNIEXPORT void JNICALL Java_com_example_leanffmpeg_media_FFMediaPlayer_native_1UnInit
        (JNIEnv *env, jobject obj, jlong player_handle)
{

}

JNIEXPORT jlong JNICALL
Java_com_example_leanffmpeg_media_FFMediaPlayer_native_1GetMediaParams(JNIEnv *env, jobject thiz,
                                                                         jlong player_handle,
                                                                         jint param_type)
{
    long value = 0;
    return value;
}

JNIEXPORT void JNICALL
Java_com_example_leanffmpeg_media_FFMediaPlayer_native_1OnSurfaceCreated(JNIEnv *env,
                                                                           jclass clazz,
                                                                           jint render_type) {

}

JNIEXPORT void JNICALL
Java_com_example_leanffmpeg_media_FFMediaPlayer_native_1OnSurfaceChanged(JNIEnv *env, jclass clazz,
                                                                           jint render_type,
                                                                           jint width,
                                                                           jint height) {

}

JNIEXPORT void JNICALL
Java_com_example_leanffmpeg_media_FFMediaPlayer_native_1OnDrawFrame(JNIEnv *env, jclass clazz, jint render_type) {

}


#ifdef __cplusplus
}
#endif



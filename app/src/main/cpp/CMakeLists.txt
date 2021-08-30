
cmake_minimum_required(VERSION 3.10.2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

set(jnilibs ${CMAKE_SOURCE_DIR}/../jniLibs)
set(libname learn-ffmpeg)

include_directories(
        include
        glm
        common
        ${CMAKE_SOURCE_DIR}/recorder
        ${CMAKE_SOURCE_DIR}/util
        ${CMAKE_SOURCE_DIR}/player
        ${CMAKE_SOURCE_DIR}/player/decoder
        ${CMAKE_SOURCE_DIR}/player/render
        ${CMAKE_SOURCE_DIR}/player/render/audio
        ${CMAKE_SOURCE_DIR}/player/render/video)

link_directories(
        ${jnilibs}/${ANDROID_ABI})

file(GLOB src-files
        ${CMAKE_SOURCE_DIR}/*.cpp
        ${CMAKE_SOURCE_DIR}/util/*.cpp
        ${CMAKE_SOURCE_DIR}/player/*.cpp
        ${CMAKE_SOURCE_DIR}/player/decoder/*.cpp
        ${CMAKE_SOURCE_DIR}/player/render/video/*.cpp
        ${CMAKE_SOURCE_DIR}/player/render/audio/*.cpp
        ${CMAKE_SOURCE_DIR}/recorder/SingleVideoRecorder.cpp
        )

add_library(${libname}
             SHARED
             ${src-files} )


set(third-party-libs
        avformat
        avcodec
        avfilter
        swresample
        swscale
        avutil
        fdk-aac
        x264
        )

set(native-libs
        android
        EGL
        GLESv3
        OpenSLES
        log
        m
        z
        )

target_link_libraries(${libname}
        ${log-lib}
        ${third-party-libs}
        ${native-libs} )
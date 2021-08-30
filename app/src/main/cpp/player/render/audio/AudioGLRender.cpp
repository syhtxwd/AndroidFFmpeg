//
// Created by syh on 2021-08-29.
//

#include <LogUtil.h>
#include <GLUtils.h>
#include "AudioGLRender.h"
#include <gtc/matrix_transform.hpp>
#include <detail/type_mat.hpp>
#include <detail/type_mat4x4.hpp>
#include <render/video/VideoGLRender.h>


AudioGLRender* AudioGLRender::m_pInstance = nullptr;
std::mutex AudioGLRender::m_Mutex;

AudioGLRender *AudioGLRender::GetInstance() {
    if(m_pInstance == nullptr) {
        std::unique_lock<std::mutex> lock(m_Mutex);
        if(m_pInstance == nullptr) {
            m_pInstance = new AudioGLRender();
        }

    }
    return m_pInstance;
}
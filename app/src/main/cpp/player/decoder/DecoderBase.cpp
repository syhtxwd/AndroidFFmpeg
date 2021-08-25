//
// Created by syh on 2021-08-24.
//

#include "DecoderBase.h"
#include "LogUtil.h"

int DecoderBase::Init(const char *url, AVMediaType mediaType) {
    LOGCATE("DecoderBase::Init url=%s, mediaType=%d", url, mediaType);
    strcpy(m_Url,url);
    m_MediaType = mediaType;
    return 0;
}
void DecoderBase::UnInit() {

}
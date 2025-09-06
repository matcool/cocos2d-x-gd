#include "ObjectDecoder.h"
#include "../xml/DS_Dictionary.h"

using namespace cocos2d;

bool ObjectDecoder::init() {
    return CCNode::init();
}

ObjectDecoder::ObjectDecoder() {
}

ObjectDecoder* ObjectDecoder::sharedDecoder() {
    static ObjectDecoder* sharedDecoder = nullptr;
    if (!sharedDecoder) {
        sharedDecoder = new ObjectDecoder();
        sharedDecoder->init();
    }
    return sharedDecoder;
}

#ifdef _WIN32
static_assert(sizeof(ObjectDecoder) == 0x148);
#endif

CCObject* ObjectDecoder::getDecodedObject(int key, DS_Dictionary* dict) {
    if (m_delegate) {
        return m_delegate->getDecodedObject(key, dict);
    }
    return nullptr;
}

ObjectDecoderDelegate* ObjectDecoder:: getDelegate() const {
    return m_delegate;
}

void ObjectDecoder::setDelegate(ObjectDecoderDelegate* delegate) {
    m_delegate = delegate;
}
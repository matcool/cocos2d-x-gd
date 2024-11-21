#include "ObjectDecoder.h"

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
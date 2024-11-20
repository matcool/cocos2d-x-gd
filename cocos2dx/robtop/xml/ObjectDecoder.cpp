#include "ObjectDecoder.h"

bool ObjectDecoder::init() {
    ROB_UNIMPLEMENTED();
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
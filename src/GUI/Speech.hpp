#pragma once
#include "../../lib/whisper.cpp/include/whisper.h"
#include <string>

class Speech {
private:
    struct whisper_context* ctx;
    bool isInitialized;

public:
    Speech();
    ~Speech();
    bool init();
    std::string transcribe(const std::string& audioFile);
};
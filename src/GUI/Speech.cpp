#include "Speech.hpp"
#include "Logger.hpp"
#include "wav.h"
#include <filesystem>
#include <iostream>

Speech::Speech()
    : ctx(nullptr)
    , isInitialized(false)
{
}

Speech::~Speech()
{
    if (ctx) {
        whisper_free(ctx);
    }
}

bool Speech::init()
{
    if (isInitialized)
        return true;

    Logger::log("Loading whisper model...");

    // Initialize context params properly
    struct whisper_context_params cparams = {
        .use_gpu = true, // enable GPU if available
    };

    // Correct initialization with context params
    ctx = whisper_init_from_file_with_params("../../lib/whisper.cpp/models/ggml-model-whisper-base.en.bin", cparams);

    if (ctx == nullptr) {
        Logger::log("Error: Failed to initialize whisper context");
        return false;
    }

    Logger::log("Whisper model loaded successfully");
    isInitialized = true;
    return true;
}

std::string Speech::transcribe(const std::string& audioFile)
{
    if (!isInitialized) {
        if (!init()) {
            Logger::log("Error: Speech recognition not initialized");
            return "Error: Speech recognition not initialized";
        }
    }

    // Add file existence check
    if (!std::filesystem::exists(audioFile)) {
        Logger::log("Error: File not found - " + audioFile);
        return "Error: File not found";
    }

    Logger::log("Starting transcription of: " + audioFile);

    // Configure whisper parameters correctly
    struct whisper_full_params params = whisper_full_default_params(WHISPER_SAMPLING_GREEDY);
    params.print_progress = false;
    params.print_realtime = false;
    params.print_timestamps = false;
    params.translate = false;
    params.language = "en";
    params.n_threads = 4;

    // Read audio file and process
    std::vector<float> pcmf32;
    if (!::read_wav(audioFile, pcmf32)) {
        Logger::log("Error: Failed to read audio file");
        return "Error: Failed to read audio file";
    }

    // Add sample count verification
    Logger::log("Loaded " + std::to_string(pcmf32.size()) + " samples (" + std::to_string(pcmf32.size() / 16000.0f) + "s)");

    // Process audio through Whisper
    if (whisper_full(ctx, params, pcmf32.data(), pcmf32.size()) != 0) {
        return "Error: Failed to process audio";
    }

    // Get the transcription
    std::string result;
    const int n_segments = whisper_full_n_segments(ctx);
    for (int i = 0; i < n_segments; ++i) {
        result += whisper_full_get_segment_text(ctx, i);
        result += " ";
    }

    return result;
}
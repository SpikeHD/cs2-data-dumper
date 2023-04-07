#pragma once

#include <string>
#include <chrono>

namespace utils {
    void runWithLogging(std::string);
    void WriteLabel(std::string, std::time_t);
    void CaptureWindowNative(std::time_t);
    void UnloadLibrary();
}

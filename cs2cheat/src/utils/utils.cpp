#include "utils.hpp"
#include <Windows.h>
#include <initguid.h>
#include <gdiplus.h>
#include <locale>
#include <codecvt>
#include "../console/console.hpp"

#pragma comment(lib, "gdiplus.lib")

using namespace Gdiplus;

void utils::runWithLogging(std::string program) {
    // Run program and printf ouput
    FILE* pipe = _popen(program.c_str(), "r");
    if (!pipe) {
		LOG("Failed to run program");
		return;
	}

    char buffer[128];
    while (fgets(buffer, 128, pipe) != NULL) {
        LOG(buffer);
	}

    _pclose(pipe);
}

void utils::CaptureWindow(std::string labelData) {
    // Open the "capture.py" script and pass in the label data
    std::string sCaptureCommand = "venv\\Scripts\\activate && python capture.py " + labelData;

    LOG("Running: %s\n\n", sCaptureCommand.c_str());

    // Run the capture script
    utils::runWithLogging(sCaptureCommand);
}

void utils::UnloadLibrary() {
    void CS2_UnloadLibrary();
    CS2_UnloadLibrary();
}

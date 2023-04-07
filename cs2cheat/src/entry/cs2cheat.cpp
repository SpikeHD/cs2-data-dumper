#include <thread>
#include <filesystem>
#include <stdio.h>
#include <stdlib.h>

#include "../sdk/interfaces/interfaces.hpp"
#include "../sdk/memory/memory.hpp"
#include "../hooks/hooks.hpp"
#include "../utils/utils.hpp"

namespace fs = std::filesystem;

void InitializeCheat() {
    CModule navsystem(NAVSYSTEM_DLL, true);
    while (!navsystem.IsLoaded()) {
        navsystem.Load();
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }

    console::Initialize();
    interfaces::Initialize();
    memory::Initialize();
    hooks::Initialize();

    // Data dump paths
    std::string sMainDumpPath = "./dump";

    // Create paths if they don't exist
    fs::path pImagePath{sMainDumpPath + "/images"};
    fs::path pLabelPath{sMainDumpPath + "/labels"};

    std::stringstream s;
    s << "Creating dirs..." << std::endl;
    s << "Image path: " << pImagePath << std::endl;
    s << "Label path: " << pLabelPath << std::endl;

    if (!fs::exists(pImagePath)) {
        fs::create_directories(pImagePath);
    }

    if (!fs::exists(pLabelPath)) {
        fs::create_directories(pLabelPath);
    }

    LOG("%s", s.str().c_str();
}

void UninitializeCheat() {
    hooks::Shutdown();
    memory::Shutdown();
    interfaces::Shutdown();
    console::Shutdown();
}

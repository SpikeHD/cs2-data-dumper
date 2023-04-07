#include <thread>

#include "../sdk/interfaces/interfaces.hpp"
#include "../sdk/memory/memory.hpp"
#include "../hooks/hooks.hpp"
#include "filesystem"

namespace fs = std::filesystem;

void InitializeCheat() {
    CModule navsystem(NAVSYSTEM_DLL, true);
    while (!navsystem.IsLoaded()) {
        navsystem.Load();
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }

    // Data dump paths
    std::string sMainDumpPath = "./dump";

    // Create paths if they don't exist
    fs::path pImagePath{sMainDumpPath + "/images"};
    fs::path pLabelPath{sMainDumpPath + "/labels"};

    if (!fs::exists(pImagePath)) {
        fs::create_directory(pImagePath);
    }

    if (!fs::exists(pLabelPath)) {
        fs::create_directory(pLabelPath);
    }

    console::Initialize();
    interfaces::Initialize();
    memory::Initialize();
    hooks::Initialize();
}

void UninitializeCheat() {
    hooks::Shutdown();
    memory::Shutdown();
    interfaces::Shutdown();
    console::Shutdown();
}

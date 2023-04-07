#include "utils.hpp"
#include <Windows.h>
#include <initguid.h>
#include <gdiplus.h>
#include <locale>
#include <codecvt>
#include <fstream>
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

void utils::WriteLabel(std::string sContent, std::time_t time) {
    std::string path = "./dump/labels/" + std::to_string(static_cast<int>(time)) + ".txt";
    std::ofstream file(path);

    if (file.is_open()) {
        file << sContent.c_str();
        file.close();
    }
}

void utils::CaptureWindowNative(std::time_t time) {
    std::string path = "./dump/images/" + std::to_string(static_cast<int>(time)) + ".bmp";

    // Get the screen dimensions
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    // Create a device context for the entire screen
    HDC hScreenDC = GetDC(NULL);

    // Create a compatible device context for the screen DC
    HDC hMemDC = CreateCompatibleDC(hScreenDC);

    // Create a bitmap to hold the screenshot
    HBITMAP hBitmap =
        CreateCompatibleBitmap(hScreenDC, screenWidth, screenHeight);

    // Select the bitmap into the compatible device context
    HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBitmap);

    // Copy the screen contents to the compatible device context
    BitBlt(hMemDC, 0, 0, screenWidth, screenHeight, hScreenDC, 0, 0, SRCCOPY);

    // Save the bitmap to a file
    BITMAPFILEHEADER bmpFileHeader;
    BITMAPINFOHEADER bmpInfoHeader;
    bmpFileHeader.bfType = 0x4D42;  // 'BM' signature
    bmpFileHeader.bfSize =
        sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) +
        screenWidth * screenHeight * 4;  // 4 bytes per pixel (RGBA)
    bmpFileHeader.bfOffBits =
        sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    bmpInfoHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmpInfoHeader.biWidth = screenWidth;
    bmpInfoHeader.biHeight = screenHeight;
    bmpInfoHeader.biPlanes = 1;
    bmpInfoHeader.biBitCount = 32;  // 32 bits per pixel (RGBA)
    bmpInfoHeader.biCompression = BI_RGB;
    std::ofstream file(path.c_str(), std::ios::binary);
    file.write(reinterpret_cast<const char*>(&bmpFileHeader),
               sizeof(BITMAPFILEHEADER));
    file.write(reinterpret_cast<const char*>(&bmpInfoHeader),
               sizeof(BITMAPINFOHEADER));
    int imageSize = screenWidth * screenHeight * 4;
    char* imageData = new char[imageSize];
    GetBitmapBits(hBitmap, imageSize, imageData);

    for (int y = 0; y < screenHeight / 2; y++) {
        int swapY = screenHeight - y - 1;
        for (int x = 0; x < screenWidth * 4; x++) {
            std::swap(imageData[y * screenWidth * 4 + x],
                      imageData[swapY * screenWidth * 4 + x]);
        }
    }

    file.write(imageData, imageSize);
    delete[] imageData;
    file.close();

    // Clean up resources
    SelectObject(hMemDC, hOldBitmap);
    DeleteObject(hBitmap);
    DeleteDC(hMemDC);
    ReleaseDC(NULL, hScreenDC);
}

void utils::UnloadLibrary() {
    void CS2_UnloadLibrary();
    CS2_UnloadLibrary();
}

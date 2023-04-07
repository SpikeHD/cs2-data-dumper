#include "utils.hpp"
#include <Windows.h>
#include <initguid.h>
#include <gdiplus.h>
#include <locale>
#include <codecvt>
#include "../console/console.hpp"

#pragma comment(lib, "gdiplus.lib")

using namespace Gdiplus;

std::wstring StringToWideString(const std::string& str) {
    int len = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);
    wchar_t* wstr = new wchar_t[len];
    MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, wstr, len);
    std::wstring result(wstr);
    delete[] wstr;
    return result;
}

void utils::CaptureWindow(const std::string& filename) {
    // Get CS2 window handle
    HWND hwnd = FindWindow(NULL, (LPCSTR)"Counter-Strike 2");

    // Verify handle exists
    if (!hwnd) {
		LOG("Failed to find CS2 window\n");
		return;
	}

    // Get the window dimensions
    RECT rect;
    GetWindowRect(hwnd, &rect);

    int width = rect.right - rect.left;
    int height = rect.bottom - rect.top;

    // Create a bitmap with the window dimensions
    HDC hdcScreen = GetDC(NULL);
    HDC hdcWindow = GetDC(hwnd);
    HBITMAP hBitmap = CreateCompatibleBitmap(hdcScreen, width, height);

    // Copy the window contents to the bitmap
    PrintWindow(hwnd, hdcWindow, PW_CLIENTONLY);

    LOG("Printed window\n");

    // Create a GDI+ Bitmap object from the HBITMAP
    Bitmap bitmap(hBitmap, (HPALETTE)NULL);

    LOG("Created BMP obj\n");

    // Save the bitmap as a PNG file
    CLSID pngClsid;
    LOG("CLSID getting...\n");
    CLSIDFromString(L"{557CF406-1A04-11D3-9A73-0000F81EF32E}", &pngClsid);

    LOG("CLSID got\n");

    std::string pngFilename = filename + ".png";

    LOG("before save (%s)...\n", pngFilename);

    bitmap.Save(StringToWideString(filename).c_str(), &pngClsid, NULL);

    LOG("Saved BMP to: %s\n", pngFilename);

    // Cleanup
    DeleteObject(hBitmap);
    ReleaseDC(hwnd, hdcWindow);
    ReleaseDC(NULL, hdcScreen);
}

void utils::UnloadLibrary() {
    void CS2_UnloadLibrary();
    CS2_UnloadLibrary();
}

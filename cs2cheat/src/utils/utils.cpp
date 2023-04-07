#include "utils.hpp"
#include <Windows.h>
#include <initguid.h>
#include <gdiplus.h>
#pragma comment(lib, "gdiplus.lib")

using namespace Gdiplus;

void GetEncoderClsid(const WCHAR* format, CLSID* pClsid) {
    UINT num = 0;   // number of image encoders
    UINT size = 0;  // size of the image encoder array in bytes

    ImageCodecInfo* pImageCodecInfo = NULL;

    GetImageEncodersSize(&num, &size);
    if (size == 0) return;

    pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
    if (pImageCodecInfo == NULL) return;

    GetImageEncoders(num, size, pImageCodecInfo);

    for (UINT i = 0; i < num; ++i) {
        if (wcscmp(pImageCodecInfo[i].MimeType, format) == 0) {
            *pClsid = pImageCodecInfo[i].Clsid;
            break;
        }
    }

    free(pImageCodecInfo);
}

// Function to capture the contents of the window
void utils::CaptureWindow(const wchar_t* filename) {
    // Get the window handle
    HWND hwnd = FindWindow(NULL, (char*)"Counter-Strike 2");

    // Get the window dimensions
    RECT rect;
    GetWindowRect(hwnd, &rect);
    int width = rect.right - rect.left;
    int height = rect.bottom - rect.top;

    // Create a bitmap with the window dimensions
    HDC hdcScreen = GetDC(NULL);
    HDC hdcWindow = GetDC(hwnd);
    HBITMAP hBitmap = CreateCompatibleBitmap(hdcScreen, width, height);
    HGDIOBJ oldObj = SelectObject(hdcWindow, hBitmap);

    // Copy the window contents to the bitmap
    PrintWindow(hwnd, hdcWindow, PW_CLIENTONLY);

    // Save the bitmap to a file using GDI+
    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
    CLSID clsid;
    GetEncoderClsid(L"image/jpeg", &clsid);
    Bitmap bitmap(hBitmap, NULL);
    bitmap.Save(filename, &clsid, NULL);
    GdiplusShutdown(gdiplusToken);

    // Cleanup
    SelectObject(hdcWindow, oldObj);
    DeleteObject(hBitmap);
    ReleaseDC(hwnd, hdcWindow);
    ReleaseDC(NULL, hdcScreen);
}

void utils::UnloadLibrary() {
    void CS2_UnloadLibrary();
    CS2_UnloadLibrary();
}

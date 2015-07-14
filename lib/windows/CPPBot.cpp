#include "CPPBot"
#include <iostream>
#include <windows.h>
#include <Winuser.h>
#include <vector>
#include <cstdlib>
#include <cstring>


// data for the windows implementation
static std::vector<unsigned char> pixels;
static std::vector<unsigned char> convertedPixels;

CPPBot::CPPBot()
{
    // make our application DPIres aware
    // if we didn't do that windows report wrong screen dimensions.
    // Why can't I get theses informations easily on windows ?
    HMODULE hUser32 = LoadLibrary("user32.dll");
    typedef BOOL (*SetProcessDPIAwareFunc)();
    SetProcessDPIAwareFunc setDPIAware = (SetProcessDPIAwareFunc)GetProcAddress(hUser32, "SetProcessDPIAware");
    if (setDPIAware)
        setDPIAware();
    FreeLibrary(hUser32);
}

CPPBot::~CPPBot()
{
    pixels.clear();
}

// ┌──────────────────────────────────────────────────────────────────┐
// │  Keyboard                                                        │
// └──────────────────────────────────────────────────────────────────┘

void CPPBot::keyboardPress(const int key)
{
    std::cout << "Sorry : CPPBot::keyboardPress is not implemented" << std::endl;
}

void CPPBot::keyboardRelease(const int key)
{
    std::cout << "Sorry : CPPBot::keyboardRelease is not implemented" << std::endl;
}

void CPPBot::keyboard(const int key)
{
    keyboardPress(key);
    keyboardRelease(key);
}

// ┌──────────────────────────────────────────────────────────────────┐
// │  Mouse                                                           │
// └──────────────────────────────────────────────────────────────────┘
void CPPBot::mousePosition(const int x, const int y)
{
    std::cout << "Sorry : CPPBot: mousePosition is not implemented" << std::endl;
}
void CPPBot::mouseGetPosition(int& x, int& y)
{
    std::cout << "Sorry : CPPBot: mouseGet is not implemented" << std::endl;
}
void CPPBot::mousePress(const int button)
{
    std::cout << "Sorry : CPPBot: mousePress is not implemented" << std::endl;
}
void CPPBot::mouseRelease(const int button)
{
    std::cout << "Sorry : CPPBot: mouseRelease is not implemented" << std::endl;
}
void CPPBot::mouse(const int button)
{
    mousePress(button);
    mouseRelease(button);
}


// ┌──────────────────────────────────────────────────────────────────┐
// │  Screen                                                          │
// └──────────────────────────────────────────────────────────────────┘
void convertScreenPixel()
{
    // making an horizontal flip.
    // convert from ABGR -> BGR
    convertedPixels.resize(pixels.size() * 3 / 4);
    int j = 0;
    for(int i = pixels.size(); i>0; --i)
    {
        convertedPixels[++j] = pixels[--i]; //R
        convertedPixels[++j] = pixels[--i]; //G
        convertedPixels[++j] = pixels[--i]; //B
    }
}
const unsigned char* CPPBot::screen()
{
    int width = GetSystemMetrics(SM_CXSCREEN);
    int height = GetSystemMetrics(SM_CYSCREEN);

    // create DC
    HDC hDc = CreateCompatibleDC(0);
    // create hBitmap
    HBITMAP hBmp = CreateCompatibleBitmap(GetDC(0), width, height);

    // transfert from DC to hBitmap
    SelectObject(hDc, hBmp);
    BitBlt(hDc, 0, 0, width, height, GetDC(0), 0, 0, SRCCOPY);

    // get raw byte from hBitmap
    BITMAP Bmp = {0};
    BITMAPINFO Info = {0};
    std::memset(&Info, 0, sizeof(BITMAPINFO)); //not necessary really..
    GetObject(hBmp, sizeof(Bmp), &Bmp);

    Info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    Info.bmiHeader.biWidth = width = Bmp.bmWidth;
    Info.bmiHeader.biHeight = height = Bmp.bmHeight;
    Info.bmiHeader.biPlanes = 1;
    Info.bmiHeader.biBitCount = Bmp.bmBitsPixel;
    Info.bmiHeader.biCompression = BI_RGB;
    Info.bmiHeader.biSizeImage = ((width * Bmp.bmBitsPixel + 31) / 32) * 4 * height;


    pixels.resize(Info.bmiHeader.biSizeImage);
    GetDIBits(hDc, hBmp, 0, height, pixels.data(), &Info, DIB_RGB_COLORS);

    DeleteObject(&Bmp);
    DeleteObject(hBmp);
    DeleteDC(hDc);

    convertScreenPixel();
    return convertedPixels.data();
}
const int CPPBot::screenWidth()
{
    return GetSystemMetrics(SM_CXSCREEN);
}
const int CPPBot::screenHeight()
{
    return GetSystemMetrics(SM_CYSCREEN);
}

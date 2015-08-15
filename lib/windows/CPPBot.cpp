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
static int screenWidthCached = 0;
static int screenHeightCached = 0;
bool isInitialized = false;
static const DWORD mouseButtonDown[3] = {MOUSEEVENTF_LEFTDOWN,MOUSEEVENTF_MIDDLEDOWN,MOUSEEVENTF_RIGHTDOWN};
static const DWORD mouseButtonUp[3]   = {MOUSEEVENTF_LEFTUP,  MOUSEEVENTF_MIDDLEUP,  MOUSEEVENTF_RIGHTUP};

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

    if (!isInitialized)
    {
        isInitialized = true;
        screenWidthCached = screenWidth();
        screenHeightCached = screenHeight();
    }
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
    INPUT input;
    input.type = INPUT_KEYBOARD;
    input.ki.wScan = 0;
    input.ki.time = 0;
    input.ki.dwExtraInfo = 0;
    input.ki.wVk = key+0x41-'a';
    input.ki.dwFlags = 0;
    SendInput(1, &input, sizeof(INPUT));
    std::cout << key << std::endl;
}

void CPPBot::keyboardRelease(const int key)
{
    INPUT input;
    input.type = INPUT_KEYBOARD;
    input.ki.wScan = 0;
    input.ki.time = 0;
    input.ki.dwExtraInfo = 0;
    input.ki.wVk = key+0x41-'a';
    input.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &input, sizeof(INPUT));
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
    INPUT input;
    input.type = INPUT_MOUSE;
    input.mi.mouseData=0;
    input.mi.dx =  x*(65536.f/(screenWidthCached-1));
    input.mi.dy =  y*(65536.f/(screenHeightCached-1));
    input.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE;
    SendInput(1,&input,sizeof(input));
}
void CPPBot::mouseGetPosition(int& x, int& y)
{
    std::cout << "Sorry : CPPBot: mousePress is not implemented" << std::endl;
}
void CPPBot::mousePress(const int button)
{
    INPUT input;
    input.type = INPUT_MOUSE;
    input.mi.time = 0;
    input.mi.dwFlags = mouseButtonDown[button];
    SendInput(1,&input,sizeof(input));
}
void CPPBot::mouseRelease(const int button)
{
    INPUT input;
    input.type = INPUT_MOUSE;
    input.mi.time = 0;
    input.mi.dwFlags = mouseButtonUp[button];
    SendInput(1,&input,sizeof(input));
}
void CPPBot::mouse(const int button)
{
    mousePress(button);
    mouseRelease(button);
}


// ┌──────────────────────────────────────────────────────────────────┐
// │  Screen                                                          │
// └──────────────────────────────────────────────────────────────────┘
void convertScreenPixel(int width, int height)
{
    // making an horizontal flip.
    // convert from ABGR -> BGR
    convertedPixels.resize(pixels.size() * 3 / 4);

    int i = 0;

    for(int y = height-1; y>=0; --y) // flip horizontally
    {
        unsigned char * row = pixels.data() + width * y * 4;
        for(int x = 0; x<width; ++x)
        {
            convertedPixels[i+2] = *(row++); // B
            convertedPixels[i+1] = *(row++); // G
            convertedPixels[i+0] = *(row++); // R
            row+=1; // A
            i+=3;
        }
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

    convertScreenPixel(width,height);
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

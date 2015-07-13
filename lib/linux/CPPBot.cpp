#include "CPPBot"
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <cstring> // memset
#include <iostream>


// data for the linux implementation
static int CPPBotElements = 0;
static Display* display = NULL;
static unsigned char* pixels = NULL;
static int width = 0;
static int height = 0;


CPPBot::CPPBot()
{
    if (!CPPBotElements)
        display = XOpenDisplay(0); 
    CPPBotElements++;
}

CPPBot::~CPPBot()
{
    CPPBotElements--;
    if (!CPPBotElements)
    {
        XCloseDisplay(display);
        if (pixels) delete pixels;
        pixels = NULL;
    }
}

// ┌──────────────────────────────────────────────────────────────────┐
// │  Keyboard                                                        |
// └──────────────────────────────────────────────────────────────────┘

void keyboardEvent(bool pressed,int key)
{
    // Find the window which has the current keyboard focus.
    Window win;
    int    revert;
    XGetInputFocus(display, &win, &revert);
    Window winRoot = XDefaultRootWindow(display);


    XKeyEvent event;

    event.display     = display;
    event.window      = win;
    event.root        = winRoot;
    event.subwindow   = None;
    event.time        = CurrentTime;
    event.x           = 1;
    event.y           = 1;
    event.x_root      = 1;
    event.y_root      = 1;
    event.same_screen = True;
    event.keycode     = XKeysymToKeycode(display, key);
    event.state       = 0;//modifiers;
    event.type = pressed? KeyPress : KeyRelease;
    XSendEvent(event.display, event.window, True, KeyPressMask, (XEvent *)&event);

}
void CPPBot::keyboardPress(const int key)
{
    keyboardEvent(true,key);
}

void CPPBot::keyboardRelease(const int key)
{
    keyboardEvent(false,key);
}

void CPPBot::keyboard(const int key)
{
    keyboardPress(key);
    keyboardRelease(key);
}

// ┌──────────────────────────────────────────────────────────────────┐
// │  Mouse                                                           |
// └──────────────────────────────────────────────────────────────────┘

void CPPBot::mousePosition(const int x, const int y)
{
    int mouse_x, mouse_y;
    mouseGetPosition(mouse_x,mouse_y);

    XWarpPointer (display, None, None, 0,0,0,0, x-mouse_x, y-mouse_y);
    XFlush (display);
}
void CPPBot::mouseGetPosition(int& x, int& y)
{
    XEvent event;
    XQueryPointer (display, DefaultRootWindow (display),
            &event.xbutton.root, &event.xbutton.window,
            &event.xbutton.x_root, &event.xbutton.y_root,
            &event.xbutton.x, &event.xbutton.y,
            &event.xbutton.state);
    x = event.xbutton.x;
    y = event.xbutton.y;
}

void mouseEvent(bool pressed, const int button)
{
    // Create and setting up the event
    XEvent event;
    memset(&event, 0, sizeof (event));
    event.xbutton.button = 
         (button == CPPBot::LEFT  ) ? Button1
        :(button == CPPBot::MIDDLE) ? Button2
        :(button == CPPBot::RIGHT ) ? Button3
        : 0;
    event.xbutton.same_screen = True;
    event.xbutton.subwindow = DefaultRootWindow (display);
    while (event.xbutton.subwindow)
    {
        event.xbutton.window = event.xbutton.subwindow;
        XQueryPointer (display, event.xbutton.window,
                &event.xbutton.root, &event.xbutton.subwindow,
                &event.xbutton.x_root, &event.xbutton.y_root,
                &event.xbutton.x, &event.xbutton.y,
                &event.xbutton.state);
    }
    event.type = pressed ? ButtonPress : ButtonRelease;

    XSendEvent (display, PointerWindow, True, ButtonPressMask, &event);
    XFlush (display);
}
void CPPBot::mousePress(const int button)
{
    mouseEvent(true,button);
}
void CPPBot::mouseRelease(const int button)
{
    mouseEvent(false,button);
}
void CPPBot::mouse(const int button)
{
    mousePress(button);
    mouseRelease(button);
}

// ┌──────────────────────────────────────────────────────────────────┐
// │  Screen                                                          |
// └──────────────────────────────────────────────────────────────────┘
const unsigned char* CPPBot::screen()
{
    XWindowAttributes gwa;
    Window root = DefaultRootWindow(display);
    XGetWindowAttributes(display, root , &gwa);

    // allo
    if (gwa.width != width || gwa.height != height || !pixels)
    {
        if (pixels) delete pixels;
        width = gwa.width;
        height = gwa.height;
        pixels = new unsigned char[width * height * 3];
    }

    XImage *image = XGetImage(display,root, 0,0 , width,height,AllPlanes, ZPixmap);

    unsigned long red_mask   = image->red_mask;
    unsigned long green_mask = image->green_mask;
    unsigned long blue_mask  = image->blue_mask;

    unsigned char* i = pixels;
    for (int y = 0; y < height ; y++)
    for (int x = 0; x < width; x++)
    {
        
        unsigned long pixel = XGetPixel(image,x,y);

        unsigned char blue  = pixel & blue_mask;
        unsigned char green = (pixel & green_mask) >> 8;
        unsigned char red   = (pixel & red_mask) >> 16;

        *(i++) = red;
        *(i++) = green;
        *(i++) = blue;
    }

    return pixels;

}
const int CPPBot::screenWidth()
{
    XWindowAttributes gwa;

    XGetWindowAttributes(display, DefaultRootWindow(display), &gwa);
    int width = gwa.width;
    return gwa.width;;
}
const int CPPBot::screenHeight()
{
    XWindowAttributes gwa;

    XGetWindowAttributes(display, DefaultRootWindow(display), &gwa);
    int height = gwa.height;
    return gwa.height;;
}

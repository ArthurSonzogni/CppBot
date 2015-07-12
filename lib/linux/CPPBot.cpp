#include "CPPBot"
#include <iostream>
#include <X11/Xlib.h>
#include <X11/keysym.h>

Display* display;

CPPBot::CPPBot()
{
    display = XOpenDisplay(0); 
}

CPPBot::~CPPBot()
{
    XCloseDisplay(display);
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

    if (pressed)
        event.type = KeyPress;
    else
        event.type = KeyRelease;
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
    std::cout << "Sorry : CPPBot: mousePosition is not implemented" << std::endl;
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
// │  Screen                                                          |
// └──────────────────────────────────────────────────────────────────┘
const char* CPPBot::screen()
{
    std::cout << "Sorry : CPPBot: screen is not implemented" << std::endl;
}
const int CPPBot::screenWidth()
{
    std::cout << "Sorry : CPPBot: screenWidth is not implemented" << std::endl;
}
const int CPPBot::screenHeight()
{
    std::cout << "Sorry : CPPBot: screenHeight is not implemented" << std::endl;
}

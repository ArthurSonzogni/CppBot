#include "CPPBot"
#include <iostream>

CPPBot::CPPBot()
{
}

CPPBot::~CPPBot()
{
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
const unsigned char* CPPBot::screen()
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

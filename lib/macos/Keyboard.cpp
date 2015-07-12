#include "CPPBot"
#include <iostream>

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

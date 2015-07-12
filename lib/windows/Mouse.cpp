#include "CPPBot"
#include <iostream>

// mouse
void CPPBot::mousePosition(const int x, const int y)
{
    std::cout << "Sorry : CPPBot: mousePosition is not implemented" << std::endl;
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

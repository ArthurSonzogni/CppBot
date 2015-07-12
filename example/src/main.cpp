#include <iostream>
#include <CPPBot>

int main(int argc, const char *argv[])
{
    CPPBot bot;

    std::cout << "what feature do you want to test ?" << std::endl;
    std::cout << "1) mouse" << std::endl;
    std::cout << "2) keyboard" << std::endl;
    std::cout << "3) screen" << std::endl;
    int c;
    std::cin >> c;
    if (c == 1) // mouse
    {
    }
    else if (c == 2) // keyboard
    {
    }
    else if (c == 3) // screen
    {
        const char* s = bot.screen();
        std::cout << "screen width = " << bot.screenWidth() << std::endl;
        std::cout << "screen height = " << bot.screenHeight() << std::endl;
    }
    return 0;
}

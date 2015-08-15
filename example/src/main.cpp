#include <iostream>
#include <CPPBot>
#include <unistd.h> // for usleep

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
        // selection
        bot.mousePosition(400,400);
        bot.mousePress(CPPBot::LEFT);
        for(int i = 0; i<300; i+=3)
        {
            usleep(10000);
            bot.mousePosition(400+2*i,400+i);
        }
        bot.mouseRelease(CPPBot::LEFT);
        bot.mouse(CPPBot::LEFT);
        for(int i = 0; i<300; i+=3)
        {
            usleep(10000);
            bot.mousePosition(400+600-i,400+300+i);
        }
    }
    else if (c == 2) // keyboard
    {
        const char* text = "hello world";
        const char* letter = text;
        while(*letter)
        {
            bot.keyboard(*letter);
            letter++;
        }
    }
    else if (c == 3) // screen
    {
        // take a screen shot
        const unsigned char* screen = bot.screen();
        const unsigned int width = bot.screenWidth();
        const unsigned int height = bot.screenHeight();
        std::cout << "screen width = " << width << std::endl;
        std::cout << "screen height = " << height << std::endl;

        // sum each component;
        unsigned long long red = 0;
        unsigned long long green = 0;
        unsigned long long blue = 0;

        for(int y = 0; y<height; ++y)
        for(int x = 0; x<width;  ++x)
        {
            red   += screen[0 + 3 * (x + width * y) ];
            green += screen[1 + 3 * (x + width * y) ];
            blue  += screen[2 + 3 * (x + width * y) ];
        }
        red   /= width * height;
        green /= width * height;
        blue  /= width * height;

        std::cout << "mean color = (" << red << "," << green << "," << blue << ")" << std::endl;
    }
    return 0;
}

#include "CPPBot"

#include <unistd.h> // for usleep
#include <iostream> // for std::cout

int main(int argc, const char *argv[])
{
    CPPBot bot;

    // get screen dimension;
    const int width = bot.screenWidth();
    const int height = bot.screenHeight();

    // center mouse
    bot.mousePosition(width/2,height/2);

    // clic
    bot.mouse(CPPBot::LEFT);

    // print a,r,t,h,u,r
    bot.keyboard('a');
    bot.keyboard('r');
    bot.keyboard('t');
    bot.keyboard('h');
    bot.keyboard('u');
    bot.keyboard('r');

    // selection
    bot.mousePosition(width/2,height/2);
    bot.mousePress(CPPBot::LEFT);
    for(int i = 0; i<300; i+=3)
    {
        usleep(10000);
        bot.mousePosition(width/2-i,height/2-i);
    }
    bot.mouseRelease(CPPBot::LEFT);

    // take a screenshot
    const unsigned char* screen = bot.screen();

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
    return 0;
}

#include <iostream>
#include "CPPBot"
#include <cmath>
#include <fstream>

// todo remove
#include <unistd.h>

int main(int argc, const char *argv[])
{
    CPPBot bot;


    // print a,r,t,h,u,r
    bot.keyboard('a');
    bot.keyboard('r');
    bot.keyboard('t');
    bot.keyboard('h');
    bot.keyboard('u');
    bot.keyboard('r');

    for(int i = 0; i<1000; ++i)
    {
        std::cout << "i=" << i << std::endl;
        for(int i = 0; i<30; ++i)
        bot.screen();
    }

    const int width = bot.screenWidth();
    const int height = bot.screenHeight();

    std::cout << "width = " << width << std::endl;
    std::cout << "height = " << height<< std::endl;

    for(int i = 0; i<1; ++i)
    {
        const unsigned char * screen = bot.screen();
        int bestX = 0;
        int bestY = 0;
        int best = 0;
        for(int y = 0; y<height; ++y)
            for(int x = 0; x<width; ++x)
            {
                int red   = screen[0 + 3 * ( x + width * y)];
                int green = screen[1 + 3 * ( x + width * y)];
                int blue  = screen[2 + 3 * ( x + width * y)];
                int value = red+green+blue;
                if (value>best)
                {
                    best = value;
                    bestX = x;
                    bestY = y;
                }
            }
        std::cout << "bestValue = " << best/3 << std::endl;
        std::cout << "x = " << bestX << std::endl;
        std::cout << "y = " << bestY << std::endl;
        std::ofstream output("output.raw",std::ios::binary);
        output.write((char*)screen, 3*width*height);
    }

    std::cout << "width = " << width << std::endl;
    std::cout << "height = " << height<< std::endl;

    return 0;


    int mouse_x, mouse_y;
    int previous_mouse_x, previous_mouse_y;

    for(int t = 0; t<1; ++t)
    {
        //bot.mouseGetPosition(mouse_x,mouse_y);
        //if (previous_mouse_x!=mouse_x || previous_mouse_y!=mouse_y)
        //std::cout << "(" << mouse_x << "," << mouse_y << ")" << std::endl;
        //previous_mouse_x = mouse_x;
        //previous_mouse_y = mouse_y;
        usleep(10000);
        //bot.mousePosition(500+60*sin(t*0.05),500+60*cos(t*0.05));

        const unsigned char * s = bot.screen();
        std::cout << int(s[0]) << " ";
        std::cout << int(s[1]) << " ";
        std::cout << int(s[2]) << std::endl;
        std::cout << t << std::endl;

        std::cout << bot.screenWidth() << " " << bot.screenHeight() << std::endl;

        /*
        if (t%100==0)
        {
            std::cout << t << std::endl;
            if (t%200 == 0)
                bot.mousePress(CPPBot::LEFT);
            else
            {
                bot.mouseRelease(CPPBot::LEFT);
                bot.mouse(CPPBot::LEFT);
                const unsigned char * s = bot.screen();
                int width = bot.screenWidth();
                int height = bot.screenHeight();

                unsigned long long sum = 0;
                for(int y = 0; y<height; ++y)
                for(int x = 0; x<width;++x)
                {
                    sum += s[0+3*(x+width*y)];
                    sum += s[1+3*(x+width*y)];
                    sum += s[2+3*(x+width*y)];
                }
                std::cout << "sum=" << (sum/width/height/3) << std::endl;

            }
        }
        */
    }

    return 0;
}

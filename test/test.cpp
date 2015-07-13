#include <iostream>
#include "CPPBot"
#include <cmath>

// todo remove
#include <unistd.h>

int main(int argc, const char *argv[])
{
    CPPBot bot;


    //bot.keyboardPress('a');
    //bot.keyboardPress('r');
    //bot.keyboardPress('t');
    //bot.keyboardPress('h');
    //bot.keyboardPress('u');
    //bot.keyboardPress('r');

    //while(1)
    //{
        //for(int i = 0; i<10000000; ++i)
        //bot.keyboardPress('w');
    //}

    int mouse_x, mouse_y;
    int previous_mouse_x, previous_mouse_y;

    for(int t = 0; t<1000; ++t)
    {
        //bot.mouseGetPosition(mouse_x,mouse_y);
        //if (previous_mouse_x!=mouse_x || previous_mouse_y!=mouse_y)
        //std::cout << "(" << mouse_x << "," << mouse_y << ")" << std::endl;
        //previous_mouse_x = mouse_x;
        //previous_mouse_y = mouse_y;
        usleep(10000);
        //bot.mousePosition(500+60*sin(t*0.05),500+60*cos(t*0.05));

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
    }

    return 0;
}

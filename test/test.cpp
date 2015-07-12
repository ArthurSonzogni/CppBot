#include <iostream>
#include "CPPBot"

int main(int argc, const char *argv[])
{
    CPPBot bot;


    bot.keyboardPress('a');
    bot.keyboardPress('r');
    bot.keyboardPress('t');
    bot.keyboardPress('h');
    bot.keyboardPress('u');
    bot.keyboardPress('r');

    //while(1)
    //{
        //for(int i = 0; i<10000000; ++i)
        //bot.keyboardPress('w');
    //}

    int mouse_x, mouse_y;
    int previous_mouse_x, previous_mouse_y;
    while(1)
    {
        bot.mouseGetPosition(mouse_x,mouse_y);
        if (previous_mouse_x!=mouse_x || previous_mouse_y!=mouse_y)
        std::cout << "(" << mouse_x << "," << mouse_y << ")" << std::endl;
        previous_mouse_x = mouse_x;
        previous_mouse_y = mouse_y;
    }

    return 0;
}

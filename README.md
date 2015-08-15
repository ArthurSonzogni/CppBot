C++Bot
======

Tools for creating your bot in **C++**.

Features : 
=========

* generate **keyboard** events
* generate **mouse** events
* access **screen** pixels data.
* portable (Linux, Windows, MacOS)

Work in progress
================

| Feature  | Linux | Windows | Mac |
| -------- | ----- | --------| --- |
| keyboard | 100%  | 100%    | 0%  |
| Mouse    | 100%  | 100%    | 0%  |
| Screen   | 100%  | 100%    | 0%  |

Usage
=====
This is the API :
```C++
class CPPBot
{
    public:
        enum { LEFT = 0, MIDDLE = 1, RIGHT = 2};

        // keyboard
        void keyboardPress(const int key);
        void keyboardRelease(const int key);
        void keyboard(const int key);

        // mouse
        void mousePosition(const int x, const int y);
        void mouseGetPosition(int& x, int& y);
        void mousePress(const int button);
        void mouseRelease(const int button);
        void mouse(const int button);
        
        // screen
        const unsigned char* screen();
        const int screenWidth();
        const int screenHeight();

        // initialisation
        CPPBot();
        // destruction
        ~CPPBot();
};
```

Contribution
============

I am open to contributions, especialy the MacOS implementation, bug fixes, performances improvements and API suggestions.
Thanks you !

I hope it could be useful.

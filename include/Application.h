#ifndef __Application__
#define __Application__

#define SFML_STATIC
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Grid.h"

class Application
{
public:
    Application(unsigned int width, unsigned int height, char* name);
    ~Application();
    void run();
    void draw();
    void logic();
    void updateGrid(unsigned int x, unsigned int y);
    sf::RenderWindow* GetWindow() {return window;}
private:
    sf::RenderWindow* window = nullptr;
    sf::Event ev;
    Grid mGrid;
    bool Started = false;
    unsigned int mGridRows;
    unsigned int mGridCols;
    unsigned int mWidth;
    unsigned int mHeight;
    unsigned int mOffsetX;
    unsigned int mOffsetY;
    unsigned int mFramerate;
};

#endif
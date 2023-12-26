#include "Application.hpp"
#include <iostream>

Application::Application(unsigned width, unsigned height, char* name) : mWidth(width), mHeight(height)
{
    window = new sf::RenderWindow(sf::VideoMode(width, height), name, sf::Style::Titlebar | sf::Style::Close);
    mGridCols = 100;
    mGridRows = 100;
    mOffsetX = 10;
    mOffsetY = 20;
    mGrid = Grid(mGridRows,mGridCols,mOffsetX,mOffsetY,window);
    mFramerate = 5;
}

void Application::run()
{
    sf::Clock clock;
    sf::Time timePeriod = sf::seconds(1.f/mFramerate);
    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();
            else if (event.type == sf::Event::MouseButtonPressed) {
                if(event.mouseButton.button == sf::Mouse::Left) {
                    std::cout<<"Left Mouse Click detected"<<std::endl;
                    std::cout<<"x: "<<event.mouseButton.x<<std::endl;
                    std::cout<<"y: "<<event.mouseButton.y<<std::endl;
                    updateGrid(event.mouseButton.x,event.mouseButton.y);
                }
            } else if(event.type == sf::Event::KeyPressed) {
                if(event.key.code == sf::Keyboard::S)
                {
                    Started = true;
                    std::cout<<"Pressed S"<<std::endl;
                }
                else if(event.key.code == sf::Keyboard::E)
                {
                    Started = false;
                    std::cout<<"Pressed E"<<std::endl;
                }
            }
        }

        window->clear();
        draw();
        mGrid.draw();
        if(Started)
        {
            logic();
            sf::Time elapsed = clock.restart();
            sf::sleep(timePeriod - elapsed);
        }

        window->display();
        
    }
}

void Application::updateGrid(unsigned int x, unsigned int y)
{
    // This should figure out which cell the mouse click falls under
    // And call the setCell function for the respective cell
    float rowH = (float)(mHeight - (2 * mOffsetY))/(mGridRows);
    float colW = (float)(mWidth - (2 * mOffsetX))/(mGridCols); 
    int xVal = (x - mOffsetX)/colW;
    int yVal = (y - mOffsetY)/rowH;
    if(xVal >= 0 && xVal < mGridRows && yVal >= 0 && yVal <mGridCols)
        std::cout<<"column value: "<< xVal <<" row value:"<<yVal<<std::endl;
        std::cout<<"rowH: "<< rowH <<" colW: "<<colW<<std::endl;
        mGrid.setCell(yVal,xVal);
        int s = mGrid.getLiveNeigbours(yVal,xVal);
        std::cout<<"Neigbours: "<<s<<std::endl;
}

void Application::logic()
{
    int neighbour;
    bool state;
    auto points = mGrid.getPoints();
    // Any live cell with two or three live neighbours survives.
    // Any dead cell with three live neighbours becomes a live cell.
    // All other live cells die in the next generation. Similarly, all other dead cells stay dead.
    for(int i =0; i<mGridRows; i++)
    {
        for(int j = 0; j<mGridCols; j++)
        {
            neighbour = mGrid.getLiveNeigbours(i,j);
            state = mGrid.viewCell(i,j);
            // Game of life rules go here
            if(state)
            {
                if(neighbour != 2 && neighbour != 3)
                    points[i][j] = false;
 
           } else
            {
                if(neighbour == 3)
                    points[i][j] = true;
            }
        }
    }

    mGrid.setPoints(points);
}

void Application::draw()
{
    // This will draw the outline of the program i.e, everything apart from the grid
    // sf::VertexArray arr(sf::Quads,4);
    // window->draw(arr);
}

Application::~Application()
{
    delete window;
}

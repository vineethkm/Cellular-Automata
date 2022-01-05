#ifndef __Grid__
#define __Grid__

#define SFML_STATIC
#include <SFML/Graphics.hpp>
#include <unordered_map>

class Grid
{
public: 
    Grid() {}
    Grid(unsigned int rows, unsigned int columns, unsigned int offsetX, unsigned int offsetY, sf::RenderWindow* window);  
    Grid(Grid& other) = default;
    void draw();
    void update();
    void setCell(unsigned int x, unsigned int y);
    bool viewCell(unsigned int x, unsigned int y);
    auto getPoints() { return points; }
    void setPoints(std::unordered_map<int, std::unordered_map<int,bool>> arr) { points = arr; }
    int getLiveNeigbours(unsigned int x, unsigned int y);

private:
    sf::RenderWindow* mWindow = nullptr; 
    std::unordered_map<int, std::unordered_map<int,bool>> points;
    sf::VertexArray mVertexArray;
    unsigned int mRows;
    unsigned int mColumns;
    unsigned int mOffsetX;
    unsigned int mOffsetY;
};

#endif
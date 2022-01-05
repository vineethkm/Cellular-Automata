#include "Grid.h"

Grid::Grid(unsigned int rows, unsigned int columns, unsigned int offsetX, unsigned int offsetY, sf::RenderWindow* window): 
    mRows(rows), mColumns(columns), mWindow(window), mOffsetX(offsetX), mOffsetY(offsetY)
{
    auto size = mWindow->getView().getSize();
    float rowH = (size.y - (2 * offsetY))/((float)mRows);  
    float colW = (size.x - (2 * offsetX))/((float)mColumns);  

    for(int i = 0; i<mRows; i++)
    {
        for(int j = 0; j<mColumns; j++)
        {
            points[i][j] = false;
        }
    }
    mVertexArray.resize(mRows * mColumns * 4);
    mVertexArray.setPrimitiveType(sf::Quads);
    for(int i = 0; i < mRows; i++) {
        for(int j = 0; j < mColumns; j++) {
            mVertexArray[4*((i*mRows)+j)].position = {(colW * j) + offsetX , (rowH * (i + 1)) + offsetY};
            mVertexArray[4*((i*mRows)+j)+1].position = {(colW * j) + offsetX, (rowH * i) + offsetY};
            mVertexArray[4*((i*mRows)+j)+2].position = {(colW * (j + 1)) + offsetX, (rowH * i) + offsetY};
            mVertexArray[4*((i*mRows)+j)+3].position = {(colW * (j + 1)) + offsetX, (rowH * (i + 1)) + offsetY};
            
            mVertexArray[4*((i*mRows)+j)].color = sf::Color::Black;
            mVertexArray[4*((i*mRows)+j)+1].color = sf::Color::Black;
            mVertexArray[4*((i*mRows)+j)+2].color = sf::Color::Black;
            mVertexArray[4*((i*mRows)+j)+3].color = sf::Color::Black;
        }
    }
}

void Grid::draw()
{
    update();
    mWindow->draw(mVertexArray);
}

void Grid::update()
{
    // Update color of mVertexArray based on value of boolean points matrix
    // Black: sf::Color::Black White: sf::Color::White;
    for(int i = 0; i<mRows ; i++)
    {
        for(int j = 0; j<mColumns ; j++)
        {
            if(points[i][j]) {
                mVertexArray[4*((i*mRows)+j)].color = sf::Color::White;
                mVertexArray[4*((i*mRows)+j)+1].color = sf::Color::White;
                mVertexArray[4*((i*mRows)+j)+2].color = sf::Color::White;
                mVertexArray[4*((i*mRows)+j)+3].color = sf::Color::White;
            } else {
                mVertexArray[4*((i*mRows)+j)].color = sf::Color::Black;
                mVertexArray[4*((i*mRows)+j)+1].color = sf::Color::Black;
                mVertexArray[4*((i*mRows)+j)+2].color = sf::Color::Black;
                mVertexArray[4*((i*mRows)+j)+3].color = sf::Color::Black;
            }
        }
    }
}

void Grid::setCell(unsigned int x, unsigned int y)
{
    points[x][y] = !points[x][y];
}

bool Grid::viewCell(unsigned int x, unsigned int y)
{
    return points[x][y];
}

int Grid::getLiveNeigbours(unsigned int x, unsigned int y)
{
    int sum = 0;
    int row,col;
    // add code for the edge cases as well
    for(int i = -1; i<2; i++)
    {
        for(int j= -1; j<2; j++)
        {
            if(i == 0 && j == 0)
                continue;
            row = (int)x + i;
            col = (int)y + j;
            if(row<0 || col<0 || row>mRows-1 || col>mColumns-1)
                continue;
            sum += (int)points[row][col];
        }
    }
    
    return sum;
}
#include<iostream>

#define SFML_STATIC
#include <SFML/Graphics.hpp>
#include <Application.hpp>

int main()
{
    Application app(800,600, "Application");
    auto window = app.GetWindow();
    auto size = window->getView().getSize();
    std::cout<<"Window Size: ("<<size.x<<","<<size.y<<")"<<std::endl;
    app.run();

    return 0;
}

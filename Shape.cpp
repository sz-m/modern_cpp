#include "Shape.hpp"
#include <map>
#include <iostream>

void Shape::print() const
{
    std::cout << "Unknown Shape" << std::endl;
}

std::string Shape::getName() const
{
    return "Shape";
}

std::string Shape::getColor() const
{
  std::map<Color, std::string> colors{{Color::GREEN, "green"}, {Color::RED, "red"}, {Color::BLUE, "blue"}};
  return colors[_color];
}

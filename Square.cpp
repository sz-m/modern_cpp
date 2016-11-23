#include "Square.hpp"
#include <iostream>

Square::Square(double x, Color color)
    : Rectangle(x, x, color)
{
}

Square::Square(const Square &other)
    : Rectangle(other.getX(), other.getX(), Shape::_color)
{}

double Square::getArea()
{
    return getX() * getX();
}

double Square::getPerimeter()
{
    return 4 * getX();
}

std::string Square::getName() const
{
    return "Square";
}

void Square::print()
{
    std::cout << getName() << ":    x: " << getX()
              << ", area: " << getArea()
              << ", perimeter: " << getPerimeter()
              << ", color: " << getColor() << std::endl;
}

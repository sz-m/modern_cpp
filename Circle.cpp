#include "Circle.hpp"
#include <math.h>
#include <iostream>

Circle::Circle(double r, Color color)
    : r_(r), Shape{color}
{}

Circle::Circle(double r)
    : Circle(r, Color::RED)
{}

Circle::Circle(const Circle & other)
{
    r_ = other.getRadius();
}

double Circle::getArea() const
{
    return M_PI * r_ * r_;
}

double Circle::getPerimeter() const
{
    return 2 * M_PI * r_;
}

double Circle::getRadius() const
{
    return r_;
}

std::string Circle::getName() const
{
    return "Circle";
}

double Circle::getPi() const
{
  return 3.14;
}

void Circle::print() const
{
    std::cout << getName() << ":    radius: " << getRadius()
              << ", area: " << getArea()
              << ", perimeter: " << getPerimeter()
              << ", color: " << getColor() << std::endl;
}

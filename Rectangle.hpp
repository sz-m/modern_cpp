#pragma once

#include "Shape.hpp"

class Rectangle : public Shape
{
public:
    Rectangle(double x, double y, Color color);
    Rectangle(const Rectangle & other);

    double getArea() const;
    double getPerimeter() const;
    double getX() const;
    double getY() const;
    std::string getName() const;
    void print() const;

private:
    Rectangle();

    double x_;
    double y_;
};

#pragma once

#include "Rectangle.hpp"

class Square : public Rectangle
{
public:
    Square() = delete;
    Square(double x, Color color);
    Square(const Square & other);

    double getArea() const override;
    double getPerimeter() const override;
    std::string getName() const override;
    void print() const override;

    double getY() = delete; // should not have Y dimension
};

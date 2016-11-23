#pragma once

#include "Shape.hpp"

class alignas(64) Circle : public Shape
{
public:
    Circle() = delete; // doesn't allow to call default constructor
    Circle(double r, Color color);
    Circle(const Circle & other);

    double getArea() const override;
    double getPerimeter() const override;
    double getRadius() const;
    std::string getName() const override;
    void print() const override;

//    [[deprecated("do not use")]]
    double getPi() const;

private:
    double r_;
};

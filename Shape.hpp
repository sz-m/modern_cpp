#pragma once

#include <string>

enum class Color
{
  RED,
  BLUE,
  GREEN
};

class Shape
{
public:
    Shape() :_color{Color::RED} {}
    Shape(Color color) :_color{color} {}
    virtual ~Shape() {}

    virtual double getArea() const = 0;
    virtual double getPerimeter() const = 0;
    virtual std::string getName() const;
    virtual void print() const;

    std::string getColor() const;

protected:
    Color _color;
};

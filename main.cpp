#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <thread>
#include "Shape.hpp"
#include "Rectangle.hpp"
#include "Square.hpp"
#include "Circle.hpp"

using namespace std;

using Collection = vector<Shape *>;

bool sortByArea(Shape* first, Shape* second)
{
    if(first == nullptr || second == nullptr)
    {
        return false;
    }
    return (first->getArea() < second->getArea());
}

bool perimeterBiggerThan20(Shape* s)
{
    if(s)
    {
        return (s->getPerimeter() > 20);
    }
    return false;
}

bool areaLessThan10(Shape* s)
{
    if(s)
    {
        return (s->getArea() < 10);
    }
    return false;
}

bool printCollectionElements(const auto& collection)
{
    for(auto it = collection.begin(); it != collection.end(); ++it)
    {
        if(*it != nullptr)
        {
            (*it)->print();
        }
    }
}

void printArea(std::string name, double area)
{
    std::cout << "thread_id: " << std::this_thread::get_id() << " - " << name << ": " << area << std::endl;
}

void printAreas(const auto& collection)
{
    std::vector<std::thread> threads;
    for(auto it = collection.begin(); it != collection.end(); ++it)
    {
        if(*it != nullptr)
        {
            std::thread th(printArea, (*it)->getName(), (*it)->getArea());
            threads.push_back(std::move(th));
        }
    }
    for(auto i = 0; i < threads.size(); i++)
    {
        threads[i].join();
    }
}

void findFirstShapeMatchingPredicate(const auto& collection,
                                     bool (*predicate)(Shape* s),
                                     std::string info)
{
    auto iter = std::find_if(collection.begin(), collection.end(), predicate);
    if(*iter != nullptr)
    {
        cout << std::endl << "First shape matching predicate: " << info << endl;
        (*iter)->print();
    }
    else
    {
        cout << std::endl << "There is no shape matching predicate " << info << endl;
    }
}


class BlockingQueue
{
public:
    void push(Shape* shape)
    {
        // TODO
    }

    Shape* pop()
    {
        // TODO
        return nullptr;
    }
};

BlockingQueue g_queue;

void runQueue()
{
    bool running = true;
    while(running)
    {
        Shape * shape = g_queue.pop();
        if(shape == nullptr)
        {
            std::cout << "Queue received NULL, finishing loop" << std::endl;
            break;
        }
        else
        {
            std::cout << "Shape on queue: " << shape->getName() << std::endl;
        }
    }
}

void pushShapesToQueue(auto const& shapes)
{
    for(auto i = 0; i < shapes.size(); ++i)
    {
        g_queue.push(shapes[i]);
    }
}

int main()
{
  std::cout << "Alignment of...\n"
  << "Shape: " << alignof(Shape) << std::endl
  << "Circle: " << alignof(Circle) << std::endl
  << "Rectangle: " << alignof(Rectangle) << std::endl
  << "Int: " << alignof(int) << std::endl
  << "---------------------------" << std::endl << std::endl;

  std::cout << "Size of...\n"
  << "Shape: " << sizeof(Shape) << std::endl
  << "Circle: " << sizeof(Circle) << std::endl
  << "Rectangle: " << sizeof(Rectangle) << std::endl
  << "Int: " << sizeof(int) << std::endl
  << "---------------------------" << std::endl << std::endl;

  cout << "pi: " << (new Circle(2.0, Color::RED))->getPi() << std::endl;

    Collection shapes;
    shapes.push_back(new Circle(2.0, Color::BLUE));
    shapes.push_back(new Circle(3.0, Color::RED));
    shapes.push_back(nullptr);
    shapes.push_back(new Circle(4.0, Color::GREEN));
    shapes.push_back(new Rectangle(10.0, 5.0, Color::BLUE));
    shapes.push_back(new Square(3.0, Color::GREEN));
    shapes.push_back(new Circle(4.0, Color::BLUE));

    printCollectionElements(shapes);

    cout << std::endl << "Areas before sort: " << std::endl;
    printAreas(shapes);

    std::sort(shapes.begin(), shapes.end(), sortByArea);

    cout << std::endl << "Areas after sort: " << std::endl;
    printAreas(shapes);

    Square* square = new Square(4.0, Color::RED);
    shapes.push_back(square);

    findFirstShapeMatchingPredicate(shapes, perimeterBiggerThan20, "perimeter bigger than 20");
    findFirstShapeMatchingPredicate(shapes, areaLessThan10, "area less than 10");

    std::thread queueThread(runQueue);
    pushShapesToQueue(shapes);

    queueThread.join();

    return 0;

}


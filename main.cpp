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

using Collection = vector<std::shared_ptr<Shape>>;

template<class DerivedType, class... Arguments>
std::shared_ptr<Shape> make_shape(Arguments&& ...args)
{
  return std::make_shared<DerivedType>(std::forward<Arguments>(args)...);
}

auto sortByArea = [](std::shared_ptr<Shape> first, std::shared_ptr<Shape> second)
{
  if(first == nullptr || second == nullptr)
  {
    return false;
  }
  return (first->getArea() < second->getArea());
};

auto perimeterBiggerThan20 = [](std::shared_ptr<Shape> s)
{
  if(s)
    return (s->getPerimeter() > 20);

  return false;
};

auto areaLessThan10 = [](std::shared_ptr<Shape> s)
{
  if(s)
    return (s->getArea() < 10);

  return false;
};

auto printCollectionElements = [](const auto& collection)
{
  for(auto it = collection.begin(); it != collection.end(); ++it)
  {
    if(*it != nullptr)
      (*it)->print();
  }
};

auto printArea = [](std::string name, double area)
{
  std::cout << "thread_id: " << std::this_thread::get_id() << " - " << name << ": " << area << std::endl;
};

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
                                     bool (*predicate)(std::shared_ptr<Shape> s),
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
    void push(std::shared_ptr<Shape> shape)
    {
        // TODO
    }

    std::shared_ptr<Shape> pop()
    {
        // TODO
        return nullptr;
    }
};

BlockingQueue g_queue;

void runQueue()
{
    constexpr bool running = true;
    while(running)
    {
        std::shared_ptr<Shape> shape = g_queue.pop();
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

  std::cout << "pi: " << std::make_shared<Circle>(Circle(2.0, Color::RED))->getPi() << std::endl;

  std::make_shared<Circle>(1.1)->print();

    Collection shapes{make_shape<Circle>(2.0, Color::BLUE),
                      make_shape<Circle>(3.0, Color::RED),
                      nullptr,
                      make_shape<Circle>(4.0, Color::GREEN),
                      make_shape<Rectangle>(10.0, 5.0, Color::BLUE),
                      make_shape<Square>(3.0, Color::GREEN),
                      make_shape<Circle>(4.0, Color::BLUE),
                      make_shape<Circle>(7.0)};

    printCollectionElements(shapes);

    cout << std::endl << "Areas before sort: " << std::endl;
    printAreas(shapes);

    std::sort(shapes.begin(), shapes.end(), sortByArea);

    cout << std::endl << "Areas after sort: " << std::endl;
    printAreas(shapes);

    auto square = make_shape<Square>(Square(4.0, Color::RED));
    shapes.push_back(square);

    findFirstShapeMatchingPredicate(shapes, perimeterBiggerThan20, "perimeter bigger than 20");
    findFirstShapeMatchingPredicate(shapes, areaLessThan10, "area less than 10");

    std::thread queueThread(runQueue);
    pushShapesToQueue(shapes);

    queueThread.join();

    return 0;

}


#include "../include/tiny_traits.hpp"

struct Point {
    int x, y;

    explicit Point(int x, int y) : x(x), y(y) {}


    // Point(const Point&) = default;
    // Point& operator=(const Point&) = default;

    // Point(const Point&) = delete;
    // Point& operator=(const Point&) = delete;

    // Point(Point&&) = default;
    // Point& operator=(Point&&) = default;

    // Point(Point&&) = delete;
    // Point& operator=(Point&&) = delete;
};

int main() {
    Point p1{1, 2};
    Point p2{2, 3};

    Point p3(p1);
    p1 = p2;

    Point p4(std::move(p1));
    p1 = std::move(p2);

    return 0;
}

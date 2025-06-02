#include "../include/tiny_traits.hpp"

struct Point : tiny_traits::Eq<Point> {
    int x;
    int y;

    explicit Point(int x, int y) : x(x), y(y) {}

    bool equals(const Point& other) const {
        return (x == other.x) && (y == other.y);
    }
};

int main() {
    Point p1{1, 2};
    Point p2{2, 3};
    Point p3{1, 2};

    std::cout << std::boolalpha << (p1 == p2) << std::endl; // false
    std::cout << std::boolalpha << (p1 != p2) << std::endl; // true
    std::cout << std::boolalpha << (p1 == p3) << std::endl; // true
    std::cout << std::boolalpha << (p1 != p3) << std::endl; // false
    return 0;
}

#include "../include/tiny_traits.hpp"
#include <utility>

using namespace tiny_traits;

struct Point : tiny_traits::Into<int, Point>, tiny_traits::Into<std::pair<int, int>, Point> {
    int x;
    int y;

    explicit Point(int x, int y) : x(x), y(y) {}

    operator int() const {
        return x * x + y * y;
    }

    operator std::pair<int, int>() const {
        return {x, y};
    }
};

int main() {
    Point p{3, 4};
    int dist = p;
    std::cout << dist << std::endl;

    std::pair<int, int> vec2d = p;
    std::cout << vec2d.first << ", " << vec2d.second << std::endl;
    return 0;
}

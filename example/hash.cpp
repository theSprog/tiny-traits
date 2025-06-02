#include "../include/tiny_traits.hpp"
#include <string>
#include <unordered_map>

using namespace tiny_traits;

struct Point : tiny_traits::Hashable<Point> {
    int x;
    int y;

    explicit Point(int x, int y) : x(x), y(y) {}

    std::size_t hashcode() const {
        return std::hash<int>()(x) ^ std::hash<int>()(y << 1);
    }

    bool equals(const Point& other) const {
        return (x == other.x) && (y == other.y);
    }
};

int main() {
    std::unordered_map<Point, std::string, tiny_traits::Hasher> mp;

    Point p1{1, 2};
    Point p2{2, 3};

    // mp[p1] = "p1";
    // mp[p2] = "p2";

    // std::cout << mp[p1] << std::endl;
    // std::cout << mp[p2] << std::endl;
    return 0;
}

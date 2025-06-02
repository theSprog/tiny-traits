#include "../include/tiny_traits.hpp"

using namespace tiny_traits;

struct Point : tiny_traits::PartialOrd<Point> {
    int x;
    int y;

    explicit Point(int x, int y) : x(x), y(y) {}

    OptionalOrdering partial_compare(const Point& other) const {
        if (x == other.x && y == other.y) {
            return tiny_traits::Ordering::Equal;
        } else if (x < other.x && y < other.y) {
            return tiny_traits::Ordering::Less;
        } else if (x > other.x && y > other.y) {
            return tiny_traits::Ordering::Greater;
        }
        return OptionalOrdering::NotComparable(); // not comparable
    }
};

struct VecPoint : tiny_traits::Ord<VecPoint> {
    int x;
    int y;

    explicit VecPoint(int x, int y) : x(x), y(y) {}

    Ordering compare(const VecPoint& other) const {
        int this_dis = x * x + y * y;
        int other_dis = other.x * other.x + other.y + other.y;

        if (this_dis < other_dis) {
            return tiny_traits::Ordering::Less;
        } else if (this_dis > other_dis) {
            return tiny_traits::Ordering::Greater;
        }

        return Ordering::Equal;
    }
};

int main() {
    {
        Point p1{1, 2};
        Point p2{2, 3};
        Point p3{2, 3};
        Point p4{2, 1};

        std::cout << std::boolalpha << (p1 < p2) << std::endl; // true
        std::cout << std::boolalpha << (p2 < p3) << std::endl; // false
        std::cout << std::boolalpha << (p3 < p4) << std::endl; // false
    }

    std::cout << std::endl;

    {
        VecPoint p1{3, 4}; // 3^2 + 4^4 = 25
        VecPoint p2{4, 3}; // 4^2 + 3^2 = 25
        VecPoint p3{5, 1}; // 5^2 + 1^2 = 26
        VecPoint p4{2, 1}; // 2^2 + 1^2 = 5

        std::cout << std::boolalpha << (p1 < p2) << std::endl; // false
        std::cout << std::boolalpha << (p2 < p3) << std::endl; // true
        std::cout << std::boolalpha << (p3 > p4) << std::endl; // true
    }

    return 0;
}

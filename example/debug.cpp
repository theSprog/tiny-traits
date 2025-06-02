#include "../include/tiny_traits.hpp"

struct Point : tiny_traits::Debug {
    int x;
    int y;

    explicit Point(int x, int y) : x(x), y(y) {}

    void debug(std::ostream& os) const override {
        os << "Point(" << x << ", " << y << ")";
    }
};

int main() {
    Point p{1, 2};
    std::cout << p << std::endl;
    return 0;
}

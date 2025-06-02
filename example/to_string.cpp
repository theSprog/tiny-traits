#include "../include/tiny_traits.hpp"

struct Point : tiny_traits::ToString {
    int x;
    int y;

    explicit Point(int x, int y) : x(x), y(y) {}

    std::string to_string() const override {
        std::ostringstream oss;
        oss << "(" << x << ", " << y << ")";
        return oss.str();
    }
};

int main() {
    Point p{1, 2};
    std::cout << p.to_string() << std::endl;
    return 0;
}

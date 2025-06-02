#include "../include/tiny_traits.hpp"

using namespace tiny_traits;

struct Point : tiny_traits::AsRef<int> {
    int x;
    int y;

    explicit Point(int x, int y) : x(x), y(y) {}

    int as_ref() const {
        return x * x + y * y;
    }
};

void print_int(tiny_traits::AsRef<int>& a) {
    std::cout << a.as_ref() << std::endl;
}

int main() {
    Point p{3, 4};
    print_int(p);
    return 0;
}

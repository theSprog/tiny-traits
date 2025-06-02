#include "../include/tiny_traits.hpp"
#include <iterator>
#include <vector>

using namespace tiny_traits;

struct MyContainer : Iterable<MyContainer> {
    std::vector<int> data = {10, 20, 30};

    // --- 普通迭代器 --------------------------------------------------------
    struct iterator {
        int* ptr;

        explicit iterator(int* p) : ptr(p) {}

        int& operator*() const {
            return *ptr;
        }

        iterator& operator++() {
            ++ptr;
            return *this;
        }

        bool operator!=(const iterator& o) const {
            return ptr != o.ptr;
        }
    };

    // --- 常量迭代器 --------------------------------------------------------
    struct const_iterator {
        const int* ptr;

        explicit const_iterator(const int* p) : ptr(p) {}

        const int& operator*() const {
            return *ptr;
        }

        const_iterator& operator++() {
            ++ptr;
            return *this;
        }

        bool operator!=(const const_iterator& o) const {
            return ptr != o.ptr;
        }
    };

    // 非常量 begin/end
    iterator begin() {
        return iterator{data.data()};
    }

    iterator end() {
        return iterator{data.data() + data.size()};
    }

    // 常量 begin/end
    const_iterator begin() const {
        return const_iterator{data.data()};
    }

    const_iterator end() const {
        return const_iterator{data.data() + data.size()};
    }

    void push(int val) {
        data.push_back(val);
    }
};

int main() {
    MyContainer c;
    c.push(114514);

    const MyContainer cc;

    // 1. 非常量对象 → iterator
    for (auto x : c) std::cout << x << ' ';
    std::cout << '\n';

    // 2. 常量对象 → const_iterator
    std::copy(cc.begin(), cc.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << '\n';
}

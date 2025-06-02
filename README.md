tiny-trait is a **header-only C++11 trait library** that brings the power and clarity of Rust’s trait system to C++. It allows you to **enforce user-defined interfaces** (e.g., `debug()`, `equals()`, `hash()`, etc.) at compile-time，This leads to **zero-cost abstractions** and **idiomatic trait-based design** that fits seamlessly into modern C++ projects.



## ✨ Features

- **Header-only** and fully compatible with C++11 (and later).
- **Enforces user implementation** of key methods (like `debug()`, `equals()`, etc.).
- **Rust-inspired**: clear separation of trait interfaces and user implementations.
- **Composable**: traits can be freely combined to build rich, type-safe abstractions.

The core interface definitions are in `include/details/*.hpp`, while `tiny_traits.hpp` provides an easy entry point to include them all.



## 🚀 Getting Started

just `cp` the header file into your project:

```cpp
cp -r include/ your_project/
```

Then inherit the traits you need:

```cpp
struct MyType : Debug, Eq<MyType>, Hashable<MyType> { 
    // Must provide debug(std::ostream&), equals(const MyType&), hash()...
};
```

The compiler will enforce that your type **fully implements these methods**, ensuring robust and clear API contracts.




## 🔬 Examples

This project comes with a set of practical examples to showcase how to use each trait in a real-world scenario.

### Debug

It is similar to Rust’s `Debug`.  This trait enforces that you implement a `debug(std::ostream&)` method, and it automatically enables the `<<` operator for your type.

Here’s a simple `Point` struct example:

```cpp
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
    std::cout << p << std::endl;  // prints: Point(1, 2)
    return 0;
}
````

✅ **Key takeaways**:

* `Point` inherits from `tiny_traits::Debug`.
* The compiler will **enforce** that you implement the `debug()` method.
* `operator<<` is already provided by the trait – no need to implement it yourself.

This ensures that any type inheriting `Debug` can be printed using `std::cout`, following the Rust style but entirely in C++.



### Eq

It enforces that you provide your own equality comparison.  This trait automatically provides `operator==` and `operator!=` for your type, similar to Rust’s `PartialEq` / `Eq`.

Here’s how to use it with a simple `Point` struct:

```cpp
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
```

✅ **Key takeaways**:

- `Point` inherits from `tiny_traits::Eq<Point>`.
- The compiler **enforces** that you provide an `equals(const Point&)` method.
- `operator==` and `operator!=` are generated automatically, ensuring safe and consistent equality checks.

By keeping these operations explicit and user-defined, you get strong typing and reliable semantics across your codebase.



### PartialOrd and Ord

tiny-trait also includes `PartialOrd` and `Ord` traits to support comparison operations.  This allows you to control how objects of your type compare to each other, either partially (like `PartialOrd`) or fully (like `Ord`).

Here’s how to use both:

```cpp
using namespace tiny_traits;

// PartialOrd: may not always be comparable
struct Point : PartialOrd<Point> {
    int x;
    int y;

    explicit Point(int x, int y) : x(x), y(y) {}

    OptionalOrdering partial_compare(const Point& other) const {
        if (x == other.x && y == other.y) {
            return Ordering::Equal;
        } else if (x < other.x && y < other.y) {
            return Ordering::Less;
        } else if (x > other.x && y > other.y) {
            return Ordering::Greater;
        }
        return OptionalOrdering::NotComparable();
    }
};

// Ord: full ordering
struct VecPoint : Ord<VecPoint> {
    int x;
    int y;

    explicit VecPoint(int x, int y) : x(x), y(y) {}

    Ordering compare(const VecPoint& other) const {
        int this_dis = x * x + y * y;
        int other_dis = other.x * other.x + other.y * other.y;

        if (this_dis < other_dis) {
            return Ordering::Less;
        } else if (this_dis > other_dis) {
            return Ordering::Greater;
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
        std::cout << std::boolalpha << (p3 < p4) << std::endl; // false (not comparable)
    }

    std::cout << std::endl;

    {
        VecPoint p1{3, 4}; // distance: 25
        VecPoint p2{4, 3}; // distance: 25
        VecPoint p3{5, 1}; // distance: 26
        VecPoint p4{2, 1}; // distance: 5

        std::cout << std::boolalpha << (p1 < p2) << std::endl; // false
        std::cout << std::boolalpha << (p2 < p3) << std::endl; // true
        std::cout << std::boolalpha << (p3 > p4) << std::endl; // true
    }

    return 0;
}
```

✅ **Key takeaways**:

- **`PartialOrd`** enforces that you implement `partial_compare()`, which may return “not comparable.”
- **`Ord`** requires you to implement `compare()`, guaranteeing a full ordering.
- This example shows how `PartialOrd` types can refuse to compare in some cases, while `Ord` always provides a clear result.

These traits enable you to build **type-safe ordering logic** with clear semantics, just like in Rust – ensuring your data structures remain robust and expressive.



### Hashable

The `Hashable` trait in tiny-traits enforces that you provide a **custom `hashcode()` method**.  To ensure correctness when used in containers like `std::unordered_map`, it also **requires you to implement `equals()`** (like Rust’s `Hash + Eq` pairing).

Here’s an example with a `Point` struct:

```cpp
using namespace tiny_traits;

struct Point : Hashable<Point> {
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
    // Hasher is avaliable if you type implements Hashable
    std::unordered_map<Point, std::string, tiny_traits::Hasher> mp;

    Point p1{1, 2};
    Point p2{2, 3};

    mp[p1] = "p1";
    mp[p2] = "p2";

    std::cout << mp[p1] << std::endl; // p1
    std::cout << mp[p2] << std::endl; // p2
    return 0;
}
```

✅ **Key takeaways**:

- Inherit from `tiny_traits::Hashable<Point>` to **enforce** implementing `hashcode()` and `equals()`.
- Use the provided `tiny_traits::Hasher` as the third argument to `std::unordered_map` to ensure correct hashing.
- This guarantees your type works safely and consistently in hash-based containers.

By requiring both `hashcode()` and `equals()`, tiny-traits makes sure you always have a valid hash equality contract for your types.



👉 This project includes many more examples in the `example/` directory, demonstrating traits like `ToString`, `AsRef`, and custom iterators.  Feel free to explore them and see how tiny-traits can help make your C++ code more expressive and trait-based!

This is **not an industrial-grade project** – it’s a small hobbyist library inspired by Rust’s trait system.  If you find it interesting or useful, a ⭐️ on GitHub would be awesome



## License

MIT License 

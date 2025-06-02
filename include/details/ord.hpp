#pragma once

#include "utils.hpp"

namespace tiny_traits {
enum class Ordering {
    Less = -1,
    Equal = 0,
    Greater = 1
};

struct OptionalOrdering {
  private:
    bool comparable_;
    Ordering order_; // 只有 comparable==true 时有效

  public:
    static OptionalOrdering NotComparable() {
        return {false, Ordering::Equal};
    }

    OptionalOrdering() : comparable_(false), order_(Ordering::Equal) {}

    OptionalOrdering(Ordering order) : comparable_(true), order_(order) {}

    OptionalOrdering(bool comparable, Ordering order) : comparable_(comparable), order_(order) {}

    bool is_comparable() {
        return comparable_;
    }

    Ordering order() const {
        return order_;
    }

    bool is_equal() {
        return is_comparable() && order_ == Ordering::Equal;
    }

    bool is_greater() {
        return is_comparable() && order_ == Ordering::Greater;
    }

    bool is_less() {
        return is_comparable() && order_ == Ordering::Less;
    }
};

template <typename Derived, typename T = Derived>
struct PartialOrd {
  private:
    DEFINE_HAS_METHOD(partial_compare);

    // 偏序比较：返回可能为 not comparable，表示“不可比较”
    OptionalOrdering __inner_partial_compare(const T& other) const {
        static_assert(must_has_partial_compare<Derived, OptionalOrdering(const T& other)>::value,
                      "Derived must implement `OptionalOrdering partial_compare(const T& other) const`");
        return static_cast<const Derived&>(*this).partial_compare(other);
    }

  public:
    bool operator<(const T& other) const {
        auto cmp = __inner_partial_compare(other);
        return cmp.is_comparable() && cmp.order() == Ordering::Less;
    }

    bool operator>(const T& other) const {
        auto cmp = __inner_partial_compare(other);
        return cmp.is_comparable() && cmp.order() == Ordering::Greater;
    }

    bool operator<=(const T& other) const {
        auto cmp = __inner_partial_compare(other);
        return cmp.is_comparable() && cmp.order() != Ordering::Greater;
    }

    bool operator>=(const T& other) const {
        auto cmp = __inner_partial_compare(other);
        return cmp.is_comparable() && cmp.order() != Ordering::Less;
    }

    // 是否可以与 other 比较
    bool is_comparable(const T& other) const {
        return __inner_partial_compare(other).is_comparable();
    }
};

template <typename Derived, typename T = Derived>
struct Ord : PartialOrd<Derived, T> {
    DEFINE_HAS_METHOD(compare);

    Ordering __inner_compare(const T& other) const {
        static_assert(must_has_compare<Derived, Ordering(const T& other)>::value,
                      "Derived must implement `Ordering compare(const T& other) const`");
        return static_cast<const Derived&>(*this).compare(other);
    }

    // partial_compare 直接复用 compare
    OptionalOrdering partial_compare(const T& other) const {
        return OptionalOrdering(true, __inner_compare(other));
    }
};


} // namespace tiny_traits

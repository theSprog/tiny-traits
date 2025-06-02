#pragma once

#include "eq.hpp"
#include <cstddef>
#include <functional>

namespace tiny_traits {
template <typename Derived>
struct Hashable : Eq<Derived> {
  private:
    DEFINE_HAS_METHOD(hashcode);

    std::size_t __inner_hashcode() const {
        static_assert(must_has_hashcode<Derived, std::size_t()>::value,
                      "Derived must implement `std::size_t hashcode() const`");
        return static_cast<const Derived&>(*this).hashcode();
    }
};

struct Hasher {
    // 针对继承自 Hashable 的类型
    template <typename T>
    typename std::enable_if<std::is_base_of<Hashable<T>, T>::value, std::size_t>::type
    operator()(const T& obj) const noexcept {
        return obj.hashcode();
    }

    // 针对其他情况
    template <typename T>
    typename std::enable_if<! std::is_base_of<Hashable<T>, T>::value, std::size_t>::type
    operator()(const T& obj) const noexcept {
        return std::hash<T>{}(obj);
    }
};
} // namespace tiny_traits

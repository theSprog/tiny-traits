#pragma once

#include "utils.hpp"

namespace tiny_traits {

template <typename Derived, typename T = Derived>
struct Eq {
  private:
    DEFINE_HAS_METHOD(equals);

  public:
    bool operator==(const T& other) const {
        static_assert(must_has_equals<Derived, bool(const T& other)>::value,
                      "Derived must implement `bool equals(const T& other) const`");

        auto& self = static_cast<const Derived&>(*this);
        return self.equals(other);
    }

    bool operator!=(const T& other) const {
        return ! (*this == other);
    }
};
} // namespace tiny_traits

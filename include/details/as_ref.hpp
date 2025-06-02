#pragma once

namespace tiny_traits {
template <typename T>
struct AsRef {
    virtual T as_ref() const = 0;
    virtual ~AsRef() = default;
};
} // namespace tiny_traits

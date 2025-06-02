#pragma once

namespace tiny_traits {
struct Resettable {
    virtual void reset() = 0;
    virtual ~Resettable() = default;
};

struct Validatable {
    virtual bool is_valid() const = 0;
    virtual ~Validatable() = default;
};
} // namespace tiny_traits

#pragma once

#include <string>
#include <sstream> // IWYU pragma: keep

namespace tiny_traits {
struct ToString {
    virtual std::string to_string() const = 0;
    virtual ~ToString() = default;
};
} // namespace tiny_traits

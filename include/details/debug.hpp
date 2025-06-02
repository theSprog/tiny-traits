#pragma once

#include <iostream>

namespace tiny_traits {
struct Debug {
    virtual void debug(std::ostream&) const = 0;
    virtual ~Debug() = default;
};

inline std::ostream& operator<<(std::ostream& os, const Debug& d) {
    d.debug(os);
    return os;
}
} // namespace tiny_traits

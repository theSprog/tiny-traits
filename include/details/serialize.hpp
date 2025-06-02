#pragma once

#include <string>

namespace tiny_traits {
struct Serializable {
    virtual std::string serialize() const = 0;
    virtual ~Serializable() = default;
};

struct Deserializable {
    virtual void deserialize(const std::string&) = 0;
    virtual ~Deserializable() = default;
};
} // namespace tiny_traits

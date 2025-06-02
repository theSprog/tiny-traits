#pragma once

#include "utils.hpp"
#include <type_traits>

namespace tiny_traits {
// ---- 2. 总检查开关 ----------------------------------------------------------
template <typename C, typename = void>
struct is_valid_iterable : std::false_type {}; // 默认不合格

template <typename C>
struct is_valid_iterable<
    C,
    void_t<
        // ──(1) 嵌套类型存在 ─────────────────────────────────────────────
        typename C::iterator,
        typename C::const_iterator,

        // ──(2) iterator 三大运算 ────────────────────────────────────────
        decltype(++std::declval<typename C::iterator&>()),
        decltype(*std::declval<typename C::iterator&>()),
        decltype(std::declval<typename C::iterator&>() != std::declval<typename C::iterator&>()),

        // ──(3) const_iterator 三大运算 ──────────────────────────────────
        decltype(++std::declval<typename C::const_iterator&>()),
        decltype(*std::declval<typename C::const_iterator&>()),
        decltype(std::declval<typename C::const_iterator&>() != std::declval<typename C::const_iterator&>()),

        // ──(4) begin/end (非常量) 返回 iterator ────────────────────────
        typename std::enable_if<std::is_same<decltype(std::declval<C&>().begin()), typename C::iterator>::value>::type,
        typename std::enable_if<std::is_same<decltype(std::declval<C&>().end()), typename C::iterator>::value>::type,

        // ──(5) begin/end (常量) 返回 const_iterator ─────────────────────
        typename std::enable_if<
            std::is_same<decltype(std::declval<const C&>().begin()), typename C::const_iterator>::value>::type,
        typename std::enable_if<
            std::is_same<decltype(std::declval<const C&>().end()), typename C::const_iterator>::value>::type>>
    : std::true_type {};

// ---- 3. CRTP 基类，只做 static_assert --------------------------------------
template <typename Derived>
struct Iterable {
    Iterable() {
        static_assert(is_valid_iterable<Derived>::value,
                      "Class deriving from Iterable must:\n"
                      "  1. have nested struct iterator / const_iterator\n"
                      "  2. both iterators implement *, ++, !=\n"
                      "  3. begin()/end()  -> iterator\n"
                      "  4. begin()/end() const -> const_iterator\n");
    }
};

} // namespace tiny_traits

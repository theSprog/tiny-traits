#pragma once
#include <type_traits> // IWYU pragma: keep
#include <utility>     // IWYU pragma: keep

// C++11 void_t poly-fill
template <typename... Ts>
struct make_void {
    using type = void;
};

template <typename... Ts>
using void_t = typename make_void<Ts...>::type;

#define DEFINE_HAS_METHOD(METHOD)                                                                   \
    template <typename, typename Signature, typename = void>                                        \
    struct must_has_##METHOD : std::false_type {};                                                  \
                                                                                                    \
    template <typename C, typename Ret, typename... Args>                                           \
    struct must_has_##METHOD<C,                                                                     \
                             Ret(Args...),                                                          \
                             void_t</* decltype 必须能编译 */                                       \
                                    decltype(std::declval<C>().METHOD(std::declval<Args>()...))>> { \
        /* 完全匹配返回类型才算通过 */                                                              \
        static constexpr bool value =                                                               \
            std::is_same<decltype(std::declval<C>().METHOD(std::declval<Args>()...)), Ret>::value;  \
    };

#define DEFINE_HAS_STATIC_METHOD(METHOD)                                                                      \
    template <typename, typename Signature, typename = void>                                                  \
    struct must_has_static_##METHOD : std::false_type {};                                                            \
                                                                                                              \
    template <typename C, typename Ret, typename... Args>                                                     \
    struct must_has_static_##METHOD<C, Ret(Args...), void_t<decltype(C::METHOD(std::declval<Args>()...))>> {         \
        static constexpr bool value = std::is_same<decltype(C::METHOD(std::declval<Args>()...)), Ret>::value; \
    };

